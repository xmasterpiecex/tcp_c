#include "stdio.h"
#include "stdlib.h"


typedef struct Node
{
    int value;
    Node *left_node;
    Node *right_node;
} Node;

Node *create_node(int value)
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left_node = NULL;
    node->right_node = NULL;
    return node;
}

Node * insert_node(Node *root, int value)
{
    Node *curr_node = root;

    if (root == NULL) return create_node(value);
    while(curr_node != NULL)
    {
        if (value < curr_node->value)
        {
            if (curr_node->left_node == NULL)
            {
                curr_node->left_node = create_node(value);
                break;
            }
            curr_node = curr_node->left_node; 
            
        } else
        {
            if (curr_node->right_node == NULL)
            {
                curr_node->right_node = create_node(value);
                break;
            }
            curr_node = curr_node->right_node; 
        }
    }
    return root;
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