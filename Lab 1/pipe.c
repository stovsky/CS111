#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>


int pipe_args(int argc, char *argv[]) {

  int fd[2];
  int idx = 1;
  int err = 0;
  
  for (; idx < argc - 1; idx++) {

    // New pipe for each command
    errno = 0;
    err = pipe(fd);
    if (err == -1) {
      perror("Error with pipe");
      return errno;
    }

    pid_t pid = fork();
    errno = 0;
    if (pid < 0) {
      perror("Error with fork");
      return errno;
    }
    
    else if (pid == 0) {

      // Child process
      
      close(fd[0]);

      errno = 0;
      err = dup2(fd[1], 1);
      if (err == -1) {
	perror("Error with dup2");
	return errno;
      }
      
      close(fd[1]);
      
      errno = 0;
      err = execlp(argv[idx], argv[idx], (char*)0);
      if (err == -1) {
	errno = ECHILD;
	perror("Error with execlp");
	return errno;
      }
      
    }
    else {

      // Parent process
      
      close(fd[1]);

      errno = 0;
      err = dup2(fd[0], 0);
      if (err == -1) {
	perror("Error with dup2");
	return errno;
      }
      close(fd[0]);
                  
      errno = 0;
      err = wait(NULL);
      if (err == -1) {
	perror("Error with wait");
	return errno;
      }
            
      
    }
  }

  
  errno = 0;
  err = execlp(argv[idx], argv[idx], (char*)0);
  if (err == -1) {
    perror("Error with execlp");
    return errno;
  }

    return 0;
}


  
int main(int argc, char *argv[]) {


   int ret;

   // Check number of arguments
   errno = 0;
   if (argv[1] == NULL) {
     errno = EINVAL;
     perror("Requires at least 1 argument");
     ret = errno;
   }
   // Go into pipe
   else {
     ret = pipe_args(argc, argv);
   }
      
    return ret;
}



