#include "pipe_networking.h"


static void sighandler(int signo){
  if (signo == SIGINT) {
    remove("WKP");
    exit(0);
  }
}

int main() {
  signal(SIGINT,sighandler);

  int to_client;
  int from_client;
  char input[BUFFER_SIZE];

  while(1){
    from_client = server_handshake( &to_client );

    if(from_client){
      while(read(from_client, input, BUFFER_SIZE)){
        printf("Recieved %s\n", input);
        // sprintf(input, "%s %s", "Hello", "world");
        write(to_client, "your input was %ld characters.\n", strlen(input));
      }
    }
  }
}
