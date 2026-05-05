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

void insertStudent(long long id, char* name){
    int index = hashFunction(id);

    struct student *newStudent = (struct student*)malloc(sizeof(struct student));

    newStudent->id = id;
    strncpy(newStudent->name, name, MAX);

    // Initializing Pointers for Document Checker and Current Stage
    newStudent->docTreeRoot = NULL;
    newStudent->currentStage = NULL; 

    newStudent->next = hashTable[index];
    hashTable[index] = newStudent;

    //member 2 addition: create a document tree after student creates an account
    newStudent->docTreeRoot = docTree();

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