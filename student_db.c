#include "visa_pro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101

struct student* hashTable[TABLE_SIZE] = {NULL};

void initTable(){
    for (int i = 0; i < TABLE_SIZE; i++){
        hashTable[i] = NULL;
    }
}

int hashFunction(long long id){
    int batch = (int)(id/1000000000LL); // Extract first two digits of student ID for year/batch
    int dept = (int)((id/100) % 100); // Extract department code
    int seq = (int)(id % 100); // Extract last two digits

    int hashValue = batch + dept + seq;

    return hashValue % TABLE_SIZE;
}

// Updating insertStudent Function 
void insertStudent(long long id, char* name, char* visaEx, char* reportEx) {
    // Calculate the hash index for the student ID
    int index = hashFunction(id);

    // Allocate memory for a new student structure
    struct student *newStudent = (struct student*)malloc(sizeof(struct student));
    
    // Safety check: Ensure memory allocation was successful
    if (newStudent == NULL) return; 

    // Assign the student ID
    newStudent->id = id;
    
    // Copy the student name safely to prevent buffer overflow
    strncpy(newStudent->name, name, MAX);
    newStudent->name[MAX - 1] = '\0'; // Ensure the string is null-terminated

    // Store date information (Crucial for Member 3's deadline tracking)
    strncpy(newStudent->visaExpiry, visaEx, 20);
    strncpy(newStudent->report90DayDeadline, reportEx, 20);

    // Initialize other pointers to NULL to prevent dangling pointers
    newStudent->currentStage = NULL; 
    newStudent->current90DaysStage = NULL;
    newStudent->doc90DaysTreeRoot = NULL;

    // Insert the student into the Hash Table using Chaining to handle collisions
    newStudent->next = hashTable[index];
    hashTable[index] = newStudent;

    // Initialize the Document Tree for Visa (Member 2's logic)
    newStudent->docTreeRoot = docTree();

    // Confirm successful registration
    printf("SUCCESS: Student [%lld] added to Index %d\n", id, index);
}

struct student* searchStudent(long long id){ // Average time of O(1)
    int index = hashFunction(id);
    struct student *current = hashTable[index];

    while (current != NULL){
        if (current->id == id){
            return current;
        }
        current = current->next;
    }
    return NULL;
}