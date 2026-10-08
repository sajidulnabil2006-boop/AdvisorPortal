#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_COURSES 5


typedef struct {
    char code[20];
    char name[50];
    float marks;
    float gradePoint;
    char grade[3];
} Course;

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char department[30];
    char email[50];

    Course courses[MAX_COURSES];
    int courseCount;

    float cgpa;
} Student;



Student students[MAX_STUDENTS];
int studentCount = 0;


int login();


void addStudent();
void viewStudents();
void searchStudent();
void searchByName();
void updateStudent();
void deleteStudent();


void sortByCGPA();
void sortByName();


void statistics();
void departmentStatistics();


void addCourse();
void viewCourses();


void saveData();
void loadData();


int findStudentByID(int id);
void calculateCGPA(Student *s);
void calculateGrade(float marks, char grade[], float *gp);




int main() {

    int choice;

    loadData();

    printf("\n");
    printf("============================================\n");
    printf("       STUDENT MANAGEMENT SYSTEM\n");
    printf("============================================\n");

    if (!login()) {

        printf("\nLogin failed!\n");
        return 0;
    }

    while (1) {

        printf("\n\n============================================\n");
        printf("                ADMIN MENU\n");
        printf("============================================\n");

        printf("1.  Add Student\n");
        printf("2.  View All Students\n");
        printf("3.  Search Student by ID\n");
        printf("4.  Search Student by Name\n");
        printf("5.  Update Student\n");
        printf("6.  Delete Student\n");
        printf("7.  Sort by CGPA\n");
        printf("8.  Sort by Name\n");
        printf("9.  Student Statistics\n");
        printf("10. Department Statistics\n");
        printf("11. Add Course / Marks\n");
        printf("12. View Student Courses\n");
        printf("13. Save Data\n");
        printf("0.  Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                viewStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                searchByName();
                break;

            case 5:
                updateStudent();
                break;

            case 6:
                deleteStudent();
                break;

            case 7:
                sortByCGPA();
                break;

            case 8:
                sortByName();
                break;

            case 9:
                statistics();
                break;

            case 10:
                departmentStatistics();
                break;

            case 11:
                addCourse();
                break;

            case 12:
                viewCourses();
                break;

            case 13:
                saveData();
                break;

            case 0:

                saveData();

                printf("\nData saved successfully.\n");
                printf("Goodbye!\n");

                return 0;

            default:

                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}




int login() {

    char username[30];
    char password[30];

    int attempts = 3;

    while (attempts > 0) {

        printf("\nUsername: ");
        scanf("%s", username);

        printf("Password: ");
        scanf("%s", password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {

            printf("\nLogin successful!\n");

            return 1;
        }

        attempts--;

        printf("\nWrong username or password!\n");
        printf("Attempts remaining: %d\n", attempts);
    }

    return 0;
}




void addStudent() {

    if (studentCount >= MAX_STUDENTS) {

        printf("\nStudent limit reached!\n");
        return;
    }

    Student s;

    printf("\n============================================\n");
    printf("              ADD STUDENT\n");
    printf("============================================\n");

    printf("Enter Student ID: ");
    scanf("%d", &s.id);

    /* Check duplicate ID */

    if (findStudentByID(s.id) != -1) {

        printf("\nThis Student ID already exists!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %s[^\n]", s.name);

    printf("\nEnter Age: ");
    scanf("%d", &s.age);

    printf("\nEnter Gender: ");
    scanf("%s", s.gender);

    printf("\nEnter Department: ");
    scanf(" %[^\n]", s.department);

    printf("\nEnter Email: ");
    scanf("%s", s.email);

    s.courseCount = 0;
    s.cgpa = 0.0;

    students[studentCount] = s;

    studentCount++;

    saveData();

    printf("\nStudent added successfully!\n");
}




void viewStudents() {

    if (studentCount == 0) {

        printf("\nNo students available.\n");
        return;
    }

    printf("\n");
    printf("================================================================================\n");
    printf("%-8s %-20s %-5s %-10s %-20s %-6s\n", "ID", "Name", "Age", "Gender", "Department", "CGPA");

    printf("================================================================================\n");

    for (int i = 0; i < studentCount; i++) {

        printf("%-8d %-20s %-5d %-10s %-20s %.2f\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].gender,
               students[i].department,
               students[i].cgpa);
    }

    printf("================================================================================\n");
}



void searchStudent() {

    int id;

    printf("\nEnter Student ID: ");
    scanf("%d", &id);

    int index = findStudentByID(id);

    if (index == -1) {

        printf("\nStudent not found!\n");
        return;
    }

    Student *s = &students[index];

    printf("\n============================================\n");
    printf("              STUDENT DETAILS\n");
    printf("============================================\n");

    printf("ID         : %d\n", s->id);
    printf("Name       : %s\n", s->name);
    printf("Age        : %d\n", s->age);
    printf("Gender     : %s\n", s->gender);
    printf("Department : %s\n", s->department);
    printf("Email      : %s\n", s->email);
    printf("CGPA       : %.2f\n", s->cgpa);
}



void searchByName() {

    char name[50];
    int found = 0;

    printf("\nEnter student name: ");
    scanf(" %[^\n]", name);

    printf("\nSearch Results:\n");

    for (int i = 0; i < studentCount; i++) {

        if (strstr(students[i].name, name) != NULL) {

            printf("\nID         : %d\n", students[i].id);
            printf("Name       : %s\n", students[i].name);
            printf("Department : %s\n", students[i].department);
            printf("CGPA       : %.2f\n", students[i].cgpa);

            found = 1;
        }
    }

    if (!found) {

        printf("\nNo student found.\n");
    }
}


void updateStudent() {

    int id;

    printf("\nEnter Student ID: ");
    scanf("%d", &id);

    int index = findStudentByID(id);

    if (index == -1) {

        printf("\nStudent not found!\n");
        return;
    }

    Student *s = &students[index];

    printf("\nCurrent information:\n");

    printf("Name       : %s\n", s->name);
    printf("Age        : %d\n", s->age);
    printf("Gender     : %s\n", s->gender);
    printf("Department : %s\n", s->department);
    printf("Email      : %s\n", s->email);

    printf("\nEnter new information:\n");

    printf("Name: ");
    scanf(" %[^\n]", s->name);

    printf("Age: ");
    scanf("%d", &s->age);

    printf("Gender: ");
    scanf("%s", s->gender);

    printf("Department: ");
    scanf(" %[^\n]", s->department);

    printf("Email: ");
    scanf("%s", s->email);

    saveData();

    printf("\nStudent updated successfully!\n");
}




void deleteStudent() {

    int id;

    printf("\nEnter Student ID: ");
    scanf("%d", &id);

    int index = findStudentByID(id);

    if (index == -1) {

        printf("\nStudent not found!\n");
        return;
    }

    printf("\nStudent: %s\n", students[index].name);

    char confirm;

    printf("Are you sure you want to delete? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y') {

        printf("\nDelete cancelled.\n");
        return;
    }

    /* Shift students */

    for (int i = index; i < studentCount - 1; i++) {

        students[i] = students[i + 1];
    }

    studentCount--;

    saveData();

    printf("\nStudent deleted successfully!\n");
}


void sortByCGPA() {

    Student temp;

    for (int i = 0; i < studentCount - 1; i++) {

        for (int j = 0; j < studentCount - i - 1; j++) {

            if (students[j].cgpa <
                students[j + 1].cgpa) {

                temp = students[j];

                students[j] = students[j + 1];

                students[j + 1] = temp;
            }
        }
    }

    printf("\nStudents sorted by CGPA.\n");

    viewStudents();
}



void sortByName() {

    Student temp;

    for (int i = 0; i < studentCount - 1; i++) {

        for (int j = 0; j < studentCount - i - 1; j++) {

            if (strcmp(students[j].name,
                       students[j + 1].name) > 0) {

                temp = students[j];

                students[j] = students[j + 1];

                students[j + 1] = temp;
            }
        }
    }

    printf("\nStudents sorted alphabetically.\n");

    viewStudents();
}




void statistics() {

    if (studentCount == 0) {

        printf("\nNo students available.\n");
        return;
    }

    float total = 0;

    int highest = 0;
    int lowest = 0;

    for (int i = 0; i < studentCount; i++) {

        total += students[i].cgpa;

        if (students[i].cgpa >
            students[highest].cgpa) {

            highest = i;
        }

        if (students[i].cgpa <
            students[lowest].cgpa) {

            lowest = i;
        }
    }

    float average = total / studentCount;

    printf("\n============================================\n");
    printf("             STUDENT STATISTICS\n");
    printf("============================================\n");

    printf("Total Students : %d\n", studentCount);

    printf("Average CGPA   : %.2f\n", average);

    printf("\nHighest CGPA:\n");
    printf("Name : %s\n", students[highest].name);
    printf("CGPA : %.2f\n", students[highest].cgpa);

    printf("\nLowest CGPA:\n");
    printf("Name : %s\n", students[lowest].name);
    printf("CGPA : %.2f\n", students[lowest].cgpa);
}



void departmentStatistics() {

    char department[30];

    int total = 0;
    float cgpaTotal = 0;

    printf("\nEnter Department: ");
    scanf(" %[^\n]", department);

    for (int i = 0; i < studentCount; i++) {

        if (strcmp(students[i].department,
                   department) == 0) {

            total++;

            cgpaTotal += students[i].cgpa;
        }
    }

    if (total == 0) {

        printf("\nNo students found in this department.\n");
        return;
    }

    printf("\n============================================\n");
    printf("        DEPARTMENT STATISTICS\n");
    printf("============================================\n");

    printf("Department    : %s\n", department);
    printf("Total Students: %d\n", total);
    printf("Average CGPA  : %.2f\n",
           cgpaTotal / total);
}



void addCourse() {

    int id;

    printf("\nEnter Student ID: ");
    scanf("%d", &id);

    int index = findStudentByID(id);

    if (index == -1) {

        printf("\nStudent not found!\n");
        return;
    }

    Student *s = &students[index];

    if (s->courseCount >= MAX_COURSES) {

        printf("\nMaximum course limit reached!\n");
        return;
    }

    Course *c = &s->courses[s->courseCount];

    printf("\nEnter Course Code: ");
    scanf("%s", c->code);

    printf("Enter Course Name: ");
    scanf(" %[^\n]", c->name);

    printf("Enter Marks (0-100): ");
    scanf("%f", &c->marks);

    calculateGrade(c->marks,
                   c->grade,
                   &c->gradePoint);

    s->courseCount++;

    calculateCGPA(s);

    saveData();

    printf("\nCourse added successfully!\n");

    printf("Grade      : %s\n", c->grade);
    printf("Grade Point: %.2f\n", c->gradePoint);
    printf("New CGPA   : %.2f\n", s->cgpa);
}



void calculateGrade(float marks, char grade[], float *gp) {

    if (marks >= 80) {

        strcpy(grade, "A+");
        *gp = 4.00;
    }

    else if (marks >= 75) {

        strcpy(grade, "A");
        *gp = 3.75;
    }

    else if (marks >= 70) {

        strcpy(grade, "A-");
        *gp = 3.50;
    }

    else if (marks >= 65) {

        strcpy(grade, "B+");
        *gp = 3.25;
    }

    else if (marks >= 60) {

        strcpy(grade, "B");
        *gp = 3.00;
    }

    else if (marks >= 55) {

        strcpy(grade, "B-");
        *gp = 2.75;
    }

    else if (marks >= 50) {

        strcpy(grade, "C+");
        *gp = 2.50;
    }

    else if (marks >= 45) {

        strcpy(grade, "C");
        *gp = 2.25;
    }

    else if (marks >= 40) {

        strcpy(grade, "D");
        *gp = 2.00;
    }

    else {

        strcpy(grade, "F");
        *gp = 0.00;
    }
}



void calculateCGPA(Student *s) {

    if (s->courseCount == 0) {

        s->cgpa = 0;

        return;
    }

    float total = 0;

    for (int i = 0; i < s->courseCount; i++) {

        total += s->courses[i].gradePoint;
    }

    s->cgpa = total / s->courseCount;
}


void viewCourses() {

    int id;

    printf("\nEnter Student ID: ");
    scanf("%d", &id);

    int index = findStudentByID(id);

    if (index == -1) {

        printf("\nStudent not found!\n");
        return;
    }

    Student *s = &students[index];

    printf("\n============================================\n");
    printf("Student: %s\n", s->name);
    printf("============================================\n");

    if (s->courseCount == 0) {

        printf("No courses registered.\n");
        return;
    }

    for (int i = 0; i < s->courseCount; i++) {

        printf("\nCourse %d\n", i + 1);

        printf("Code        : %s\n",
               s->courses[i].code);

        printf("Name        : %s\n",
               s->courses[i].name);

        printf("Marks       : %.2f\n",
               s->courses[i].marks);

        printf("Grade       : %s\n",
               s->courses[i].grade);

        printf("Grade Point : %.2f\n",
               s->courses[i].gradePoint);
    }

    printf("\nCGPA: %.2f\n", s->cgpa);
}



int findStudentByID(int id) {

    for (int i = 0; i < studentCount; i++) {

        if (students[i].id == id) {

            return i;
        }
    }

    return -1;
}


void saveData() {

    FILE *file;

    file = fopen("students.dat", "wb");

    if (file == NULL) {

        printf("\nError opening file!\n");
        return;
    }

    fwrite(&studentCount, sizeof(int),1,file);

    fwrite(students,
           sizeof(Student),
           studentCount,
           file);

    fclose(file);
}




void loadData() {

    FILE *file;

    file = fopen("students.dat", "rb");

    if (file == NULL) {

        return;
    }

    fread(&studentCount,
          sizeof(int),
          1,
          file);

    fread(students,
          sizeof(Student),
          studentCount,
          file);

    fclose(file);
}