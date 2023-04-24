#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define FIFO_NAME "my_fifo"


int main(int argc, char const *argv[]) {
  /* code */
  int file_mode;

  if(argc <= 1) {
    perror("Please specify the file mode\n");
    exit(-1);
  } else {

    file_mode = argv[1][0] == 'r' ? O_RDONLY : O_WRONLY;
    printf("arg: %s\n", argv[1]);
    printf("chosen filemode: %s\n", file_mode == O_RDONLY ? "O_RDONLY" : file_mode == O_WRONLY ? "O_WRONLY" : "false");


  }

  int acs = access(FIFO_NAME, F_OK);

  if(acs == 0) {
    printf("Named pipe already exists!\n");
  } else if (errno != ENOENT){
    perror("Access error\n");
    exit(1);
  }else {
    //pipe doesn't exist
    int mkfifo_res = mkfifo(FIFO_NAME, 0666);
    if(mkfifo_res != 0) {
      perror("MKFIFO Error\n");
      exit(1);
    }
    printf("named pipe created successfully!\n");

  }

  printf("opening named pipe..\n");


  int fd =  open(FIFO_NAME, file_mode);

  if(fd == -1) {
    perror("open error\n");
    exit(1);
  }

  printf("named pipe opened!\n");

  if(argv[1][0] == 'r') {
    char buffer[128];
    printf("Reading from named pipe!\n");
    sleep(1);
    read(fd, buffer, sizeof(buffer));
    printf("Read from pipe: %s\n", buffer);

  } else {

    char buffer[128] = "Hello Reader!";
    printf("Writing to named pipe!\n");
    write(fd, buffer, sizeof(buffer));
    printf("Wrote to pipe: %s\n", buffer);

  }

  close(fd);
  return 0;
}
