#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
char *newargv[] = {};

int
main(int argc, char **argv)
{
  // time 
  int i, start, elapsed;
  
  // shifting left 
  for(i=1; i<sizeof(argv); i++) {
  	newargv[i-1] = argv[i];
  }
  
  // adding 0 at the end 
  newargv[sizeof(argv)-1] = 0;
  start = uptime();
  
  // start time
  printf("Time: %d\n", start);
  
  // child
  int pid = fork();
  
  // catching if child was created 
  if(pid == -1) {
  	printf("fork failed\n");
  	exit(1);
  } else if (pid == 0) {
  
  	// calling with shifts 
  	exec(newargv[0], newargv);
  	printf("exec failed\n");
  	exit(1);
  } else {
  
  	// calling wait
  	int wpid = wait((int *) 0);
  	elapsed = uptime() - start;
        printf("Elapsed time: %d\n", elapsed);
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
