#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int addToDatabase(char *name, float rating);
char *get_string(const char *str);
float get_float(const char *prompt);

int main(void) {
    printf("***** Female Database Creator *****\n\n");

    char *userChoice = get_string("Choose an option:\n1. add entry\n2. learn more\n1");

    if (userChoice == NULL) {
        return 1;
    }

    if (strcmp(userChoice, "1") == 0) {
        char *name = get_string("Enter name: ");
        float rating = get_float("Enter rating: ");
        addToDatabase(name, rating);

        if (name == NULL) {
            fprintf(stderr, "Failed to allocate memory.\n");
            return 1;
        }
    }
    else if (strcmp(userChoice, "2") == 0) {
        printf("Female Database Creator is a fast and simple way to create a database of all the women you know.\n");
        printf("Enter in info such as name, weight, rating, age, etc.\n" );
        printf("This is stored locally on your device in the form of a .csv file.\n");
    }

    return 0;
}

char *get_string(const char *str) {
    char *string = malloc(31);
    if (string == NULL) {
        return nullptr;
    }

    printf("%s", str);
    fflush(stdout);

    if(scanf("%30s", string) != 1) {
        free(string);
        return nullptr;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    return string;
}

float get_float(const char *prompt) {
    char buffer[30];
    char *endptr;
    float input = 0;

    printf("%s", prompt);

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        input = strtof(buffer, &endptr);

        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }

        if (*endptr != '\n' && *endptr != 0) {
            fprintf(stderr, "Invalid input, try again.\n");
            return 0;
        }
    }
    else {
        fprintf(stderr, "Invalid input, try again.\n");
    }
    return input;
}

int addToDatabase(char *name, float rating) {
    FILE *file = fopen("/Users/hdea3/Documents/Coding/untitled/database.csv", "a");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    if(fprintf(file, "Name: %s, Rating: %.2f\n", name, rating) < 0) {
        perror("Error writing to file");
        fclose(file);
        return 2;
    }

    fclose(file);
    printf("Operation Successful.\n");

    free(name);

    return 0;
}