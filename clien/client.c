#include "stdio.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netinet/ip.h"
#include "arpa/inet.h"
#include "string.h"
#include "unistd.h"

typedef struct Node
{
    char key[20];
    char data[1024];
    struct Node *next_node;
} Node;

void main(void)
{
    struct sockaddr_in server;
    char serv_ip[] = "127.0.0.1";
    char msg_buff[1024];
    Node node;
    int key;

    server.sin_family = AF_INET;
    server.sin_port = htons(1488);

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    inet_pton(AF_INET, serv_ip, &server.sin_addr);

    int conn = connect(sock, (struct sockaddr *)&server, sizeof(server));

    for (;;)
    {
        char *msg = fgets(msg_buff, sizeof(msg_buff), stdin);
        send(sock, msg, strlen(msg), 0);

        if (read(sock, node.data, sizeof(node.data)) > 0)
        {
            printf("%s\n", node.data);
        }
    }

    close(sock);
}