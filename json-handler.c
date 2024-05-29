#include "json-handler.h"
#include <stdio.h>
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>

char *read_in_object() {
    //setup variable for json config
    const char* suffix = "/.config/LogOutMan/LogOutMan.json";
    const char* json_file = strcat(getenv("HOME"),suffix);

    // Open a file in read mode
    FILE *fptr;
    fptr = fopen(json_file, "r");

    // Get file length
    fseek(fptr, 0L, SEEK_END);
    long file_size = ftell(fptr);
    rewind(fptr);

    //read data from file
    char *buffer = malloc(file_size);
    if (fptr) {
        fread(buffer, 1, file_size, fptr);
    } else {
        return "not open";
    }

    fclose(fptr);
    return buffer;
}

char ***parse(const char *const JSON_string) {

    int json_array_length =6;

    int length_of_longest_string = 0;

    //parse string to "Commands" object
    cJSON *json_object = cJSON_Parse(JSON_string);
    if (json_object == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
            return NULL;
        }
    }

    const cJSON *command = NULL;
    const cJSON *commands = NULL;
    commands = cJSON_GetObjectItemCaseSensitive(json_object, "Commands");
    cJSON_ArrayForEach(command,commands)
    {
        cJSON *name_attribute = cJSON_GetObjectItemCaseSensitive(command, "name");
        cJSON *command_attribute = cJSON_GetObjectItemCaseSensitive(command, "command");

        if (!cJSON_IsString(name_attribute) || !cJSON_IsString(command_attribute))
        {
            perror("Parsing error");
            return NULL;
        }
        int name_length = strlen(name_attribute->valuestring);
        int command_length = strlen(command_attribute->valuestring);

        if(length_of_longest_string< name_length||length_of_longest_string<command_length){
            length_of_longest_string = name_length;
        }
    }
    //----------------

    
    char ***names_and_commands = (char ***) malloc(json_array_length * sizeof(char **));
    if (names_and_commands == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < json_array_length; i++) {
        names_and_commands[i] = (char **) malloc(2 * sizeof(char *));
        if (names_and_commands[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < 2; j++) {
            names_and_commands[i][j] = (char *) malloc((length_of_longest_string + 1) * sizeof(char)); // +1 for null terminator
            if (names_and_commands[i][j] == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(names_and_commands[i][j], ""); // Initialize with empty string
        }
    }

    int command_indicator=0;
    cJSON_ArrayForEach(command,commands)
    {
        cJSON *name_attribute = cJSON_GetObjectItemCaseSensitive(command, "name");
        cJSON *command_attribute = cJSON_GetObjectItemCaseSensitive(command, "command");

        if (!cJSON_IsString(name_attribute) || !cJSON_IsString(command_attribute))
        {
            goto end;
        }

        names_and_commands[command_indicator][0] = cJSON_Print(name_attribute);
        names_and_commands[command_indicator][1] = cJSON_Print(command_attribute);

        //remove circumfix of elements
        names_and_commands[command_indicator][0] += 1;
        names_and_commands[command_indicator][1] += 1;
        (names_and_commands[command_indicator][0])[strlen(names_and_commands[command_indicator][0]) -1] = '\0';
        (names_and_commands[command_indicator][1])[strlen(names_and_commands[command_indicator][1]) -1] = '\0';
        command_indicator++;

    }

    //deletion of json object
    end:
    cJSON_Delete(json_object);

    return names_and_commands;
}