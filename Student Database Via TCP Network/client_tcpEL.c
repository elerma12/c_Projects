/****************Client program********************************/

/* client_tcp.c is on zeus.cs.txstate.edu
   open a window on zeus.
   compile:
   $gcc -o c client_tcp.c
   $./c eros.cs.txstate.edu
*/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>

int main(int argc, char **argv){
   int clientSocket, score,check;
  char buffer[1024] ,ID[5],Fname[9],Lname[9];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  unsigned short port;
  struct hostent *hostnm;


  uint32_t num, cnum;
  char msg[1024];

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8000);

  /* Set IP address to localhost */
  hostnm = gethostbyname(argv[1]);
  serverAddr.sin_addr.s_addr = *((unsigned long *)hostnm->h_addr); 
/* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);


// communication starts from here
for( ;;)
{

   // send an integer to the server
  printf("Please choose one of the choices below. \n 1.) Add a New Student \n 2.) Display Student's Information \n 3.) Display Student's Score \n 4.) Display all Students' Information \n 5.) Delete Student  \n 6). Exit the Program \n Choice: ");
  scanf("%d", &num);
  cnum = htonl(num);


  if (num == 1)
  { 
    bzero(buffer,sizeof(buffer));
    printf( "Please enter new student's ID (Enter six digits only):");
    scanf( "%s",ID);
    // while ( strlen(ID)!=6)
    // {
    //   printf( "Please enter new student's ID (Enter six digits only):");
    //   scanf( "%s",ID);
    // }
    printf( "Please enter new student's first name:");
    scanf( "%s",Fname);
    printf( "Please enter new student's last name:");
    scanf( "%s",Lname);
    printf( "Please enter new student's score (0-100):");
    scanf( "%d",&score);
    //get data and place it in buffer 
    sprintf(buffer, "%s,%s,%s,%d \n",ID,Fname,Lname,score);
    // send an integer to the server
    send(clientSocket, &cnum, sizeof(cnum), 0);
    // recieve request notification
    recv(clientSocket, msg, sizeof(msg), 0);
    printf("%s\n", msg);
    // send buffer data 
    send(clientSocket, buffer, sizeof(buffer), 0);
    //recieve message from server 
    recv(clientSocket, msg, sizeof(msg), 0);
    printf("%s\n", msg);
    printf(buffer); // might have to change it to printf("%s\n",buffer);
    printf("\n");
  }

   if (num == 2)
  {
    bzero(buffer,sizeof(buffer));
    printf("Please enter Student's ID (six digits only):");
    scanf( "%s",ID);
    send(clientSocket, &cnum, sizeof(cnum), 0);
    // recieve request notification
    recv(clientSocket, msg, sizeof(msg), 0);
    printf("%s\n", msg);
     // get data from file
    sprintf(buffer,"%s\n",ID);
    //send ID to server
    send(clientSocket, buffer, sizeof(buffer), 0);
    bzero(buffer,sizeof(buffer));
    //recive ID from server
    recv(clientSocket,buffer,sizeof(buffer),0);
    printf("%s\n",buffer );
    
    
  }
// user selects to grab list of students who all score above a certain score 
  if (num == 3)
  {
    bzero(buffer,sizeof(buffer));
    printf("Please enter score (0-100):");
    scanf("%d",&score);
    // send an integer to the server
    send(clientSocket, &cnum, sizeof(cnum), 0);
    // recieve request notification
    recv(clientSocket, msg, sizeof(msg), 0);
    printf("%s\n", msg);
    // code for code retriveal
    printf("All Students who scored above ");
    printf("%d",score);
    printf(":\n");
    send(clientSocket,&score,sizeof(int),0);
    recv(clientSocket,buffer,sizeof(buffer),0);
    sscanf(buffer,"%d",&check);// check counter for checking if the entire file has been read 
    while(check!=2)
    {
      sscanf(buffer,"%d,%[^,],%[^,],%[^,],%d",&check,ID,Fname,Lname,&score);
      printf("%s %s %s %d\n",ID,Fname,Lname,score );
      bzero(buffer,sizeof(buffer));
      sprintf(buffer,"ok");
      send(clientSocket,buffer,sizeof(buffer),0);
      bzero(buffer,sizeof(buffer));
      recv(clientSocket,buffer,sizeof(buffer),0);
      sscanf(buffer,"%d",&check);
    }

  }
   if (num == 4)
  {
    bzero(buffer,sizeof(buffer));
    //code to get all data
    send(clientSocket, &cnum, sizeof(cnum), 0);
    recv(clientSocket, msg, sizeof(msg), 0);
    printf("%s\n",msg);
    printf("List of all students in the server:\n");
    send(clientSocket,buffer,sizeof(buffer),0);
    recv(clientSocket,buffer,sizeof(buffer),0);
    sscanf(buffer,"%d",&check);// check counter for checking if the entire file has been read 
    while(check!=2)
    {
      sscanf(buffer,"%d,%[^,],%[^,],%[^,],%d",&check,ID,Fname,Lname,&score);
      printf("%s %s %s %d\n",ID,Fname,Lname,score );
      bzero(buffer,sizeof(buffer));
      sprintf(buffer,"ok");
      send(clientSocket,buffer,sizeof(buffer),0);
      bzero(buffer,sizeof(buffer));
      recv(clientSocket,buffer,sizeof(buffer),0);
      sscanf(buffer,"%d",&check);
    }
    
  }
   if (num == 5)
  {
    bzero(buffer,sizeof(buffer));
    printf("Please enter the ID of the student that you wish to delete (six digits only):");
    scanf("%s", ID);
    send(clientSocket, &cnum, sizeof(cnum), 0);
    recv(clientSocket, msg, sizeof(msg), 0);
    printf("%s\n", msg);
    sprintf(buffer,"%s\n",ID);
    //send ID to server
    send(clientSocket, buffer, sizeof(buffer), 0);
    bzero(buffer,sizeof(buffer));
    recv(clientSocket,buffer,sizeof(buffer),0);
    printf("%s\n",buffer );
  }
   

  if (num == 6)
  {
    send(clientSocket, &cnum, sizeof(cnum), 0);
    recv(clientSocket, msg, sizeof(msg), 0);
    printf("%s\n", msg); 
    break;
  }

}

  close(clientSocket);

  return 0;
}

