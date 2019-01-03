#include "pipe_networking.h"

char * SERVER_PIPE = "WKP";
/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
// int server_handshake(int *to_client) {
//   mkfifo(SERVER_PIPE,0666);
//   printf("Server: Created server to client pipe\n");
//   int client_server = open(SERVER_PIPE,O_RDONLY);
//
//   char pipe_name[HANDSHAKE_BUFFER_SIZE];
//   read(client_server, pipe_name, HANDSHAKE_BUFFER_SIZE);
//   printf("Server: Read server to client pipe name\n");
//
//   remove(SERVER_PIPE);
//   printf("Server: Removed server to pipe\n");
//
//   int server_client = open(pipe_name,O_WRONLY);
//   write(server_client,ACK,HANDSHAKE_BUFFER_SIZE);
//   printf("Server: sent %s to client\n",ACK);
//
//   char acknowledgement[HANDSHAKE_BUFFER_SIZE];
//   read(client_server, acknowledgement, HANDSHAKE_BUFFER_SIZE);
//   printf("Server: Recieved %s\n", acknowledgement);
//
//   *to_client = server_client;
//   return client_server;
// }

int server_handshake(int *to_client) {
  mkfifo(SERVER_PIPE,0666);
  printf("Server: Created server to client pipe\n");
  int client_server = open(SERVER_PIPE,O_RDONLY);

  char pipe_name[HANDSHAKE_BUFFER_SIZE];
  read(client_server, pipe_name, HANDSHAKE_BUFFER_SIZE);
  printf("Server: Read server to client pipe name\n");

  remove(SERVER_PIPE);
  printf("Server: Removed server to pipe\n");

  int f = fork();
  if(f) return 0;

  int server_client = open(pipe_name,O_WRONLY);
  write(server_client,ACK,HANDSHAKE_BUFFER_SIZE);
  printf("Server: sent %s to client\n",ACK);

  char acknowledgement[HANDSHAKE_BUFFER_SIZE];
  read(client_server, acknowledgement, HANDSHAKE_BUFFER_SIZE);
  printf("Server: Recieved %s\n", acknowledgement);

  *to_client = server_client;
  return client_server;
}

// int subserver_handshake(int *to_client){
//   if(!fork()){
//     int server_client = open(pipe_name,O_WRONLY);
//     write(server_client,ACK,HANDSHAKE_BUFFER_SIZE);
//     printf("Server: sent %s to client\n",ACK);
//
//     char acknowledgement[HANDSHAKE_BUFFER_SIZE];
//     read(client_server, acknowledgement, HANDSHAKE_BUFFER_SIZE);
//     printf("Server: Recieved %s\n", acknowledgement);
//
//     *to_client = server_client;
//     return client_server;
//   }
//   else{
//     close(client_server);
//   }
// }


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  mkfifo("client_pi",0666);
  printf("Client: Created client to server pipe\n");

  int client_server = open(SERVER_PIPE,O_WRONLY);
  char pipe_name[HANDSHAKE_BUFFER_SIZE] = "client_pi";
  write(client_server, pipe_name, HANDSHAKE_BUFFER_SIZE);
  printf("Client: Sent client to server pipe name\n");

  int server_client = open("client_pi",O_RDONLY);
  char acknowledgement[HANDSHAKE_BUFFER_SIZE];
  read(server_client, acknowledgement, HANDSHAKE_BUFFER_SIZE);
  printf("Client: Recieved %s\n", acknowledgement);

  remove("client_pi");
  printf("Client: Removed client to server pipe\n");

  write(client_server, acknowledgement, HANDSHAKE_BUFFER_SIZE);
  printf("Client: Sent acknowledgement back to server\n");

  *to_server = client_server;
  return server_client;
}
