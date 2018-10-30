#include <stdio.h>
#include <stdlib.h>
#include<string.h>
struct tree_element
{
    char name[20];
    int ftype, nc, level;
    struct tree_element *link[5];
};
typedef struct tree_element
    node;
void create(node **root, int lev, char *dname) {
    int i, gap;
    if (*root == NULL)
    {
        (*root) = (node *)malloc(sizeof(node));
        printf("\nEnter 1 for Directory / 2 for File :");
        scanf("%d", &(*root)->ftype);
        if ((*root)->ftype == 1) 
            printf("Enter name of directory (under %s) :", dname);
        else 
            printf("Enter name of file (under %s) :", dname);
        scanf("%s", (*root)->name);
        (*root)->level = lev;
        for (i = 0; i < 5; i++)
            (*root)->link[i] = NULL;
        // If it is a directory
        if ((*root)->ftype == 1)
        {
            printf("No of sub-directories/files (for %s):", (*root)->name);
            scanf("%d", &(*root)->nc);
            for (i = 0; i < (*root)->nc; i++)
                create(&((*root)->link[i]), lev + 1, (*root)->name);
        }
        else
            (*root)->nc = 0;
    }
}
void display(node **root) {
    int i;
    if (*root != NULL) {
        // If it is a directory
        if ((*root)->ftype == 1)
        {
            for (i=0; i<(*root)->level; i++) printf("\t");
            printf("-%s\n", (*root)->name);
            for (i = 0; i < (*root)->nc; i++)
                display(&((*root)->link[i]));
        }
        else {
            for (i=0; i<(*root)->level; i++) printf("\t");
            printf("--%s\n", (*root)->name);
        }
    }
}
int search(node **root, char *name) {
    int i,f;
    if (*root != NULL) {
        if (strcmp(name, (*root)->name) == 0) return 1;
        for (i = 0; i < (*root)->nc; i++){ f = search(&((*root)->link[i]), name);
            if(f) return 1;}
    }

    return 0;
}
void delete(node **root, char *name) {
    int i;
    if (*root != NULL) {
        if (strcmp(name, (*root)->name) == 0) {
            for (i = 0; i < (*root)->nc; i++) free((*root)->link[i]);
            free(*root);
        }
        else for (i = 0; i < (*root)->nc; i++) delete(&((*root)->link[i]), name);
    }
}
void main()
{
    int i;
    char name[20];
    node *root;
    root = NULL;
    create(&root, 0, "root");
    display(&root);  
    printf("1. Search\n2. Delete\n");
    scanf("%d", &i);
    if (i == 1) {
        printf("Enter file/directory name: \n");
        scanf("%s", name);
        if (search(&root, name) == 1) printf("Found");
        else printf("Not found");
    }
    else {
        printf("Enter file/directory name: ");
        scanf("%s", name);
        delete(&root, name);
        display(&root);
    }
}