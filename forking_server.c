#include "networking.h"
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
void process(char *s);
void subserver(int from_client);
#define SHMSZ 27

void calculate(){
 int shmid;
  key_t key;
  int *shm, *pids;
  key = 5678;
  shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
  shm = shmat(shmid, NULL, 0);
  pids = shm;
  //your code goes here, calculate who got most right, and store it in a file called Winners,txt
  
  pids[8]=1;
}

int main() {
  remove("PlayerAnswers.txt");
  int listen_socket;
  int f;
  listen_socket = server_setup();
  int shmid;
  key_t key;
  int *shm, *pids;
  key = 5678;
  shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
  shm = shmat(shmid, NULL, 0);
  pids = shm;
  pids[1]=0;
  for(int i=2; i<=8; i++){
    pids[i]=0;
  }
  while (1) {
    int client_socket = server_connect(listen_socket);
    f = fork();
    if (f == 0){
      int count=0;
      int spot=0;
      for(int i=2; i<=5; i++){
	if(pids[i]!=getpid()){
	  count++;
	  if(pids[i]==0){
	    spot=i;
	  }
	}
      }
      if(count==4){
	pids[spot]=getpid();
      }
      count=0;
      for(int i=2; i<=5; i++){
 	if(pids[i]!=0){
	  count++;
	}
      }
      if(count==4){
	for(int i=2; i<=5; i++){
	  pids[i]=0;
	}
	pids[1]+=1;
	pids[6]=1;
      }
      subserver(client_socket);
    }
    else{
      close(client_socket);
      
    }
  }
}

void subserver(int client_socket){
  char buffer[BUFFER_SIZE];
  int shmid;
  key_t key;
  int *shm, *pids;
  key = 5678;
  shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
  shm = shmat(shmid, NULL, 0);
  pids = shm;
  while (read(client_socket, buffer, sizeof(buffer))) {
    int count=0;
    int spot=0;
    for(int i=2; i<=5; i++){
      if(pids[i]!=getpid()){
	count++;
	if(pids[i]==0){
	  spot=i;
	}
      }
    }
    if(count==4){
      pids[spot]=getpid();
    }
    count=0;
    for(int i=2; i<=5; i++){
      if(pids[i]!=0){
	count++;
      }
    }
    if(count==4){
      for(int i=2; i<=5; i++){
	pids[i]=0;
      }
      
      pids[1]+=1;
    }
    FILE *q = fopen("questions.txt", "rb");
    fseek(q, 0, SEEK_END);
    long fsize = ftell(q);
    fseek(q, 0, SEEK_SET);  //same as rewind(f);
    char *line = malloc(fsize + 1);
    fread(line, fsize, 1, q);
    char ** args = calloc(6, sizeof(line));
    char * s = strdup(line);
    int z = 0;
    while(args[z] = strsep(&s, "\n")){
      z++;
    }
    z=0;
    while(args[z]!=NULL){
      z++;
    }
    fclose(q);
    int max=z;
    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    write(client_socket, buffer, sizeof(buffer));
    FILE *f = fopen("PlayerAnswers.txt","a");
    char ans[100];
    sprintf(ans, "%i", getpid());
    strcat(ans,":");
    strcat(ans,buffer);
    fprintf(f,"%s\n",ans);
    printf("%s \n",ans);
    fclose(f);
    if(pids[1]==max){
      int fin=0;
      for(int i=2; i<=5; i++){
	if(pids[i]!=0){
	  fin++;
	}
      }
      if(fin==4){
	pids[7]=1;
	calculate();
      }
    }
  }//End read loop
  close(client_socket);
  exit(0);
}


void process(char * s) {
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
}
