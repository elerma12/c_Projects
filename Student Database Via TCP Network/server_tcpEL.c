/***************Server program**************************/

/* server_tcp.c is on eros.cs.txstate.edu
   open a window on eros.
   compile and run the server program first:
   $gcc -o s server_tcp.c
   $./s
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

//function to add student to file 
int add(char *ID,char *Fname, char *Lname,int score)  // fix problem where the first number will duplicate first option if second input has the same ID 
{
 int yes = 1;
 int no = 2;
 FILE *fp = fopen("database.txt","a+");
 char tempID[5],tempFname[9],tempLname[9],tempchar;
 int tempScore;
 while(fscanf(fp,"%[^,],%[^,],%[^,],%d",tempID,tempFname,tempLname,&tempScore)==4)
 {
   if(strcmp(tempID, ID)==0) 
   {
     fclose(fp); 
     return no;
   }

  fscanf(fp,"%c",&tempchar);
 }

 fseek(fp,0,SEEK_END);
 fprintf(fp, "%s,%s,%s,%d\n", ID,Fname,Lname,score);
 fclose(fp);
 return yes;
}


// display student's info based on ID input
char* display( char *ID)  
{
   char *returnString,tempchar;
   //returnstring to return the details to main function
   returnString = (char*)malloc(sizeof(char)*1024*4);
   //open the file
   FILE *fp = fopen("database.txt","r");
   char tempID[5],tempFname[9],TempLname[9];
   int tempScore;

   //read from the file
   while(fscanf(fp,"%[^,],%[^,],%[^,],%d",tempID,tempFname,TempLname,&tempScore)==4)
   {
       //compare with the student's ID
       if(strcmp(tempID, ID)== 0) 
       {
           bzero(returnString,sizeof(returnString));
           sprintf(returnString,"%s,%s,%s,%d",tempID,tempFname,TempLname,tempScore);
           fclose(fp);
           return returnString;
       }
       fscanf(fp,"%c",&tempchar);
   }

   fclose(fp);
   return NULL;
}


//function to delete a student's information 
int delete (char *ID)
{
  FILE *fp = fopen("database.txt","r");
  FILE *fp2 = fopen(".tmp.database.txt","w");
  char tempID[5],tempFname[9],TempLname[9],tempchar ;
  int tempScore, check=0;
  int yes = 1;
  int no = 2;
  while(fscanf(fp,"%[^,],%[^,],%[^,],%d",tempID,tempFname,TempLname,&tempScore)==4)
  {
     if(strcmp(tempID, ID)!= 0)
     {
       fprintf(fp2, "%s,%s,%s,%d\n",tempID,tempFname,TempLname,tempScore);
     } 
     else
     {
        check = 1;
     }
      fscanf(fp,"%c",&tempchar);
  }

  fclose(fp);
  fclose(fp2);
  remove("database.txt");
  rename(".tmp.database.txt","database.txt");

  if(check==0) 
  {
    return no;
  }
  else
  { 
    return yes;
  }
}



int main(int argc, char **argv){
  int welcomeSocket,newSocket, score,counter;
  char buffer[1024],ID[5],Fname[9],Lname[9],*returnString;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  unsigned short port; /* port server binds to */

  uint32_t num;
  char msg[1024];

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(8000);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);



