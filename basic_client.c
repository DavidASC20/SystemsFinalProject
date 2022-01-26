#include "pipe_networking.h"


int main() {

  int socket;
  printf("Enter ip: ");
  char ip[1000];
  fgets(ip, sizeof(ip), stdin);
  socket = client_handshake(ip);
  while(1) {      //while boardstate == 0 , see what server is doing and mimic on the other end

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
