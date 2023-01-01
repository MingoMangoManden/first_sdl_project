#include <stdio.h>
#include <stdlib.h>

struct node
{
    int num;
    struct node* next;
};
typedef struct node node;

void ll_traverse(node* head)
{
    node* current_node = head;
    int indx = 0;

    while (current_node != NULL)
    {
        printf("%i | %i\n", indx, current_node->num);
        current_node = current_node->next;
        indx++;
    }
}

int ll_size(node* head)
{
    node* current_node = head;
    int size = 0;

    while (current_node != NULL)
    {
        size += 1;
        current_node = current_node->next;
    }

    return size;
}

void ll_insert_end(node* n, node* head)
{
    node* current_node = head;
    
    while (current_node != NULL)
    {
        if (current_node->next == NULL)
            break;
        current_node = current_node->next;
    }

    current_node->next = n;
}

// TODO: Test & make sure it doesn't break the chain of data
void ll_insert_at(int a, node* n, node* head)
{
    node* current_node = head;
    int indx = 0;
    
    while (current_node != NULL)
    {
        if (current_node->next == NULL || indx == a)
            n->next = current_node->next;
            current_node->next = n;
            break;
        current_node = current_node->next;
        indx++;
    }
}

// TODO: Test
void ll_remove(int data, node* head)
{
    node* current_node = head;
    node* prev_node = (node*) malloc(sizeof(node*));

    while (current_node != NULL)
    {
        if (current_node->num == data)
        {
            prev_node->next = current_node->next;
            break;
        }

        current_node = current_node->next;
    }
}

int main()
{
    struct node f = { 25 };
    struct node s = { 25 };
    struct node t = { 50 };
    struct node fo = { 45 };

    ll_insert_end(&s, &f);
    ll_insert_end(&t, &f);
    ll_insert_end(&fo, &f);


    //printf("Size of Linked List : %i\n", ll_size(&f));
    ll_traverse(&f);

    return 0;
}
