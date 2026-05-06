#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "visa_pro.h"

// Function to create a new node for a document
struct docNode *createDocumentNode (char document[])
{
    struct docNode *newNode = (struct docNode *)malloc(sizeof(struct docNode));

    if (newNode != NULL)
    {
        strncpy(newNode->docName, document, MAX);   // safely copying string into fixed-size array
        newNode->docName[MAX - 1] = '\0';           // to ensure string ends safely
        newNode->isCollected = 0;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

// Tree architecture
struct docNode *docTree()
{
    // Final goal
    struct docNode *root = createDocumentNode("Visa Support Letter");

    // Documents required to request for visa support letter:
    // Branch 1: documents to prepare by yourself
    struct docNode *selfPrep = createDocumentNode("Self-Prepared Documents");
    root->left = selfPrep;

    // Sub-branch for identity and fees
    struct docNode *identity = createDocumentNode("Identity and Fees");
    selfPrep->right = identity;
    identity->left = createDocumentNode("Original Passport");
    identity->left->left = createDocumentNode("Passport Copies (Bio/Visa/Last Arrival Stamp)");

    // Sub-branch for forms
    selfPrep->left = createDocumentNode("Forms");
    selfPrep->left->left = createDocumentNode("Immigration Form 7 (TM.7)");
    selfPrep->left->right = createDocumentNode("Overstay Penalty Form");
    selfPrep->left->left->left = createDocumentNode("TM.30 Notification");

    struct docNode *miscellenous = createDocumentNode("Photos and Fees");
    identity->right = miscellenous;
    miscellenous->left = createDocumentNode("Photos(4 x 6 cm)");
    miscellenous->right = createDocumentNode("Application Fee (1,900 Baht)");

    // Branch 2: Office Documents (IA and RO)
    struct docNode *officeDocs = createDocumentNode("University Office Documents");
    root->right = officeDocs;

    // IA office branch
    officeDocs->left = createDocumentNode("IA Office (2nd Floor N2)");
    officeDocs->left->left = createDocumentNode("Certified KMUTT Request Letter");
    
    // Registrar's office (RO) branch
    struct docNode *roOffice = createDocumentNode("Registrar's Office (THE HUB)");
    officeDocs->right = roOffice;
    roOffice->left = createDocumentNode("Transcript or E-Transcript");

    struct docNode *roMisc = createDocumentNode("Enrollment and Status");
    roOffice->right = roMisc;
    roMisc->left = createDocumentNode("Tution Fee Receipt");
    roMisc->right = createDocumentNode("Certificate of student status");

    return root;
}


// List out missing documents (Member 3)
void listMissingDocuments(struct docNode *root) {
    if (root == NULL) return;

    // Traverse the tree to find uncollected nodes
    listMissingDocuments(root->left);
    listMissingDocuments(root->right);

    // Update conditions
    // Must match the display conditions in documentChecklist exactly
    if ((root->left == NULL && root->right == NULL) || 
        (strcmp(root->docName, "Immigration Form 7 (TM.7)") == 0) || 
        (strcmp(root->docName, "Original Passport") == 0) ||
        (strcmp(root->docName, "TM. 47 (Notification for staying longer than 90 days)") == 0)) 
    {
        if (root->isCollected == 0) {
            printf("   >> [%s]\n", root->docName);
        }
    }
}

// Interactive checklist for documents
void documentChecklist(struct docNode *root)
{
    if (root == NULL) return;

    // Post-order traversal
    documentChecklist(root->left);
    documentChecklist(root->right);
    
    // Leaf node logic
    /**
     * DOCUMENT DISPLAY LOGIC: (written by Member 3)
     * 1. Default: Only "Leaf Nodes" (nodes without children) are displayed as checklist items.
     * 2. Parent Nodes: Usually act as group headers/categories and are hidden to avoid duplication.
     * 3. Special Exceptions: "Original Passport", "TM.7", and "TM.47" are forced to display via strcmp 
     *    because they require individual verification despite having child nodes.
     */
    if ((root->left == NULL && root->right == NULL) || 
        (strcmp(root->docName, "Immigration Form 7 (TM.7)") == 0) ||
        (strcmp(root->docName, "Original Passport") == 0)||
        (strcmp(root->docName, "TM. 47 (Notification for staying longer than 90 days)") == 0)) 
    {
        printf("Verification: Have you obtained [%s]? (Yes = 1 : No = 0): ", root->docName);
        scanf("%d", &root->isCollected);
    }
    
    // Parent node
    else
    {
        // Automatically calculate status based on children
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

struct docNode *docTree90 ()
{
    struct docNode *root = createDocumentNode("TM. 47 (Notification for staying longer than 90 days)");
    root->left = createDocumentNode("TM. 30 Notification");
    root->right = createDocumentNode("Original Passport");
    return root;
};

// Final verification: returns 1 only if the entire tree is successfully collected

int isTreeComplete(struct docNode *root)
{
    if (root == NULL) return 1;
    int leftTree = isTreeComplete(root->left);
    int rightTree = isTreeComplete(root->right);

    // Checks if sub-trees are complete & current root is collected
    if (leftTree && rightTree && root->isCollected == 1)
    {
        return 1;
    }

    return 0;
}

// Function to clear the document tree status

// Called by renewVisaProcess in process_manager.c when student restarts the process
void clearDocumentTree(struct docNode *root)

{
    if (root == NULL) return;

    // Post-order traversal: visit children before root

    clearDocumentTree(root->left);
    clearDocumentTree(root->right);
    // Reset document collection status to 0 (not collected)
    root->isCollected = 0;
}

// Function to avoid memory leak

void deleteDocumentTree(struct docNode *root)
{
    if (root == NULL)
    return;

    // Post-order traversal
    deleteDocumentTree(root->left);
    deleteDocumentTree(root->right);
    free(root);

}