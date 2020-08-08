#include <stdio.h>
#include <sys/socket.h>
#include <string.h>

/*
 #include <netinet/in.h>
 
 struct sockaddr_in {
 short            sin_family;   // e.g. AF_INET
 unsigned short   sin_port;     // e.g. htons(3490)
 struct in_addr   sin_addr;     // see struct in_addr, below
 char             sin_zero[8];  // zero this if you want to
 };
 
 struct in_addr {
 unsigned long s_addr;  // load with inet_aton()
 };
 */

#define SERV_PORT   5193
#define MAXLINE     1024

int main(char *argv, int argc) {
    argc = argc;
    argv = argv;
    
    int sockfd;
    struct sockaddr_in addr;
    char buff[MAXLINE];
    time_t ticks;
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }
    
    memset((void *) &addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERV_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(sockfd, (struct sockaddr_in *) &addr, sizeof(addr)) < 0) {
        perror("bind error");
        exit(1);
    }
    
    while(1) {
        if (recvfrom(sockfd, buff, MAXLINE, 0, (struct sockaddr_in *) &addr, sizeof(addr))) < 0) {
            perror("recv error");
            exit(1);
        }
        
        ticks = time(NULL);
        snprintf(buff, "%.24s/r/n", ctime(ticks);
        if (sendto(sockfd, buff, MAXLINE, 0, (struct sockaddr_in *) &addr, sizeof(addr)) < 0) {
            perror("sendto error");
            exit(1);
       }
    }
    
    exit(0);
}
