#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

int main() {
  signal(SIGINT, signalhandler);
  int to_client, from_client;
  char buffer[BUFFER_SIZE];
  while(1){
    from_client = server_handshake(&to_client);
    while(read(from_client, buffer, sizeof(buffer)));
    process(buffer);
    write(to_client, bugger, sizeof(buffer));
}
  //gotta add the fork in!!
  
void subserver(int from_client) {
}

void process(char * s) {
  
}
