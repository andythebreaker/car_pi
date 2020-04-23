/***  TCP Server tcpserver.c
 *
 * 利用 socket 介面設計網路應用程式
 * 程式啟動後等待 client 端連線，連線後印出對方之 IP 位址
 * 並顯示對方所傳遞之訊息，並回送給 Client 端。
 *
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/errno.h>

#define SERV_PORT 5134


#define MAXNAME 1024


extern int errno;


main()
{
 int socket_fd;      /* file description into transport */
 int recfd;     /* file descriptor to accept        */
 int length;     /* length of address structure      */
 int nbytes;     /* the number of read **/
 char buf[BUFSIZ];
 struct sockaddr_in myaddr; /* address of this service */
 struct sockaddr_in client_addr; /* address of client    */
/*                             
 *      Get a socket into TCP/IP
 */
 if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) <0) {
  perror ("socket failed");
  exit(1);
 }
/*
 *    Set up our address
 */
 bzero ((char *)&myaddr, sizeof(myaddr));
 myaddr.sin_family = AF_INET;
 myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 myaddr.sin_port = htons(SERV_PORT);


/*
 *     Bind to the address to which the service will be offered
 */
 if (bind(socket_fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) <0) {
  perror ("bind failed");
  exit(1);
 }


/*
 * Set up the socket for listening, with a queue length of 5
 */
 if (listen(socket_fd, 20) <0) {
  perror ("listen failed");
  exit(1);
 }
/*
 * Loop continuously, waiting for connection requests
 * and performing the service
 */
 length = sizeof(client_addr);
 printf("Server is ready to receive !!\n");
 printf("Can strike Cntrl-c to stop Server >>\n");
 while (1) {
  if ((recfd = accept(socket_fd,
      (struct sockaddr_in *)&client_addr, &length)) <0) {
   perror ("could not accept call");
   exit(1);
         }


  if ((nbytes = read(recfd, &buf, BUFSIZ)) < 0) {
   perror("read of data error nbytes !");
   exit (1);
  }
   
  printf("Create socket #%d form %s : %d\n", recfd,
  inet_ntoa(client_addr.sin_addr), htons(client_addr.sin_port));
  printf("%s\n", &buf);
 
  /* return to client */
  if (write(recfd, &buf, nbytes) == -1) {
   perror ("write to client error");
   exit(1);
  }
  close(recfd);
  printf("Can Strike Crtl-c to stop Server >>\n");
 }
}