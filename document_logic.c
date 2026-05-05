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
    //final goal
    struct docNode *root = createDocumentNode("Visa Support Letter");

    //documents required to request for visa support letter:
   //branch 1: documents to prepare by yourself
   struct docNode *selfPrep = createDocumentNode("Self-Prepared Documents");
   root->left = selfPrep;

   //sub-branch for identity and fees
   struct docNode *identity = createDocumentNode("Identity and Fees");
   selfPrep->right = identity;
   identity->left = createDocumentNode("Original Passport");
   identity->left->left = createDocumentNode("Passport Copies (Bio/Visa/Last Arrival Stamp)");

   //sub-branch for forms
   selfPrep->left = createDocumentNode("Forms");
   selfPrep->left->left = createDocumentNode("Immigration Form 7 (TM.7)");
   selfPrep->left->right = createDocumentNode("Overstay Penalty Form");
   selfPrep->left->left->left = createDocumentNode("TM.30 Notification");

   struct docNode *miscellenous = createDocumentNode("Photos and Fees");
   identity->right = miscellenous;
   miscellenous->left = createDocumentNode("Photos(4 x 6 cm)");
   miscellenous->right = createDocumentNode("Application Fee (1,900 Baht)");

   //branch 2: Office Documents (IA and RO)
   struct docNode *officeDocs = createDocumentNode("University Office Documents");
   root->right = officeDocs;

   //IA office branch
   officeDocs->left = createDocumentNode("IA Office (2nd Floor N2)");
   officeDocs->left->left = createDocumentNode("Certified KMUTT Request Letter");
   
   //registrar's office (RO) branch
   struct docNode *roOffice = createDocumentNode("Registrar's Office (THE HUB)");
   officeDocs->right = roOffice;
   roOffice->left = createDocumentNode("Transcript or E-Transcript");

   struct docNode *roMisc = createDocumentNode("Enrollment and Status");
   roOffice->right = roMisc;
   roMisc->left = createDocumentNode("Tution Fee Receipt");
   roMisc->right = createDocumentNode("Certificate of student status");

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
        //automatically calculate status based on children
        if (root->left != NULL && root->right != NULL)
        {
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

//to avoid memory leak
void deleteDocumentTree(struct docNode *root)
{
    if (root == NULL) 
    return;

    //post-order transversal
    deleteDocumentTree(root->left);
    deleteDocumentTree(root->right);

    free(root);
}
