#include "networking.h"
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>
#define SHMSZ 27

int main(int argc, char **argv) {
  int server_socket;
  char buffer[BUFFER_SIZE];
  int shmid;
  key_t key;
  int *shm, *pids;
  key = 5678;
  shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
  shm = shmat(shmid, NULL, 0);
  pids = shm;
  int beg;
  int oplace=0;
  if(pids[6]==0){
    if (argc == 2)
      server_socket = client_setup( argv[1]);
    else
      server_socket = client_setup( TEST_IP );
  
  }
  else{
    printf("server is full please try again at a later time");
    exit(0);
  }
  FILE *f = fopen("questions.txt", "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);  //same as rewind(f);
  char *line = malloc(fsize + 1);
  fread(line, fsize, 1, f);
  char ** args = calloc(6, sizeof(line));
  char * s = strdup(line);
  int i = 0;
  while(args[i] = strsep(&s, "\n")){
    i++;
  }
  i=0;
  while(args[i]!=NULL){
    i++;
  }
  args[i-1]=NULL;
  fclose(f);
  while (1) {
    if(pids[1]>oplace){
       if(beg!=1 &&pids[6]==1){
	 beg=1;
	 printf("Let the Games Begin \n");
       }
      printf("%s\n",args[pids[1]]);
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
      write(server_socket, buffer, sizeof(buffer));
      read(server_socket, buffer, sizeof(buffer));
      printf("received: [%s]\n", buffer);
      oplace++;
    }
  }
}
