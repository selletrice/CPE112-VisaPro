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

    // Name the stages
    strcpy(s1->stageName, "Student Profile Registration");
    strcpy(s2->stageName, "Document Collection");
    strcpy(s3->stageName, "Immigration Visit");
    strcpy(s4->stageName, "Visa Issued");

    // Link stages together
    s1->next = s2;
    s2->next = s3;
    s3->next = s4;
    s4->next = NULL;

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
        printf("Error: Student process has not initialized\n");
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