// communication starts from here


 for ( ;;) 
 {   //receive an integer from the client
    recv(newSocket, &num, sizeof(num), 0);
    printf("Integer received: %d\n",ntohl(num));   
    
 
  //option to add a student 
  if (ntohl(num) == 1 )  
  {
    bzero(buffer,sizeof(buffer));
   // send a reply message to the client
    strcpy(msg, "Request to create profile has been recieved.");
    send(newSocket, msg, sizeof(msg), 0);
    recv(newSocket,buffer,sizeof(buffer),0);
    printf("%s\n",buffer);

    sscanf(buffer,"%[^,],%[^,],%[^,],%d",ID,Fname,Lname,&score);

    //call add_user to add into database
    counter = add(ID,Fname,Lname,score);
    //copy all contents of buffer in to variables and send them through add
    if ( counter == 2)
    {
      strcpy(msg,"Cannot add student, student already exists in Database\n");
    }
    else
    {
      strcpy(msg, "Data shown below has been sent to the server\n");
    }
    send(newSocket, msg, sizeof(msg), 0);
  }



// option to display students info
  if (ntohl(num) == 2 ) 
  {
    bzero(buffer,sizeof(buffer));
   // send a reply message to the client
    strcpy(msg, "Request to display student Info has been recieved.");
    send(newSocket, msg, sizeof(msg), 0);
    recv(newSocket,buffer,sizeof(buffer),0);
    sscanf(buffer,"%s",ID);
    returnString = display(ID);
    bzero(buffer,sizeof(buffer));
    if(returnString==NULL) 
    {
      sprintf(buffer,"ID Doesn't exist"); 
    }
    else
    {
      sprintf(buffer,"%s\n",returnString);
    }

    send(newSocket,buffer,sizeof(buffer),0);
  }



//option to print all student who score aboove a certain number 
  if (ntohl(num) == 3 )
  {
    FILE *fp = fopen("database.txt","r");
    char tempID[5],tempFname[9],tempLname[9],tempchar;
    int tempScore;
   // send a reply message to the client
    strcpy(msg, "Request for score of students has been recieved.");
    send(newSocket, msg, sizeof(msg), 0);
     // recieve score 
    recv( newSocket,&score,sizeof(int),0);
    while(fscanf(fp,"%[^,],%[^,],%[^,],%d",tempID,tempFname,tempLname,&tempScore)==4)
    {
      if(tempScore > score)
      {
        bzero(buffer,sizeof(buffer));
        sprintf(buffer,"1,%s,%s,%s,%d",tempID,tempFname,tempLname,tempScore);
        send(newSocket,buffer,sizeof(buffer),0);
        recv(newSocket,buffer,sizeof(buffer),0);
      }  
      fscanf(fp,"%c,",&tempchar);
    }
    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"2\n");
    send(newSocket,buffer,sizeof(buffer),0);
    fclose(fp);
  }



  // to print all students in database 
  if (ntohl(num) == 4 )
  {
   // send a reply message to the client
    strcpy(msg, "Request to display the entire database has ben recieved.");
    send(newSocket, msg, sizeof(msg), 0);
    FILE *fp = fopen("database.txt","r");
    char tempID[5],tempFname[9],tempLname[9],tempchar;
    int tempScore;
    recv(newSocket,buffer,sizeof(buffer),0);  
     while(fscanf(fp,"%[^,],%[^,],%[^,],%d",tempID,tempFname,tempLname,&tempScore)==4)
    {
     
      bzero(buffer,sizeof(buffer));
      sprintf(buffer,"1,%s,%s,%s,%d",tempID,tempFname,tempLname,tempScore);
      send(newSocket,buffer,sizeof(buffer),0);
      recv(newSocket,buffer,sizeof(buffer),0);
      fscanf(fp,"%c,",&tempchar);

    }
    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"2\n");
    send(newSocket,buffer,sizeof(buffer),0);
    fclose(fp);
  }



//option to delete a student 
  if (ntohl(num) == 5 )
  {
   // send a reply message to the client
    strcpy(msg, "Request to delete student has been recieved");
    send(newSocket, msg, sizeof(msg), 0);
    recv(newSocket,buffer,sizeof(buffer),0);
    sscanf(buffer,"%s",ID);
    counter = delete(ID);
    bzero(buffer,sizeof(buffer));
    if(counter == 2) 
    {
      sprintf(buffer,"ID Doesn't exist\n");
    }

    else
    {
      sprintf(buffer,"Successfully deleted\n");
    }
     send(newSocket,buffer,sizeof(buffer),0);
  }

  // option to shutdown program
  if ( ntohl(num)== 6)
  {
    bzero(buffer,sizeof(buffer));
    // send a reply message to the client
    strcpy(msg, "Exiting Program...server is shutting down");
    send(newSocket, msg, sizeof(msg), 0);
    break;
  }
}



  close(newSocket);
  close(welcomeSocket);

  return 0;
}
