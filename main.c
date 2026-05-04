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
            break;
        // Search and print current stage
        case 2:
            // Insert code here later
            break;
        // Move stage forward by moving pointer to next
        case 3:
            // Insert code here later
            break;
        // Visa Renewal
        case 4:
            // Insert code here later
            break;
        case 5:
           return 0;
    }
}
return 0;
}