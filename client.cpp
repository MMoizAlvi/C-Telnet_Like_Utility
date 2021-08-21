#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include "pthread.h"
#include "iostream"
#include "string.h"

using namespace std;


char re[2048];
char next_line[]={'\r','\n'};
void send_in_socket(char re[]);
void communication_socket(int fd);


int main(int argc,char *argv[]) {
	
	if(argc != 4)
	{
		cout<<"less arguments are passed! try again."<<endl;
		cout<<"\nPlease Enter Valid Command Line Args."<<endl;
		cout<<"FOR TCP input T or t For UDP input U or u after IP and port no.  "<<endl;
		exit(1);
	}
	
	if(*argv[3] == 'T'||*argv[3] == 't')
	{
		cout<<"\nWelcome its connected to: "<<argv[1]<<" on port no. "<<argv[2]<<endl;

	int fd = socket(AF_INET, SOCK_STREAM, 0);

	if (fd == -1) {
		perror("Socket Creation Failed \n");
		exit (1);
	}


	struct sockaddr_in s_addr;
	s_addr.sin_family	= AF_INET;
	s_addr.sin_port		= htons(atoi(argv[2]));
	inet_aton(argv[1],&s_addr.sin_addr);
	
	if (connect(fd, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1) {
		perror("Connect failed \n");
		exit(1);
	}
	
	if(atoi(argv[2])==25)
	{	//sending email 
		recv(fd,re,sizeof(re),0);
		cout<<re<<endl;
		bzero(&re,sizeof(re));
		cout<<"\nTO SEND AN EMAIL FOLLOW THE INSTRUCTIONS\n"<<endl;
		cout<<"please type helo and then client IP adress to start communication: "<<endl;
		communication_socket(fd);
		
		cout<<"type mail from: and then sender's email address after space: "<<endl;
		communication_socket(fd);
		
		cout<<"type rcpt to: and then recipient's email address after space: "<<endl;
		communication_socket(fd);
		
		cout<<"input data and hit enter"<<endl;
		communication_socket(fd);
		
		cout<<"\n***************ENTER YOUR SUBJECT AND BODY OF EMAIL***************"<<endl;
		cout<<"HIT '.' TO TERMINATE YOUR SENDING PROCESS\n"<<endl;
		char subject[100];
		fgets(subject,100,stdin);
		send(fd,subject,strlen(subject),0);
		send(fd,"\n\r\n",strlen("\n\r\n"),0);
		bzero(&subject,sizeof(subject)); 
		char body[1024];
		if(fgets(body,1024,stdin)==NULL)
		{
			cout<<"fail to get correct input"<<endl;
		}
		else
		{
			body[strcspn(body,"\n")]='\0';
		}
		send(fd,body,strlen(body),0);
		send(fd,"\r\n",strlen("\r\n"),0);
		bzero(&body,sizeof(body)); 
		if(fgets(body,1024,stdin)==NULL)
		{
			cout<<"fail to get correct input"<<endl;
		}
		else
		{
			body[strcspn(body,"\n")]='\0';
		}
		send(fd,body,strlen(body),0);
		send(fd,"\r\n",strlen("\r\n"),0);
		bzero(&body,sizeof(body)); 
		recv(fd,body,sizeof(body),0);
		cout<<body<<endl;
		bzero(&body,sizeof(body)); 
		
		cout<<"Enter quit to exit anytime! "<<endl;
		communication_socket(fd);
		
		}
		else if(atoi(argv[2])==110)
		{
			//recieving email
		 
		recv(fd,re,sizeof(re),0);
		cout<<re<<endl;
		bzero(&re,sizeof(re));
		cout<<"\nTO READ AN EMAIL FOLLOW THE INSTRUCTIONS\n"<<endl;
		cout<<"please type user and then user email id after space: "<<endl;
		communication_socket(fd);
		
		cout<<"please type pass and enter your password after space: "<<endl;
		communication_socket(fd);
		
		cout<<"input retr then serial no. to read your specific email "<<endl;
		cout<<" Enter quit to exit your mailbox anytime! "<<endl;
		while(1)
			{
				communication_socket(fd);
			}
		
		}
		else if(atoi(argv[2])==80)
		{
			//GET HTTP
		cout<<"\nTo issue GET command input GET / HTTP/1.1 => Host: IP address \n"<<endl;
		char get_data[125000]={};
		send_in_socket(get_data);
		send(fd, get_data, strlen(get_data), 0);
		send(fd,"\r\n",strlen("\r\n"),0);
		bzero(&get_data,sizeof(get_data));
		send_in_socket(get_data);
		send(fd, get_data, strlen(get_data), 0);
		send(fd,"\r\n\n",strlen("\r\n\n"),0);
		bzero(&get_data,sizeof(get_data));
		recv(fd,get_data,sizeof(get_data),0);
		cout<<get_data<<endl;
		
		}
		
	
		
	}
	else if(*argv[3] == 'U'||*argv[3] == 'u')
	{
		int fd = socket(AF_INET, SOCK_DGRAM, 0);

	if (fd == -1) {
		perror("Socket Creation Failed \n");
		exit (1);
	}


	struct sockaddr_in s_addr;
	s_addr.sin_family	= AF_INET;
	s_addr.sin_port		= htons(atoi(argv[2]));
	inet_aton(argv[1],&s_addr.sin_addr);
	cout<<"\nWelcome its connected to: "<<argv[1]<<" on port no. "<<argv[2]<<endl;
	if(atoi(argv[2])==25)
	{	//sending email 
		cout<<"\nSMTP not supported on UDP ! TRY AGAIN with TCP/IP"<<endl;
		cout<<"\nFOR TCP input T or t For UDP input U or u after IP and port no.  "<<endl;
		}
		else if(atoi(argv[2])==110)
		{
			//recieving email
		 cout<<"\nPOP3 not supported on UDP ! TRY AGAIN with TCP/IP"<<endl;
		cout<<"\nFOR TCP input T or t For UDP input U or u after IP and port no.  "<<endl;
		
		}
		else if(atoi(argv[2])==80)
		{
			//GET HTTP
		 cout<<"\nGET HTTP not supported on UDP ! TRY AGAIN with TCP/IP"<<endl;
		 cout<<"\nFOR TCP input T or t For UDP input U or u after IP and port no.  "<<endl;
		
		}
	
	}
	else
	{
		cout<<"\nPlease Enter Valid Command Line Args."<<endl;
		cout<<"FOR TCP input T or t For UDP input U or u after IP and port no.  "<<endl;
	}
		
	
	

	return 0;
}

void communication_socket(int fd)
{
		send_in_socket(re);
		send(fd,re,strlen(re),0);
		bzero(&re,sizeof(re));
		send(fd,next_line,strlen(next_line),0);
		bzero(&re,sizeof(re)); 
		recv(fd,re,sizeof(re),0);
		cout<<re<<endl;
		bzero(&re,sizeof(re));
}

void communication_socket(int fd,char r[])
{

		send_in_socket(re);
		send(fd,re,strlen(re),0);
		bzero(&re,sizeof(re));
		send(fd,next_line,strlen(next_line),0);
		bzero(&re,sizeof(re)); 
		recv(fd,re,sizeof(re),0);
		cout<<re<<endl;
		bzero(&re,sizeof(re));
}


void send_in_socket(char re[])
{
	if(fgets(re,1024,stdin)==NULL)
		{
			cout<<"fail to get correct input"<<endl;
		}
		else
		{
			re[strcspn(re,"\n")]='\0';
		}
}
