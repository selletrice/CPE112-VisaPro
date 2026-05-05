#include "visa_pro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stageNode *headStage = NULL; //Global pointer for start or end of the roadmap

void initVisaRoadmap(){
    // Create new nodes for each stage
    struct stageNode *s1 = (struct stageNode*)malloc(sizeof(struct stageNode));
    struct stageNode *s2 = (struct stageNode*)malloc(sizeof(struct stageNode));
    struct stageNode *s3 = (struct stageNode*)malloc(sizeof(struct stageNode));
    struct stageNode *s4 = (struct stageNode*)malloc(sizeof(struct stageNode));
    struct stageNode *s5 = (struct stageNode*)malloc(sizeof(struct stageNode));


    // Name the stages
    strcpy(s1->stageName, "Student Profile Registration");
    strcpy(s2->stageName, "Document Collection");
    strcpy(s3->stageName, "Immigration Visit");
    strcpy(s4->stageName, "Visa Processing");
    strcpy(s5->stageName, "Visa Issued");

    // Link stages together
    s1->next = s2;
    s2->next = s3;
    s3->next = s4;
    s4->next = s5;
    s5->next = NULL;

    // Set stage 1 as the head (very first) stage
    headStage = s1;
}

void startVisaProcess(struct student *s){
    if (headStage == NULL){
        initVisaRoadmap();
    }

    if (s != NULL){
        s->currentStage = headStage;
        printf("Process Started: %s is now at [%s]\n", s->name, s->currentStage->stageName);
    }
}

void renewVisaProcess(struct student *s, char* newExpiry){
    // Update the pointer to point back to the beginning, thus resetting the process
    strncpy(s->visaExpiry, newExpiry, 20);
    s->currentStage = headStage; // Reset the Linked List pointer to Stage 1

    // Member 2 Task: Call a function here to clear their Document Tree
    if (s->docTreeRoot != NULL)
    {
        clearDocumentTree(s->docTreeRoot);
    }

    // Member 3 Task: Update their 90-day reminder Priority Queue

    printf("Visa Renewed for %s. New Expiry: %s. Process restarted.\n", s->name, s->visaExpiry);
}

void moveToNextStage(struct student *s){
    if (s == NULL || s->currentStage == NULL){
        printf("Error: Visa process has not initialized\n");
        return;
    }

    if (s->currentStage->next != NULL){
        s->currentStage = s->currentStage->next;
        printf("SUCCESS! %s moved to stage: %s", s->name, s->currentStage->stageName);
    }
    else{
        printf("PROCESS COMPLETE! %s has already reached the final stage %s", s->name, s->currentStage->stageName);
    }
}

void init90DaysRoadmap(){
    struct stageNode *n1 = (struct stageNode*)malloc(sizeof(struct stageNode));
    struct stageNode *n2 = (struct stageNode*)malloc(sizeof(struct stageNode));
    struct stageNode *n3 = (struct stageNode*)malloc(sizeof(struct stageNode));

    strcpy(n1->stageName, "90-Day Notification Receipt");
    strcpy(n1->stageName, "90-Day Document Verification");
    strcpy(n1->stageName, "90-Day Report Completed");

    n1->next = n2;
    n2->next = n3;
    n3->next = NULL;

    headStage = n1;
}

void start90DaysProcess(struct student *s){
    if (headStage == NULL){
        init90DaysRoadmap();
    }
    if (s != NULL){
        s->currentStage = headStage;
        printf("Process Started: %s is now at [%s]\n", s->name, s->currentStage->stageName);
    }
}

void move90DaysNextStage(struct student *s){
    if (s == NULL || s->currentStage == NULL){
        printf("Error: 90-Days process has not initialized\n");
        return;
    }

    if (s->current90DaysStage != NULL){
        s->current90DaysStage = s->current90DaysStage->next;
        printf("90-DAY SUCCESS: %s moved to: %s\n", s->name, s->current90DaysStage->stageName);
    } else{
        printf("90-DAY COMPLETE: Final stage reached.\n");
    }
}