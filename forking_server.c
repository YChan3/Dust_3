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
#include <ctype.h>
void process(char *s);
void subserver(int from_client);
#define SHMSZ 27

void convertToUpperCase(char * temp) {
  char * name;
  name = strtok(temp,":");

  // Convert to upper case
  char *s = name;
  while (*s) {
    *s = toupper((unsigned char) *s);
    s++;
  }

}

char * fWinr(int max){
  FILE *fp;
  FILE *fa;
  char input[256];
  char input2[256];
  char input3[256];
  char input4[256];
  char ans[256];

  struct player{
  	char id[10];
  	char name[50];
  	int score;
  };

  /* opening file for reading */
  fp = fopen("PlayerAnswers.txt" , "r");

  int i = 1;
  struct player p1;
  struct player p2;
  struct player p3;
  struct player p4;

  char *token;

  fgets(input, 256, fp);
  p1.score = 0;
  token = strtok(input, ":");
  strcpy(p1.id, token);
  token = strtok(NULL, ":");
  token = strtok(token, "\n");
  strcpy(p1.name, token);

  fgets(input, 256, fp);
  p2.score = 0;
  token = strtok(input, ":");
  strcpy(p2.id, token);
  token = strtok(NULL, ":");
  token = strtok(token, "\n");
  strcpy(p2.name, token);

  fgets(input, 256, fp);
  p3.score = 0;
  token = strtok(input, ":");
  strcpy(p3.id, token);
  token = strtok(NULL, ":");
  token = strtok(token, "\n");
  strcpy(p3.name, token);

  fgets(input, 256, fp);
  p4.score = 0;
  token = strtok(input, ":");
  strcpy(p4.id, token);
  token = strtok(NULL, ":");
  token = strtok(token, "\n");
  strcpy(p4.name, token);

  fa = fopen("answers.txt" , "r");

  while(max--){
    fgets(ans, 256, fa);
    int counter = 4;
    while(counter--){
      fgets(input, 256, fp);
      strcpy(input2, input);
      strcpy(input3, input);
      strcpy(input4, input);
      token = strtok(input, ":");
      if(strcmp(p1.id, token) == 0){
        token = strtok(NULL, ":");
        token = strtok(token, "\n");
        convertToUpperCase(token);
        if(strcmp(token, strtok(ans, "\n")) == 0){
          p1.score += 1;
        }
      }
      token = strtok(input2, ":");
      if(strcmp(p2.id, token) == 0){
        token = strtok(NULL, ":");
        token = strtok(token, "\n");
        convertToUpperCase(token);
        if(strcmp(token, strtok(ans, "\n")) == 0){
          p1.score += 1;
        }
      }
      token = strtok(input3, ":");
      if(strcmp(p3.id, token) == 0){
        token = strtok(NULL, ":");
        token = strtok(token, "\n");
        convertToUpperCase(token);
        if(strcmp(token, strtok(ans, "\n")) == 0){
          p1.score += 1;
        }
      }
      token = strtok(input4, ":");
      if(strcmp(p4.id, token) == 0){
        token = strtok(NULL, ":");
        token = strtok(token, "\n");
        convertToUpperCase(token);
        if(strcmp(token, strtok(ans, "\n")) == 0){
          p1.score += 1;
        }
      }
    }
  }
  fclose(fa);
  fclose(fp);
  struct player w1;
  struct player w2;
  if(p1.score > p2.score){
    strcpy(w1.name, p1.name);
    w1.score = p1.score;
  }else{
    strcpy(w1.name, p2.name);
    w1.score = p2.score;
  }
  if(p3.score > p4.score){
    strcpy(w2.name, p3.name);
    w2.score = p3.score;
  }else{
    strcpy(w2.name, p4.name);
    w2.score = p4.score;
  }
  char *str_to_ret = malloc(sizeof(char) * 50);
  if(w1.score > w2.score){
    strcpy(str_to_ret, w1.name);
    return(str_to_ret);
  }
  strcpy(str_to_ret, w2.name);
  return(str_to_ret);
}

void calculate(){
  printf("Start of calculate \n");
  int shmid;
  key_t key;
  int *shm, *pids;
  key = 5678;
  shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
  shm = shmat(shmid, NULL, 0);
  pids = shm;
  int a = shmget(5679,1024,0666|IPC_CREAT);
  char *winnerglob = (char*) shmat(a,(void*)0,0); 
  printf("Start of fWinr \n");
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
  int max=z-2;
  char * winner = fWinr(max);
  strcpy(winnerglob,winner);
  printf("end of calculate \n");
  pids[8]=1;
}

int main() {
  remove("PlayerAnswers.txt");
  remove("Winners.txt");
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
  shmdt(pids);
  shmctl(shmid,IPC_RMID,NULL);
  int a = shmget(5679,1024,0666|IPC_CREAT);
  char *winnerglob = (char*) shmat(a,(void*)0,0);
  shmdt(winnerglob);
  shmctl(a,IPC_RMID,NULL);
  printf("destroy \n");
  shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
  shm = shmat(shmid, NULL, 0);
  pids = shm;
  for(int i=1; i<=10; i++){
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
    int max=z-2;
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
      pids[7]=1;
    }
    if(pids[10]==4){
      printf("calculating \n");
      calculate();
      pids[10]++;
      printf("done \n");
	
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
