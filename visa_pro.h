#ifndef VISA_PRO_H
#define VISA_PRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

// Member 3: Deadline Thresholds
#define VISA_NOTICE   90
#define VISA_WARNING  45
#define VISA_CRITICAL 15
#define REPORT_NOTICE   14
#define REPORT_WARNING  7
#define REPORT_CRITICAL 3


// Node for Student Profile and Hashing
struct stageNode{
    char stageName[MAX];
    struct stageNode *next;
};

// Node for Tree
struct docNode{
    char docName[MAX];
    int isCollected; // 0 for false, 1 for true
    struct docNode *right;
    struct docNode *left;
};

// The Student Profile
struct student{
    long long id;
    char name[MAX];
    char visaExpiry[20]; // YYYY-MM-DD
    char report90DayDeadline[20]; // 90-Day Timer

    struct stageNode *currentStage; // Member 1: Points to current Linked List node
    struct stageNode *current90DaysStage; 

    struct docNode *docTreeRoot; // Member 2: Points to root of Document Tree
    struct docNode *doc90DaysTreeRoot;

    struct docNode *report90TreeRoot; //For 90-Day Reporting

    struct student *next; // Chaining for Hash Table
};

// Member 1: From student_db.c

void displayHeader();

void initTable();
void insertStudent(long long id, char* name, char* visaEx, char* reportEx); // new update
struct student* searchStudent(long long id);

// Member 1: From process_manager.c

// Visa 
void initVisaRoadmap();
void startVisaProcess(struct student *s);
void moveToNextStage(struct student *s);
void renewVisaProcess(struct student *s, char* newExpiry);

// 90-Days
void init90DaysRoadmap();
void start90DaysProcess(struct student *s);
void move90DaysNextStage(struct student *s);

//Member 2: From document_logic.c
struct docNode *createDocumentNode(char document[]);
struct docNode *docTree();
void documentChecklist(struct docNode *root);;
int isTreeComplete(struct docNode *root);
void clearDocumentTree(struct docNode *root);
void deleteDocumentTree(struct docNode *root);

// Member 3: Deadline and Checklist Updating
int getDaysRemaining(char* dateStr);
void checkDeadlinesAndProcess(struct student *s);
struct docNode *docTree90();
struct docNode *docTree();
void resetStatus(struct docNode *node);
void listMissingDocuments(struct docNode *root);
void handleChecklistProgress(struct student *s, int type);

#endif 