#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;
  char input[BUFFER_SIZE];

  from_server = client_handshake( &to_server );
  while(1){
    if(read(from_server, input, BUFFER_SIZE)){
      printf(input);
    }
    printf("%s\n", "What is the input");
    fgets(input, BUFFER_SIZE, stdin);
    strtok(input, "\n");
    write(to_server, input, BUFFER_SIZE);
  }
}
