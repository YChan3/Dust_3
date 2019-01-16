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
  int oplace=0;;
  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  
  
  while (1) {
    if(pids[1]>oplace){
      printf("enter data: ");
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
      write(server_socket, buffer, sizeof(buffer));
      read(server_socket, buffer, sizeof(buffer));
      printf("received: [%s]\n", buffer);
      oplace++;
    }
  }
}
