#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void signalhandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

int main() {
  signal(SIGINT, signalhandler);
  int to_client, from_client;
  //char buffer[BUFFER_SIZE];
  while(1){
    from_client = server_setup();
    if(!fork()){
      subserver(from_client);
    }
    else{
      remove("luigi");
      printf("[server] handshake: removed wkp\n");
      close(from_client);
    }
  }
}
/*  
    from_client = server_handshake(&to_client);
    while(read(from_client, buffer, sizeof(buffer)));
    process(buffer);
    write(to_client, bugger, sizeof(buffer));
}
*/
  
void subserver(int from_client) {
  char b[256];
  int to_client = server_connect(from_client);
  while(read(from_client,b,sizeof(b))){
    printf("Subserver %d: Received [%s] from [%d]\n",getpid(), b, from_client);
    process(b);
    write(to_client, b, sizeof(b));
    printf("Subserver %d: Wrote[%s] to [%d]\n", getpid(), b, to_client);
  }
}

void process(char * s) {
  int x = 0;
  while(x<strlen(s)){
    if(s[x] == 32){
      s[x] = '_';
    }
    x++;
  }
}
