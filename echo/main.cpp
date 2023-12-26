#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        cout<<"err1\n";
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int rc = bind(listener, (struct sockaddr *)&addr, sizeof(addr));
    if(rc < 0)
    {
        cout<<"err2\n";
    }

    listen(listener, 5);
    
    while(1)
    {
        sockaddr_in * client_addr = new sockaddr_in;
        socklen_t len = sizeof (sockaddr_in);
        sock = accept(listener,  (sockaddr*)(client_addr), &len);
        if(sock < 0)
        {
            cout<<"err3\n";
        }

        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);
            if(bytes_read <= 0) break;
            send(sock, buf, bytes_read, 0);
        }
    
        close(sock);
    }
    
    return 0;
}