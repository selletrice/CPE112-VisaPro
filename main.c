#include "visa_pro.h"
#include <stdio.h>

void displayHeader(){
    printf("\n******************************************\n");
    printf("*              VISAPRO                   *\n");
    printf("*    VISA & 90-DAY TRACKING SYSTEM       *\n");
    printf("*    Computer Engineering Project        *\n");
    printf("******************************************\n");
}

int main()
{
    int choice;
    long long id;
    char name[MAX];

    // Framework initialization
    initTable();
    initVisaRoadmap();
    init90DaysRoadmap();

    displayHeader();

    while (1)
    {
        printf("\n--- MAIN MENU ---\n");
        printf("1: Register Student Profile\n");
        printf("2: Run Automated Scheduler (Check Priority)\n");
        printf("5: Exit\n");

        printf("Enter choice:\n");
        if (scanf("%d", &choice) != 1)
        {
            break;
        }

        getchar();

        switch (choice)
        {
        // Register Student Profile
        case 1:
            printf("Enter Student ID: ");
            scanf("%lld", &id);

            getchar();

            printf("Enter Full Name: ");
            fgets(name, MAX, stdin);
            insertStudent(id, name);

            name[strcspn(name, "\n")] = 0;

            insertStudent(id, name);
            struct student *newStudent = searchStudent(id);

            if (newStudent != NULL)
            {
                printf("Select Process: [1] Visa [2] 90-Days [3] Both: ");
                int track;
                scanf("%d", &track);
                if (track == 1 || track == 3)
                {
                    startVisaProcess(newStudent);
                }
                if (track == 2 || track == 3)
                {
                    start90DaysProcess(newStudent);
                }
                printf("SUCCESS: %s is registered.\n", newStudent->name);
            }
            break;
            // Search and print current stage
        case 2:
            printf("Enter Student ID to check current progress: ");
            scanf("%lld", &id);
            struct student *s = searchStudent(id);

            if (s != NULL)
            {
                // DATE CHECK: Is Visa deadline sooner than 90-Day?
                if (strcmp(s->visaExpiry, s->report90DayDeadline) < 0)
                {
                    printf("\n[PRIORITY: VISA] Deadline: %s\n", s->visaExpiry);

                    // Only run this if the student is actually on the Visa track
                    if (s->currentStage != NULL && strcmp(s->currentStage->stageName, "Document Collection") == 0)
                    {
                        if (s->docTreeRoot == NULL)
                            s->docTreeRoot = docTree();

                        documentChecklist(s->docTreeRoot);

                        if (isTreeComplete(s->docTreeRoot))
                        {
                            printf("System: All documents verified! Advancing to Immigration Visit...\n");
                            moveToNextStage(s);
                        }
                    }
                }
                else // 90-Day is the more immediate priority
                {
                    printf("\n[PRIORITY: 90-DAY] Deadline: %s\n", s->report90DayDeadline);

                    // Only run this if the student is actually on the 90-Day track
                    if (s->current90DaysStage != NULL && strcmp(s->current90DaysStage->stageName, "90-Day Document Verification") == 0)
                    {
                        if (s->doc90DaysTreeRoot == NULL)
                            s->doc90DaysTreeRoot = docTree90();

                        documentChecklist(s->doc90DaysTreeRoot);

                        if (isTreeComplete(s->doc90DaysTreeRoot))
                        {
                            printf("System: 90-Day Papers verified! Advancing...\n");
                            move90DaysNextStage(s);
                        }
                    }
                }
            }
            else
            {
                printf("Error: Student ID %lld not found in student database.\n", id);
            }
            break;
        case 3:
            return 0;
        }
    }
    return 0;
}