/* This program is to display and change the attributes of files present on disk */
/* REQUIRED HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define READ_ONLY 0x01   
#define HIDDEN    0x02   
#define SYSTEM    0x04 
#define VOLUME    0x08 
#define DIRECTORY 0x10   
#define ARCHIVE   0x20   

typedef struct {
    char filename[9];      
    char extension[4];     
    unsigned char attr;    
} DirectoryEntry;

/*display_attributes: Function to display file attributes */
void display_attributes(DirectoryEntry *entry) {
    printf("File: %s.%s\n", entry->filename, entry->extension);
    printf("Attributes: \n");
    if (entry->attr & READ_ONLY) printf("Read-only\n");
    if (entry->attr & HIDDEN) printf("Hidden \n");
    if (entry->attr & SYSTEM) printf("System \n");
    if (entry->attr & VOLUME) printf("Volume \n");
    if (entry->attr & DIRECTORY) printf("Directory \n");
    if (entry->attr & ARCHIVE) printf("Archive \n");
}

/* Function to apply real read-only attribute on the file using chmod */
void apply_real_attributes(DirectoryEntry *entry) {
    char filepath[100];
    sprintf(filepath, "%s.%s", entry->filename, entry->extension);

    if (entry->attr & READ_ONLY) {
        chmod(filepath, S_IRUSR | S_IRGRP | S_IROTH);  
        printf("Applied read-only to %s\n", filepath);
    } else {
        chmod(filepath, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 
	printf("Applied read-write to %s\n", filepath);
    }


    if (entry->attr & HIDDEN) {
        char new_name[100];
        sprintf(new_name, ".%s.%s", entry->filename, entry->extension,5);
        rename(filepath, new_name);
        printf("Renamed file to hidden: %s\n", new_name);
    }
}

/* modify_attributes: Function to modify file attributes */
void modify_attributes(DirectoryEntry *entry) {
	int choice;
    unsigned char mask;
    printf("Modify Attributes:\n");
    printf("1. Toggle Read-only\n");
    printf("2. Toggle Hidden\n");
    printf("3. Toggle System\n");
    printf("4. Toggle Volume Label\n");
    printf("5. Toggle Directory\n");
    printf("6. Toggle Archive\n");
    printf("7. Exit\n");

    while (1) {
        printf("Enter choice: ");
        scanf("%d", &choice);
        if (choice == 7) break;

        switch (choice) {
            case 1:
                mask = READ_ONLY;
                break;
            case 2:
                mask = HIDDEN;
                break;
            case 3:
                mask = SYSTEM;
                break;
            case 4:
                mask = VOLUME;
                break;
            case 5:
                mask = DIRECTORY;
                break;
            case 6:
                mask = ARCHIVE;
                break;
            default:
                printf("Invalid choice\n");
                continue;
        }

        entry->attr ^= mask;  
        display_attributes(entry);  
    }
}

/* create_sample_file: Function to create a sample file and initialize DirectoryEntry */
void create_sample_file(DirectoryEntry *entry) {
    char filepath[100];
    sprintf(filepath, "%s.%s", entry->filename, entry->extension);

    
    int fd = open(filepath, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("Error creating file");
        return;
    }
    write(fd, "Sample content", 14);  
    close(fd);
}
/* main: Checking and modifying file attributes */
int main() 
{
    DirectoryEntry entry;
    strcpy(entry.filename, "file");  
    strcpy(entry.extension, "txt");  
    entry.attr = 0x00;               
    /* Create a sample file */
    create_sample_file(&entry);

    /* Display the initial attributes */
    display_attributes(&entry);

    /* Modify the attributes interactively */
    modify_attributes(&entry);

    /* Apply the real file system changes based on the attributes */
    apply_real_attributes(&entry);

    printf("Final Attributes:\n");
    display_attributes(&entry);

    return 0;
}
/* End main */
