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

char* tup(char * change) {
  int i = 0;
  char c;
  char str[200];
  strcpy(str,change);
  while(*change++) {
    str[i]=toupper(str[i]);
    i++;
  }
  char *m=str;
  return m;

}

char* win(){
  int shmid;
  key_t key;
  int *shm, *pids;
  key = 5678;
  shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
  shm = shmat(shmid, NULL, 0);
  pids = shm;
  int * pi =calloc(5, sizeof(int));
  int * corr =calloc(5, sizeof(int));
  char ** p;
  corr[2]=0;
  corr[3]=0;
  corr[4]=0;
  corr[5]=0;
  
  pi[2]=pids[22];
  pi[3]=pids[23];
  pi[4]=pids[24];
  pi[5]=pids[25];

  
  char * buffer = 0;
  long length;
  FILE * f = fopen ("PlayerAnswers.txt", "rb");
  if (f){
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)
      {
	fread (buffer, 1, length, f);
      }
    fclose (f);
  }
  char ** args = calloc(6, sizeof(buffer));
  int i = 0;
  while(args[i] = strsep(&buffer, "\n")){
    i++;
  }
  args[i-1]='\0';
  
  char * buffer2 = 0;
  long length2;
  FILE * f1 = fopen ("answers.txt", "rb");
  if (f1){
    fseek (f1, 0, SEEK_END);
    length2 = ftell (f1);
    fseek (f1, 0, SEEK_SET);
    buffer2 = malloc (length2);
    if (buffer2)
      {
	fread (buffer2, 1, length2, f1);
      }
    fclose (f1);
  }
  char ** args2 = calloc(20, sizeof(buffer2));
  int i2 = 0;
  while(args2[i2] = strsep(&buffer2, ",")){
    i2++;
  }
  args2[i2-1]='\0';
  i2=0;
  while(args2[i2]!=NULL && args2[i2]!='\n'){
    i=0;
    while(args[i]!=NULL && args[i]!='\n'){
      char bu[100];
      strcpy(bu, args[i]);
      char * sec=bu;
      char * res= strsep(&sec, ":");
      if(strcmp(args2[i2],tup(sec))==0){
	char as2[10];
	char as3[10];
	char as4[10];
	char as5[10];	  
	snprintf(as2, 10, "%d", pi[2]);
	snprintf(as3, 10, "%d", pi[3]);
	snprintf(as4, 10, "%d", pi[4]);
	snprintf(as5, 10, "%d", pi[5]);
	if(strcmp(res,as2)==0){
	  corr[2]++;
	}
	else if(strcmp(res,as3)==0){
	  corr[3]++;
	}
	else if(strcmp(res,as4)==0){
	  corr[4]++;
	}
	
	else if(strcmp(res,as5)==0){
	  corr[5]++;
	}
	
      }
      i++;
    }
    i2++;
  }
  if(corr[2]==corr[3]==corr[4]==corr[5]){
    return 0;
  }
  int best=2;
  for(int y=2; y<=5;y++ ){
    if(corr[y]>corr[best]){
      best=y;
    }
  }

  char *pid1=strsep(&args[0], ":");
  char *p1 =args[0];
  char *pid2=strsep(&args[1], ":");
  char *p2 =args[1];
  char *pid3=strsep(&args[2], ":");
  char *p3 =args[2];
  char *pid4=strsep(&args[3], ":");
  char *p4 =args[3];

  return args[best-2];
  
}

char * fWinr(){
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
  printf("got it open dude \n");
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
  printf("in the middle \n");
  while(fgets(ans, 256, fa) != NULL){
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
  printf("open sesame \n");
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
  printf("near end \n");
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
  char * winner = "Sorry the asnwering service is down";
  strcpy(winnerglob,winner);
  printf("%s \n", winnerglob);
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
