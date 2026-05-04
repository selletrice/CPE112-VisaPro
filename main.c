#include "visa_pro.h"
#include <stdio.h>

int main(){
    int choice;
    long long id;
    char name[MAX];

    // Framework initialization
    initTable();
    initVisaRoadmap();

    while(1){
        printf("\n--- VISA PROGRESS TRACKING SYSTEM---\n");
        printf("1: Register Student Profile\n");
        printf("2: Check Visa Status (Roadmap)\n");
        printf("3: Move to the Next Stage\n");
        printf("4: Renew Visa (Reset Cycle)\n");
        printf("5: Exit\n");
        printf("Enter choice:\n");
        scanf("%d", &choice);
    switch(choice){
        // Register Student Profile
        case 1:
            printf("Enter Student ID: ");
            scanf("%lld", &id);
            printf("Enter Name: ");
            scanf("%s", name);
            insertStudent(id, name);

            struct student *newStudent = searchStudent(id);
            if (newStudent != NULL){
                startVisaProcess(newStudent);
            }
            break;
        // Search and print current stage
        case 2:
            printf("Enter Student ID to check current progress: ");
            scanf("%lld", &id);
            struct student *s = searchStudent(id);
            if (s != NULL && s->currentStage != NULL){
                printf("Student: %s\n", s->name);
                printf("Current Status: %s\n", s->currentStage->stageName);
            } else{
                printf("Student not found or no process started.");
            }
            break;
        // Move stage forward by moving pointer to next
        case 3:
            printf("Enter Student ID to update progress: ");
            scanf("%lld", &id);
            struct student *updateStage = searchStudent(id);
            if (updateStage != NULL){
                moveToNextStage(updateStage);
            } else{
                printf("Student not found.\n");
            }
            break;
        // Visa Renewal
        case 4:
            // For Member 3
            break;
        case 5:
           return 0;
    }
}
return 0;
}