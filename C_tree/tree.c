#include "stdio.h"
#include "stdlib.h"


typedef struct Node
{
    int val;
    Node *left_node;
    Node *right_node;
} Node;

Node *create_node(int val)
{
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->left_node = NULL;
    node->right_node = NULL;
    return node;
}

Node * insert_node(Node *node, int value)
{
    if (node == NULL)
    {
        return create_node(value);
    }
    
    if (value < node->val)
    {
        insert_node(node->left_node, value);
    } else
    {
        insert_node(node->right_node, value);
    }
    return node;
} 


int main()
{
    Node *tree = NULL;
    tree = insert_node(tree, 4);
    tree = insert_node(tree, 6);
    tree = insert_node(tree, 8);

    printf("hello world\n");
    return 1;
}