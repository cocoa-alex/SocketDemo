//
//  main.c
//  TCP-Time
//
//  Created by Steve on 14-1-23.
//  Copyright (c) 2014年 Steve. All rights reserved.
//

#include "../unp/unp.h"
#include "../unp/apueerror.h"
#include <time.h>

int main(int argc, const char * argv[])
{
    int listenfd,connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;
    
    listenfd=Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(1024);
    
    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));//bind
    
    Listen(listenfd, LISTENQ);
    
    for (; ;) {
        connfd=Accept(listenfd, (SA*)NULL, NULL);
        
        ticks=time(NULL);
        
        snprintf(buff, sizeof(buff), "%.24s\r\n",ctime(&ticks));
        
        Write(connfd, buff, strlen(buff));
        
        Close(connfd);
    }
}

