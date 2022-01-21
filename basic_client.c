#include "pipe_networking.h"


int main() {

  int socket;

  socket = client_handshake();

  while(1) {

      printf("Enter input: ");
      char line[1000];
      fgets(line, sizeof(line), stdin);
      write(socket, line, strlen(line));
      printf("Response: ");
      char line2[1000];
      read(socket, line2, sizeof(line2));
      printf("%s\n", line2);
    }
}
