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
