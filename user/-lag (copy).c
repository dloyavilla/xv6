#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char *argv[] = {"matmul", 0 };

int
main()
{
  printf("Time: %d\n", uptime());
  int pid = fork();
  if(pid == -1) {
  	printf("ls -lag: fork failed\n");
  	exit(1);
  } else if (pid == 0) {
  	exec("user/time1", argv);
  	printf("time1: exec failed\n");
  	exit(1);
  } else {
  	int wpid = wait((int *) 0);
  	printf("elapsed time: %d\n", uptime());
  	if(wpid == pid){
        // the shell exited; restart it.
        exit(1);
      } else if(wpid < 0){
        printf("time1: wait returned an error\n");
        exit(1);
      } else {
        // it was a parentless process; do nothing.
      }	
  }
  exit(0);
}
