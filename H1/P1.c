#include <stdio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define SIZE 128
#define DEBUG 0

typedef struct stack_elem{
    char* value;
    struct stack_elem* next;
}s_node;

s_node* push(s_node* head, char* value);
s_node* pop(s_node* head);

int main (int argc, char* argv[])
{
    FILE * fp;
    char in_line[SIZE];

    if(argc == 2)
    {

    }
    else
        fp = fopen("test.txt", "r");
    
    if (fp == NULL)
    {
        exit(0);
    }
    
    s_node* head;
    head = (s_node*) NULL;
    
    //Read each line of the file, and print it to screen
    while(fgets(in_line, SIZE, fp) != NULL)
    {   
        char* line = (char*) malloc(sizeof(in_line));
        strcpy(line,in_line);
        if(DEBUG)
            printf("%s", line);
        head = push(head,line);
    }
    if(DEBUG)
        printf("\nNow in reverse\n\n");
    
    while(head != NULL)
    {
        printf("%s",head->value);
        head = pop(head);
    }
    free(head);
    close(fp);
    free(fp);
    return 0;
}

s_node* push(s_node* head, char* value)
{
    s_node* new_head = (s_node*) malloc(sizeof(s_node));
    new_head->value = value;
    new_head->next = head;
    return new_head;
}

s_node* pop(s_node* head)
{
    if(head != NULL)
    {
        s_node* ret_val = head->next;
        free(head->value);
        free(head);
        return ret_val;
    }
    return head;
}
