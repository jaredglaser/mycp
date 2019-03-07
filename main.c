#define  BUFFERSIZE 128
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  struct stat statbuf;
  char bufferinput[BUFFERSIZE];
  char yes[] = "y";
  char no[] = "n";
  char YES[] = "Y";
  char NO[] = "N";
  
  if(argc != 3){ //verify that two arguments are passed 
    printf("invalid number of arguments. Expected source and destination.\n");
    return 0;
  }
    int statfd = stat(argv[1],&statbuf);
    if(statfd < 0){
      printf("Error accessing File 1, it does not exist.\n");
      return 0;
    }
    int statfd2 = stat(argv[2],&statbuf);
    if(statfd2 >= 0){
      printf("mycp: overwrite %s? (y or n): ",argv[2]);
      int valid = 0;
      while(valid == 0){
        if(fgets(bufferinput, BUFFERSIZE , stdin) != NULL) {
          int len = strlen(bufferinput);
          bufferinput[len - 1] = '\0';   // override \n to become \0
          if(strcmp(bufferinput,yes) == 0||strcmp(bufferinput,YES) ==0 ){ //if they answered y or n
            valid = 1;
          }
          else if(strcmp(bufferinput,no) == 0 ||strcmp(bufferinput,NO) == 0){
            return 0;
          }
          if(valid == 0) //they did not enter a y or n
            printf("not valid input. Enter y or n: ");
        } 
        else { //they entered nothing
          printf("not valid input. Enter y or n: ");
		    }
      }
    }
    int fd, fd2;
    int amountRead;
    char buffer[128];
    fd = open(argv[1], O_RDONLY); //open the file we are reading from
    fd2 = open(argv[2], O_WRONLY|O_CREAT,statbuf.st_mode); //open the file we are writing to 
    if(fd >= 0 && fd2 >= 0){ //no errors with open, so we continue
      
      while ((amountRead = read(fd, &buffer, 128)) > 0){ //read 128 bytes at a time
        write(fd2,buffer,amountRead); //write these bytes to the other file
      }
    }
    else{
      printf("error opening files\n");
    }
    //close the files
    int closeVerify = close(fd) + close(fd2);
    if(closeVerify != 0){
      printf("Error closing files"); //notify user of error
    }
  return 0;
}
