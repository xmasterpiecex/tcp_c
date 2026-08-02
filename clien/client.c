#include "stdio.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netinet/ip.h"
#include "arpa/inet.h"
#include "string.h"
#include "unistd.h"

void main(void)
{
    struct sockaddr_in server;
    char serv_ip[] = "127.0.0.1";
    char msg_buff[1024];
    char data[1024];

    server.sin_family = AF_INET;
    server.sin_port = htons(1488);

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    inet_pton(AF_INET, serv_ip, &server.sin_addr);

    int conn = connect(sock, (struct sockaddr *)&server, sizeof(server));

    for (;;)
    {
        char *msg = fgets(msg_buff, sizeof(msg_buff), stdin);
        send(sock, msg, strlen(msg), 0);

        if (read(sock, data, sizeof(data)) > 0)
        {
            printf("%s\n", data);
        }
    }

    close(sock);
}