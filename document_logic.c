#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "visa_pro.h"

//function to create a new node for new document
struct docNode *createDocumentNode (char document[])
{
    struct docNode *newNode = (struct docNode *)malloc(sizeof(struct docNode));

    if (newNode != NULL)
    {
        strncpy(newNode->docName, document, MAX);   //safely copying string into fixed-size array
        newNode->docName[MAX - 1] = '\0';           //to ensure string ends safely
        newNode->isCollected = 0;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

//tree architecture
struct docNode *docTree()
{
    struct docNode *root = createDocumentNode("Visa Support Letter");

    //Registrar Branch 
    root->left = createDocumentNode("Registrar's Office Documents");
    root->left->left = createDocumentNode("Transcript");
    root->left->right = createDocumentNode("Certificate of student Status");

    //IA Branch
    root->right = createDocumentNode("IA Documents");
    root->right->left = createDocumentNode("Certified Request Letter");

    //more nodes/documents to add later

    return root;
}

//interactive checklist for documents
void documentChecklist(struct docNode *root)
{
    if (root == NULL) return;

    //post-order transversal
    documentChecklist(root->left);
    documentChecklist(root->right);

    //leaf node
    if (root->left == NULL && root->right == NULL)
    {
        printf("Verification: Have you obtained [%s]? (Yes = 1 : No = 0)", root->docName);
        scanf("%d", &root->isCollected);
    } 
    //parent node
    else 
    {
        if (root->left != NULL && root->right != NULL)
        {
            //checks if sub-requirements are obtained
            root->isCollected = (root->left->isCollected && root->right->isCollected);
        } 
        else if (root->left != NULL)
        {
            root->isCollected = root->left->isCollected;
        } 
        else if (root->right != NULL)
        {
            root->isCollected = root->right->isCollected;
        }
    }
}

//final verification: returns 1 only if the entire tree is succesfully collected
int isTreeComplete(struct docNode *root)
{
    if (root == NULL) return 1;

    int leftTree = isTreeComplete(root->left);
    int rightTree = isTreeComplete(root->right);

    //checks if sub-trees are complete & current root is collected
    if (leftTree && rightTree && root->isCollected == 1)
    {
        return 1;
    }

    return 0;
}

//function to clear the document tree status
//called by renewVisaProcess in process_manager.c when student restarts the process
void clearDocumentTree(struct docNode *root)
{
    if (root == NULL) return;

    //post-order transversal: visit children before root 
    clearDocumentTree(root->left);
    clearDocumentTree(root->right);

    //reset document collection status to 0 (not collected)
    root->isCollected = 0;
}
