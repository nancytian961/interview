#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char** argv)
{
    int sockfd,recvbytes,res,flags,error=-1,n;
    socklen_t len;
    fd_set rset,wset;
    struct timeval tval;
    struct sockaddr_in serv_addr;
    char* sendData="1234567890";//发送字符串
    char buf[1024]="/0"; //接收buffer
    //创建socket描述符
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket create failed");
        return 1;
    }

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(9999);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bzero(&(serv_addr.sin_zero),8);
    flags=fcntl(sockfd,F_GETFL,0);
    fcntl(sockfd,F_SETFL,flags|O_NONBLOCK);//设置为非阻塞

    if( (res = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) )< 0)
    {
        if(errno != EINPROGRESS)
        {
            return 1;
        }

    }

    //如果server与client在同一主机上，有些环境socket设为非阻塞会返回 0
    // if(0 == res) goto done;

    while(error!=0){

        tval.tv_sec=0;
        tval.tv_usec=3000000;   //要在while重新设置时间，否则超时不生效
        FD_ZERO(&rset);            //要在while重新添加句柄，否则检测不了变化
        FD_SET(sockfd,&rset);
        wset=rset;
        printf("enter while\n");

        res = select(sockfd+1, NULL, &wset, NULL,&tval) ;
        if( res == 0)
        {
            perror("connect time out\n");
            // close(sockfd);
            // return 1;
        }
        else 
        {
            if(res>0){

                len=sizeof(error);
                getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);

                printf("error:%d\n", error);
                if(error)
                {
                    fprintf(stderr, "Error in connection() %d - %s\n", error, strerror(error));
                    // return 1;
                }

            }


        }
    }

    if(res !=0)
    {
        printf("done\n");
        if( (n = send(sockfd, sendData, strlen(sendData),0) ) ==-1 )
        {

            perror("send error!");
            close(sockfd);
            return 1;
        }
        if( ( n = select(sockfd+1,&rset,NULL, NULL,&tval)) <= 0 )//rset没有使用过，不用重新置为sockfd
        {
            perror("receive time out or connect error");
            close(sockfd);
            return -1;
        }
        if((recvbytes=recv(sockfd, buf, 1024, 0)) ==-1)
        {
            perror("recv error!");
            close(sockfd);
            return 1;
        }


        printf("receive num %d\n",recvbytes);
        printf("%s\n",buf);

    }
}
