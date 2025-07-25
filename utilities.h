#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_STRING_SIZE 100
#define MAX_ARGUMENTS_SIZE 6
#define MAX_PHONE_NUMBER_SIZE 13


typedef struct {
    char name[MAX_STRING_SIZE];
    char phone_number[MAX_PHONE_NUMBER_SIZE];
    char email[MAX_STRING_SIZE];

}Person;

typedef enum {
    ADD,
    SHOW,
    SAVE,
    REMOVE,
    EDIT,
    LOAD,
    EXIT,
    INVALID


}COMMAND_TYPE;

typedef enum {
    NAME,
    EMAIL,
    PHONE
}PERSON_DATA;

extern Person *personArr;
extern int person_array_count;
extern const char *file_name;
extern bool exit_program;

COMMAND_TYPE get_command_type(char string_arr[][MAX_STRING_SIZE]);
void execute_command(COMMAND_TYPE type, Person **person_arr, int *person_array_count, char string_arr[][MAX_STRING_SIZE]);
void add_command(Person **person_arr, int *person_array_count, const char string_arr[][MAX_STRING_SIZE]);
FILE *openFile(char *file_name, char *mode);
void save_contacts(FILE *file, int count, Person *person_arr);
Person *load_contacts(FILE *file);
char *get_player_data_value(PERSON_DATA data, Person *person, int index);
Person *remove_people(Person *personArr, char *argument, PERSON_DATA data);

#endif //UTILITIES_H
