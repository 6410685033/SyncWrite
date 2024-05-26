#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_SIZE 20
#define MAX_ATTENDEES 10
#define ATTENDEE_NAME_SIZE 1024

typedef struct {
    char file_name[NAME_SIZE];
    char attendances[MAX_ATTENDEES][ATTENDEE_NAME_SIZE];
    int num_attendees;
} File;

void create_file(File *file, const char *file_name) {
    if (file == NULL) {
        fprintf(stderr, "Error: file pointer is NULL.\n");
        return;
    }
    if (file_name == NULL) {
        fprintf(stderr, "Warning: file_name is NULL. Initializing with default name.\n");
        strcpy(file->file_name, "Default File");
    } else {
        strncpy(file->file_name, file_name, NAME_SIZE - 1);
        file->file_name[NAME_SIZE - 1] = '\0';
    }
    file->num_attendees = 0;
}

int join_file(File *file, const char *attendee) {
    if (file->num_attendees >= MAX_ATTENDEES) {
        printf("File is full. Can't add more attendees.\n");
        return -1;
    }

    strncpy(file->attendances[file->num_attendees], attendee, ATTENDEE_NAME_SIZE - 1);
    file->attendances[file->num_attendees][ATTENDEE_NAME_SIZE - 1] = '\0';
    file->num_attendees++;

    return 0;
}

int leave_file(File *file, const char *attendee) {
    int index = -1;

    for (int i = 0; i < file->num_attendees; i++) {
        if (strcmp(file->attendances[i], attendee) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Attendee '%s' not found in the file.\n", attendee);
        return -1;
    }

    for (int i = index; i < file->num_attendees - 1; i++) {
        strncpy(file->attendances[i], file->attendances[i + 1], ATTENDEE_NAME_SIZE - 1);
        file->attendances[i][ATTENDEE_NAME_SIZE - 1] = '\0';
    }

    file->attendances[file->num_attendees - 1][0] = '\0';
    file->num_attendees--;

    return 0;
}

void print_file_info(const File *file) {
    printf("File Name: %s\n", file->file_name);
    printf("Attendees (%d):\n", file->num_attendees);
    for (int i = 0; i < file->num_attendees; i++) {
        printf("%d. %s\n", i + 1, file->attendances[i]);
    }
}

char* show_attendees(const File *file) {
    char *response = (char *)malloc(file->num_attendees * ATTENDEE_NAME_SIZE);
    if (response == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    response[0] = '\0';

    strcat(response, "attendances ");
    for (int i = 0; i < file->num_attendees; i++) {
        char temp_name[ATTENDEE_NAME_SIZE];
        strncpy(temp_name, file->attendances[i], ATTENDEE_NAME_SIZE - 1);
        temp_name[ATTENDEE_NAME_SIZE - 1] = '\0';

        // Replace newline characters with spaces
        for (char *p = temp_name; *p; ++p) {
            if (*p == '\n') {
                *p = ' ';
            }
        }

        strcat(response, temp_name);
        // if (i < file->num_attendees - 1) {
        //     strcat(response, " ");
        // }
    }

    strcat(response, "\n");
    return response;
}