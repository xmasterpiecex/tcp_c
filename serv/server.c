#include "stdio.h"
#include "stdlib.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netinet/ip.h"
#include "string.h"
#include "arpa/inet.h"
#include "unistd.h"
#include "assert.h"

typedef struct Node
{
    char key[20];
    char data[1024];
    struct Node *next_node;
} Node;

typedef struct List
{
    Node *head;
    Node *tail;
} List;

Node *create_node()
{
    Node *node = malloc(sizeof(Node));
    memset(node, 0, sizeof(Node));
    return node;
};

List *create_list()
{
    List *list = malloc(sizeof(List));
    memset(list, 0, sizeof(List));
    return list;
};

void delete_node(Node *node)
{
    free(node);
}

void delete_list(List *list)
{
    for (Node *i = list->head; i != NULL; i = i->next_node)
    {
        delete_node(i);
    }
    free(list);
}

void push_node(List *list, Node *node)
{
    assert(list != NULL);
    assert(node != NULL);

    if (list->head == NULL && list->tail == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next_node = node;
        list->tail = node;
    }
}

void fill_node(Node *node, const char *key, const char *data)
{
    assert(node != NULL);
    assert(key != NULL);
    assert(data != NULL);

    strncpy(node->key, key, sizeof(node->key));
    strncpy(node->data, data, sizeof(node->data));
}

void delete_node_by_key(List *list, const char *key)
{
    Node *i = list->head;
    Node *prev = NULL;

    while (i != NULL)
    {
        if (strncmp(i->key, key, sizeof(i->key)) == 0)
        {
            if (prev == NULL)
            {
                list->head = i->next_node;
            }
            else
            {
                prev->next_node = i->next_node;
            }
            delete_node(i);
            break;
        }
        prev = i;
        i = i->next_node;
    }
}

Node *get_node_by_key(List *list, const char *key)
{
    for (Node *i = list->head; i != NULL; i = i->next_node)
    {
        if (strncmp(key, i->key, sizeof(i->key)) == 0)
        {
            return i;
        }
    }
    return NULL;
}

int main()
{
    struct sockaddr_in client;
    struct sockaddr_in server;
    socklen_t len;
    char msg_buff[1024];
    char client_ip[INET_ADDRSTRLEN];
    char command[4];

    List *my_list = create_list();

    Node *test_node = create_node();
    Node *second_node = create_node();
    Node *more_node = create_node();

    fill_node(test_node, "fizz", "bazz");
    fill_node(second_node, "sec", "kill bill");
    fill_node(more_node, "more", "this is third node");

    push_node(my_list, test_node);
    push_node(my_list, second_node);
    push_node(my_list, more_node);

    server.sin_family = AF_INET;
    server.sin_port = htons(1488);
    server.sin_addr.s_addr = INADDR_ANY;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int bd = bind(sock, (struct sockaddr *)&server, sizeof(server));

    if (bd < 0)
    {
        printf("[X] ERROR: Binding not working");
        return -1;
    }

    if (listen(sock, 50) < 0)
    {
        perror("[X] ERROR: Server side - listen not working :");
    }

    len = sizeof(client);
    int cl_fd = accept(sock, (struct sockaddr *)&client, &len);

    while (1)
    {
        inet_ntop(AF_INET, &client.sin_addr, client_ip, sizeof(client_ip));

        if (cl_fd < 0)
        {
            perror("[X]ERROR: Accept stage not work properly");
            return -1;
        }

        int msg_d = recv(cl_fd, msg_buff, sizeof(msg_buff) - 1, 0);

        if (msg_d <= 0)
        {
            break;
        }
        msg_buff[msg_d] = '\0';

        sscanf(msg_buff, "%3s", command);

        if (strncmp(command, "get", 4) == 0)
        {
            char key[20];
            sscanf(msg_buff, "%*s %s", key);
            Node *node = get_node_by_key(my_list, key);
            if (node)
            {
                write(cl_fd, node->data, sizeof(node->data));
            }
            else
            {
                write(cl_fd, "key is not found", 17);
            }
        }
        else if (strncmp(command, "del", sizeof(command)) == 0)
        {
            char key[20];
            sscanf(msg_buff, "%*s %s", key);
            delete_node_by_key(my_list, key);
            write(cl_fd, "deleted\n", 9);
        }
        else if (strncmp(command, "add", sizeof(command)) == 0)
        {
            char key[20];
            char data[1024];

            sscanf(msg_buff, "%*s %19s %1023[^\n]", key, data);
            Node *new_node = create_node();
            fill_node(new_node, key, data);
            push_node(my_list, new_node);

            write(cl_fd, "node is created", 16);
        }
        else
        {
            write(cl_fd, "OK", 3);
        }

    }
    return 0;
}

// void delete_node_by_key(List *list, const char *key)
// {
//     Node **link = &list->head;

//     while (*link != NULL)
//     {
//         if (strcmp((*link)->key, key) == 0)
//         {
//             Node *tmp = *link;
//             *link = tmp->next_node;
//             delete_node(tmp);
//             return;
//         }

//         link = &(*link)->next_node;
//     }
// }