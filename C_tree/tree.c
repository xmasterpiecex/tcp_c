#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

typedef struct Node
{
    char *value;
    char *key;
    struct Node *left_node;
    struct Node *right_node;
} Node;

typedef struct List
{
    Node *root;
} List;

List *create_list()
{
    List *list = malloc(sizeof(List));
    if (list == NULL)
        return NULL;

    list->root = NULL;
    return list;
}

Node *create_node(char *value, char *key)
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->key = key;
    node->left_node = NULL;
    node->right_node = NULL;
    return node;
}
bool _insert_node(List *l, Node *node)
{
    if (node == NULL || l == NULL)
    {
        return false;
    }
    l->root = node;
    return true;
}

void delete_node(Node *n)
{
    free(n);
}

bool insert_node(List *root, char *value, char *key)
{
    if (root == NULL)
    {
        return false;
    }
    
    Node *curr_node = root->root;

    if (root->root == NULL)
    {
        root->root = create_node(value, key);
        return true;
    }

    while (curr_node != NULL)
    {
        int decider = strcmp(key, curr_node->key);

        if (decider == 0)
            return false;

        Node **child = decider < 0 ? &curr_node->left_node : &curr_node->right_node;

        if ((*child) == NULL)
        {
            (*child) = create_node(value, key);
            return true;
        }
        curr_node = *child;
    }
    return _insert_node(root, create_node(value, key));
}

void delete_list(List *list)
{
    Node *stack_buff[1000];
    memset(stack_buff, 0, sizeof(stack_buff));
    Node **stack_end = stack_buff;

    *stack_end = list->root;
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
    free(list);
}

int main()
{
    List *tree = create_list();
    insert_node(tree, "val1", "root node");
    insert_node(tree, "ahha val", "some node");
    insert_node(tree, "valhehe", "lala node");

    // delete_tree(tree);

    printf("root node key: %s", tree->root->key);

    return 1;
}