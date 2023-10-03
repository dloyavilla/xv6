#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char *argv[] = {"-lag", 0 };

int
main()
{
  int pid = fork();
  if(pid == -1) {
  	printf("ls -lag: fork failed\n");
  	exit(1);
  } else if (pid == 0) {
  	exec("/bin/ls", argv);
  	printf("ls -lag: exec failed\n");
  	exit(1);
  } else {
  	int wpid = wait((int *) 0);
  	if(wpid == pid){
        // the shell exited; restart it.
        exit(1);
      } else if(wpid < 0){
        printf("ls -lag: wait returned an error\n");
        exit(1);
      } else {
        // it was a parentless process; do nothing.
      }	
  }
  exit(0);
}
