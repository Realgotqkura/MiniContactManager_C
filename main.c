#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

int parseCommand(const char command[], char string_arr[][MAX_STRING_SIZE]);

int main() {
    char command[256] = "";
    char string_arr[MAX_ARGUMENTS_SIZE][MAX_STRING_SIZE];
    printf("Type out a command!\n");
    printf("Command: ");
    fgets(command, sizeof(command), stdin);

    size_t len = strlen(command);
    if (len > 0 && command[len - 1] == '\n') {
        command[len - 1] = '\0';
    }


    int arg_count = parseCommand(command, string_arr);
    COMMAND_TYPE get_command = get_command_type(string_arr[0]);
    execute_command(get_command, &personArr, &person_array_count, string_arr);


    if (exit_program == false)
        main();

    free(personArr);
    return 0;
}


int parseCommand(const char command[], char string_arr[][MAX_STRING_SIZE]){
    int current_argument_index = 0;
    int current_string_index = 0;
    for (int i = 0; command[i] != '\0'; i++) {
        if (i == 0 && command[0] == '/')
            continue;

        if (command[i] != ' ') {
            string_arr[current_argument_index][current_string_index] = command[i];
            current_string_index++;

            if (command[i+1] == '\0') {
                string_arr[current_argument_index][current_string_index] = '\0';
            }

        }else {
            string_arr[current_argument_index][current_string_index] = '\0';
            current_string_index = 0;
            current_argument_index++;
        }
    }

    return current_argument_index;
}





