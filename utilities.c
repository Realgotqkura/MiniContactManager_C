#include "utilities.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Person *personArr = NULL;
int person_array_count = 0;
const char *file_name = "contacts.txt";
bool exit_program = false;


COMMAND_TYPE get_command_type(char string_arr[][MAX_STRING_SIZE]) {
    char to_lower_case[MAX_STRING_SIZE];

    int i;
    for (i = 0; string_arr[0][i] != '\0' ;i++) {
        to_lower_case[i] = tolower((unsigned char) string_arr[0][i]);
    }
    to_lower_case[i] = '\0';

    if (strcmp(to_lower_case, "add") == 0) {
        return ADD;
    }
    if (strcmp(to_lower_case, "show") == 0) {
        return SHOW;
    }
    if (strcmp(to_lower_case, "save") == 0) {
        return SAVE;
    }
    if (strcmp(to_lower_case, "remove") == 0) {
        return REMOVE;
    }
    if (strcmp(to_lower_case, "edit") == 0) {
        return EDIT;
    }
    if (strcmp(to_lower_case, "load") == 0) {
        return LOAD;
    }
    if (strcmp(to_lower_case, "exit") == 0) {
        return EXIT;
    }

    return INVALID;
}

void execute_command(COMMAND_TYPE type, Person **person_arr, int *person_array_count, char string_arr[][MAX_STRING_SIZE]) {
    switch (type) {
        case ADD:
            add_command(person_arr, person_array_count, string_arr);
            break;
        case SAVE:
            FILE *save_file = openFile(file_name, "w+");
            save_contacts(save_file, *person_array_count, *person_arr);
            fclose(save_file);
            break;
        case LOAD:
            FILE *load_file = openFile(file_name, "r+");
            personArr = load_contacts(load_file);
            fclose(load_file);
            break;
        case EXIT:
            exit_program = true;
            break;
        case SHOW: {
            char names[*person_array_count][MAX_STRING_SIZE];
            char phone_numbers[*person_array_count][MAX_PHONE_NUMBER_SIZE];
            char emails[*person_array_count][MAX_STRING_SIZE];

            for (int i = 0; i < *person_array_count; i++) {
                strcpy(names[i], personArr[i].name);
                strcpy(phone_numbers[i], personArr[i].phone_number);
                strcpy(emails[i], personArr[i].email);
            }

            for (int i = 0; i < *person_array_count; i++) {
                printf("%d: name: %s, phone number: %s, email: %s\n",i, names[i], phone_numbers[i], emails[i]);
            }
            break;
        }
        default:
            printf("[ERROR] This shouldn't show up!\n");
            exit(1);
    }
}

/*
 *Adding the command functions
 *
 */

void add_command(Person **person_arr, int *person_array_count, const char string_arr[][MAX_STRING_SIZE]) {
    Person *temp_alloc = realloc(*person_arr, (*person_array_count + 1) * sizeof(Person));

    if (temp_alloc == NULL) {
        printf("Couldn't allocate memory (add_command)\n");
        exit(1);
    }

    *person_arr = temp_alloc;

    Person person;
    strcpy(person.name, string_arr[1]);
    strcpy(person.phone_number, string_arr[2]);
    strcpy(person.email, string_arr[3]);

    (*person_arr)[*person_array_count] = person;


    (*person_array_count)++;
    printf("Successfully added a player!\n");
}


FILE *openFile(char *file_name, char *mode) {
    FILE *return_file = fopen(file_name, mode);

    if (return_file == NULL) {
        printf("Could not open file!\n");
        exit(1);
    }

    return return_file;
}

void save_contacts(FILE *file, int count, Person *person_arr) {
    //Write number of contacts first
    fwrite(&count, sizeof(int), 1, file);
    fwrite(person_arr, sizeof(Person), count, file);
}

Person *load_contacts(FILE *file) {
    //Load in the person count
    int count = 0;
    fread(&count, sizeof(int), 1, file);
    person_array_count = count;

    Person *person_arr = malloc(sizeof(Person) * count);
    fread(person_arr, sizeof(Person), count, file);
    return person_arr;
}



