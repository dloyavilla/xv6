
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"
char *newargv[] = {};

int
main(int argc, char **argv)
{
  int i, start, elapsed;
  struct rusage ru;
  // check if we have two arguments
  if (argc < 2){
  	printf("Usage: time <comm> [args...]");
        exit(-1);
   }
 // shifting left and 0
  for(i=1; i<sizeof(argv); i++) {
  	newargv[i-1] = argv[i];
  }
  newargv[sizeof(argv)-1] = 0;
  // uptime and child 
  start = uptime();
  printf("Time: %d\n", start);
  int pid = fork();
  
  if(pid == -1) {
  	printf("fork failed\n");
  	exit(1);
  } else if (pid == 0) {
  	// call exec
  	exec(newargv[0], newargv);
  	printf("exec failed\n");
  	exit(1);
  } else {
  	// get the cputime 
  	int wpid = wait2(0, &ru);
  	elapsed = uptime() - start;
        printf("elapsed time: %d ticks, cpu time: %d ticks, %d% CPU\n", elapsed, ru.cputime, ru.cputime*100/elapsed);
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
