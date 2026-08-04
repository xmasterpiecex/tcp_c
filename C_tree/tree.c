#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct Node
{
    int value;
    struct Node *left_node;
    struct Node *right_node;
} Node;

Node *create_node(int value)
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left_node = NULL;
    node->right_node = NULL;
    return node;
}

Node *insert_node(Node *root, int value)
{
    Node *curr_node = root;

    if (root == NULL)
        return create_node(value);
    while (curr_node != NULL)
    {
        Node **child = value < curr_node->value ? &curr_node->left_node : &curr_node->right_node;

        if ((*child) == NULL)
        {
            (*child) = create_node(value);
            break;
        }

        curr_node = *child;
    }
    return root;
}

void delete_tree(Node *root)
{
    Node *stack_buff[1000];
    memset(stack_buff, 0, sizeof(stack_buff));
    Node **stack_end = stack_buff;
    
    *stack_end = root;
    stack_end++;

    while (stack_buff != stack_end)
    {
        Node *curr_node = *(--stack_end);
        *stack_end = NULL;
        if (curr_node->left_node != NULL)
        {
            *stack_end = curr_node->left_node;
            stack_end++;
        }
        if (curr_node->right_node != NULL)
        {
            *stack_end = curr_node->right_node;
            stack_end++;
        }
        free(curr_node);
    }
}

int main()
{
    Node *tree = NULL;
    tree = insert_node(tree, 6);
    tree = insert_node(tree, 4);
    tree = insert_node(tree, 8);

    delete_tree(tree);

    return 1;
}