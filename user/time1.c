#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char *argv[])
{
  int i, start, elapsed;
  char *newargv[16];
  for(i=1; i<argc; i++) {
  	newargv[i-1] = argv[i];
  }
  newargv[argc-1] = 0;
  start = uptime();
  printf("Time: %d\n", start);
  int pid = fork();
  if(pid == -1) {
  	printf("fork failed\n");
  	exit(1);
  } else if (pid == 0) {
  	exec(newargv[0], newargv);
  	printf("exec failed\n");
  	exit(1);
  } else {
  	int wpid = wait((int *) 0);
  	elapsed = uptime() - start;
        printf("Time: %d\n", elapsed);
  	if(wpid == pid){
        // the shell exited; restart it.
        exit(1);
      } else if(wpid < 0){
        printf("wait returned an error\n");
        exit(1);
      } else {
        // it was a parentless process; do nothing.
      }	
  }
  exit(0);
}
