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

    struct student *next; // Chaining for Hash Table
};


#endif