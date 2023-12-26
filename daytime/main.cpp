#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
 
int main()
{
    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_socket == -1)
    {
        exit(0);
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(7777);
    server.sin_addr.s_addr = inet_addr("172.16.40.1");
    
    if(connect(client_socket, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        std::cout<<"Error : Connect Failed \n";
        exit(0);
    }
        
	char buf[128];
    sendto(client_socket, (void*)"daytime", sizeof("daytime"), 0 , (sockaddr*)&server, sizeof(sockaddr_in));
    recvfrom(client_socket, buf, sizeof(buf), 0, NULL, NULL);
    std::cout<<"Daytime: "<<std::string(buf)<<std::endl;
    close(client_socket);
 
    return 0;
}