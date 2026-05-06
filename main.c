#include "visa_pro.h"
#include <string.h>  
#include <stdio.h>

int main() {
    int choice;
    long long id;
    char name[MAX], vDate[20], rDate[20];

    initTable();
    displayHeader();

    while (1) {
        printf("\n--- MAIN MENU ---\n");
        printf("1: Register Student Profile\n");
        printf("2: Run Automated Scheduler (Check Priority)\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            // Inside main.c - Case 1 (Registration)
            case 1:
            printf("Enter Student ID: ");
            scanf("%lld", &id);
            getchar();
            printf("Enter Full Name: ");
            fgets(name, MAX, stdin);
            name[strcspn(name, "\n")] = 0;

            // Input and Validate Visa Expiry
            int vCheck = -999;
        while (vCheck == -999) {

            printf("Enter Visa Expiry (YYYY-MM-DD): ");
            scanf("%s", vDate);
            vCheck = getDaysRemaining(vDate);

        if (vCheck == -999) {
            printf("[INVALID INPUT]: Please check your Year, Month (1-12), or Day (1-31).\n");
        }
    }

    // Input and Validate 90-Day Deadline
    int rCheck = -999;
    while (rCheck == -999) {
        printf("Enter 90-Day Deadline (YYYY-MM-DD): ");
        scanf("%s", rDate);
        rCheck = getDaysRemaining(rDate);
        if (rCheck == -999) {
            printf("[INVALID INPUT]: Please check your Year, Month (1-12), or Day (1-31).\n");
        }
    }

    insertStudent(id, name, vDate, rDate);
    break;

            case 2:
                printf("Enter ID to check: ");
                scanf("%lld", &id);
                struct student *s = searchStudent(id);
                if (s) {
                    checkDeadlinesAndProcess(s);
                } else {
                    printf("Student ID not found.\n");
                }
                break;

            case 3:
               return 0;
        }
    }
}