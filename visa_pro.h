#ifndef VISA_PRO_H
#define VISA_PRO_H

#define MAX 100

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
    struct docNode *docTreeRoot; // Member 2: Points to root of Document Tree
    struct docNode *report90TreeRoot; //For 90-Day Reporting

    struct student *next; // Chaining for Hash Table
};

// Member 1: From student_db.c
void initTable();
void insertStudent(long long id, char* name);
struct student* searchStudent(long long id);

// Member 1: From process_manager.c
void initVisaRoadmap();
void startVisaProcess(struct student *s);
void moveToNextStage(struct student *s);
void renewVisaProcess(struct student *s, char* newExpiry);

//Member 2: From document_logic.c
struct docNode *createDocumentNode(char document[]);
struct docNode *docTree();
void documentChecklist(struct docNode *root);;
int isTreeComplete(struct docNode *root);
void clearDocumentTree(struct docNode *root);
void deleteDocumentTree(struct docNode *root);


// Future Functions from other members should be included below


#endif