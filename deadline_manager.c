#include "visa_pro.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Member 3 Task
/**
 * Structure representing a node in the Priority Queue.
 * It stores a pointer to the student, the specific task description,
 * and the calculated days remaining (which serves as the priority key).
 */
struct PriorityQueueNode {
    struct student *studentData;
    char taskName[50];
    int daysRemaining;
    struct PriorityQueueNode *next;
};

/**
 * Global or local head pointer for the Priority Queue.
 * Lower daysRemaining values have HIGHER priority (Min-Heap / Ascending Linked List behavior).
 */
struct PriorityQueueNode *pqHead = NULL;

/**
 * Inserts a task into the Priority Queue sorted by urgency (ascending order of days remaining).
 */
void enqueuePriority(struct student *s, const char *task, int days) {
    struct PriorityQueueNode *newNode = (struct PriorityQueueNode *)malloc(sizeof(struct PriorityQueueNode));
    if (newNode == NULL) return;

    newNode->studentData = s;
    strcpy(newNode->taskName, task);
    newNode->daysRemaining = days;
    newNode->next = NULL;

    // Case 1: Queue is empty OR new node has higher urgency (fewer days remaining) than the head
    if (pqHead == NULL || days < pqHead->daysRemaining) {
        newNode->next = pqHead;
        pqHead = newNode;
    } else {
        // Case 2: Traverse and insert at the correct position to maintain priority order
        struct PriorityQueueNode *current = pqHead;
        while (current->next != NULL && current->next->daysRemaining <= days) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

/**
 * Optional Helper: Clears the queue memory after processing to prevent memory leaks.
 */
void freePriorityQueue() {
    struct PriorityQueueNode *current = pqHead;
    while (current != NULL) {
        struct PriorityQueueNode *temp = current;
        current = current->next;
        free(temp);
    }
    pqHead = NULL;
}
// ============================================================================

/**
 * Displays the application banner
 */
void displayHeader() {
    printf("\n******************************************\n");
    printf("*               VISAPRO                  *\n");
    printf("*      VISA & 90-DAY TRACKING SYSTEM     *\n");
    printf("*      Computer Engineering Project      *\n");
    printf("******************************************\n");
}

/**
 * Calculates the number of days between today and a given date string (YYYY-MM-DD)
 */
int getDaysRemaining(char* dateStr) {
    if (dateStr == NULL || strlen(dateStr) < 10) return -999;
    struct tm expiry = {0};
    int y, m, d;
    
    // Parse the date string
    if (sscanf(dateStr, "%d-%d-%d", &y, &m, &d) != 3) return -999;
    
    // Basic date validation
    if (y < 0 || m < 1 || m > 12 || d < 1 || d > 31) return -999;

    expiry.tm_year = y - 1900; // Years since 1900
    expiry.tm_mon = m - 1;     // Months 0-11
    expiry.tm_mday = d;
    expiry.tm_isdst = -1;      // Determine daylight savings automatically
    
    time_t now = time(NULL);
    time_t expTime = mktime(&expiry);
    
    // Validation check for month overflow (e.g., Feb 31st)
    if (expTime == -1 || expiry.tm_mon != (m - 1)) return -999;
    
    double seconds = difftime(expTime, now);
    return (int)(seconds / (60 * 60 * 24));
}

/**
 * Manages the checklist interaction for either Visa or 90-Day report
 */
void handleChecklistProgress(struct student *s, int type) {
    // Select the appropriate root based on type: 1 for Visa, 2 for 90-Day
    struct docNode *root = (type == 1) ? s->docTreeRoot : s->doc90DaysTreeRoot;
    char *typeName = (type == 1) ? "Visa Extension" : "90-Day Report";

    // Initialize 90-day tree if it hasn't been created yet
    if (type == 2 && root == NULL) {
        s->doc90DaysTreeRoot = docTree90();
        root = s->doc90DaysTreeRoot;
    }

    printf("\n--- %s DOCUMENT CHECKLIST ---\n", typeName);

    // Call Member 2's checklist interaction logic
    documentChecklist(root); 

    if (isTreeComplete(root)) {
        printf("\nSUCCESS: All documents for %s are verified!\n", typeName);
    } else {
        printf("\nINCOMPLETE: You are still missing the following documents for %s:\n", typeName);
        
        // Call Member 2's helper function to list specific missing items
        listMissingDocuments(root); 

        printf("\nSYSTEM: Your progress has been saved. Please gather these items and run the Scheduler again.\n");
    }
}

/**
 * Analyzes current deadlines and prompts the user for action if deadlines are close
 */
void checkDeadlinesAndProcess(struct student *s) {
    if (s == NULL) return;

    int vDays = getDaysRemaining(s->visaExpiry);
    int rDays = getDaysRemaining(s->report90DayDeadline);

    // ------------------------------------------------------------------------
    // ENQUEUEING INTO THE PRIORITY QUEUE
    // Automatically dynamic sort tasks by urgency without affecting execution flow
    // ------------------------------------------------------------------------
    enqueuePriority(s, "Visa Extension", vDays);
    enqueuePriority(s, "90-Day Report", rDays);
    // ------------------------------------------------------------------------

    printf("\n--- DEADLINE ANALYSIS FOR %s ---\n", s->name);

    // Handle expired cases
    if (vDays < 0 || rDays < 0) {
        if (vDays < 0) printf("[ERROR]: Visa has EXPIRED for %d days!\n", abs(vDays));
        if (rDays < 0) printf("[ERROR]: 90-Day Report is OVERDUE for %d days!\n", abs(rDays));
        printf("The system will now exit due to legal expiration status.\n");
        
        freePriorityQueue(); // Clean up before exit
        return; 
    }

    // Display Visa Status using priority thresholds
    printf("Visa Status: ");
    if (vDays <= 7) printf("[CRITICAL] %d days left!\n", vDays);
    else if (vDays <= 14) printf("[WARNING] %d days left.\n", vDays);
    else if (vDays <= 30) printf("[NOTICE] %d days left.\n", vDays);
    else printf("Safe (%d days remaining).\n", vDays);

    // Display 90-Day Status using priority thresholds
    printf("90-Day Status: ");
    if (rDays <= 3) printf("[CRITICAL] %d days left!\n", rDays);
    else if (rDays <= 7) printf("[ALERT] %d days left.\n", rDays);
    else if (rDays <= 15) printf("[REMINDER] %d days left.\n", rDays);
    else printf("Safe (%d days remaining).\n", rDays);

    // Check if user is in the "Safe Zone"
    if (vDays > 30 && rDays > 15) {
        printf("\nYou are in the safe zone. No immediate action required.\n");
        freePriorityQueue(); // Clean up queue memory
        return; 
    }

    // Interactive Menu for immediate action
    printf("\n!!! ACTION REQUIRED !!!\n");
    printf("Select Process: \n");
    printf("[1] Process Visa Extension Checklist\n");
    printf("[2] Process 90-Day Report Checklist\n");
    printf("[3] Process Both\n");
    
    int choice;
    printf("Enter choice (1-3): ");
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n'); // Clear invalid input buffer
        freePriorityQueue();
        return;
    }
    getchar(); // Clear trailing newline from buffer

    switch (choice) {
        case 1: 
            handleChecklistProgress(s, 1); 
            break;
        case 2: 
            handleChecklistProgress(s, 2); 
            break;
        case 3: 
            handleChecklistProgress(s, 1); 
            printf("\n--- Press Enter to continue to 90-Day Checklist ---\n");
            getchar(); 
            handleChecklistProgress(s, 2); 
            break;
        default: 
            printf("Invalid selection.\n"); 
            break;
    }

    freePriorityQueue(); // Clean up queue memory at the end of the process
}