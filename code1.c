#include<stdlib.h>
#include<unistd.h>
#include <string.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>


int main (){

 int sockPelayan, status, port = 8080, dengar, c, sockPelanggan, count;
 struct sockaddr_in pelayan, pelanggan;
 char kataKata[2000], *balasan, temp;

 int optval;
 socklen_t optlen = sizeof(optval);

 //socket creation
 sockPelayan = socket(AF_INET, SOCK_STREAM, 0);

  if (sockPelayan < 0)
  {
   printf("Alamak Ada Error la! \n");
  }
  else {
   printf("NAIS, socket setel \n");
  }


   if(getsockopt(sockPelayan, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
   perror("getsockopt()");
   close(sockPelayan);
   exit(EXIT_FAILURE);
   }

   printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));

        /* Set the option active */
   optval = 1;
   optlen = sizeof(optval);

   if(setsockopt(sockPelayan, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
   perror("setsockopt()");
   close(sockPelayan);
   exit(EXIT_FAILURE);
   }
   printf("SO_KEEPALIVE set on socket\n");


        /* Check the status again */
   if(getsockopt(sockPelayan, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
   perror("getsockopt()");
   close(sockPelayan);
   exit(EXIT_FAILURE);
   }
   printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));



 //BIND creation inet_addr("192.168.56.102")
 pelayan.sin_family = AF_INET;
 pelayan.sin_addr.s_addr = inet_addr("192.168.56.101");
 pelayan.sin_port = htons(port);

 status = bind(sockPelayan,(struct sockaddr *)&pelayan, sizeof(pelayan));

  if(status < 0){
   printf("BALA BALA BALA... Bind xleh buat \n");
  }
  else{
   printf("Step2 setel bos, bind jadi kt port %d.. \n", port);
  }

 //listen creation
 dengar =  listen (sockPelayan, 3);

  if (dengar < 0){
   printf("tak dengar apa2 pun... \n");
  }
  else{
   printf("tengah tunggu order je ni...\n");
  }

 c = sizeof(struct sockaddr_in);
 sockPelanggan = accept(sockPelayan, (struct sockaddr *)&pelanggan, (socklen_t *)&c );

 while(strncmp(kataKata , "berhenti", 8) != 0){

  count = 0;
  printf("Kata-kata dari pelanggan: ");

  recv(sockPelanggan, kataKata, 2000, 0);
  puts(kataKata);

  memset(kataKata,0,sizeof(kataKata));
  printf("Dari Pelayan: ");
  scanf("%c", &temp);
  scanf("%[^\n]", balasan);
  count = send(sockPelanggan, balasan, strlen(balasan), 0);
  

 }

 close(sockPelayan);

}
