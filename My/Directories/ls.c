#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv) {
  char* dir;
  int fd;
  struct tm tim;
  struct stat str;
  dir = argv[1];
  DIR* current_dir = opendir(dir);
  struct dirent *current_file = readdir(current_dir);
  while (current_file != NULL) {
    printf("%s\n", current_file->d_name);
    current_file = readdir(current_dir);
    fd = open(current_file->d_name,  O_WRONLY | O_CREAT, 0666);
  
    fstat(fd, &str);
    
    printf("st_dev = %d\n", str.st_dev);
    printf("st_ino = %d\n", str.st_ino);
    printf("st_mode = %d\n", str.st_mode);
    printf("st_nlink = %d\n", str.st_nlink);
    printf("st_uid = %d\n", str.st_uid);
    printf("st_gid = %d\n", str.st_gid);
    printf("st_size = %d\n", str.st_size);
    printf("st_blksize = %u\n", str.st_blksize);
    printf("st_blocks = %u\n", str.st_blocks);

    printf("st_atime = %u\n", str.st_atime);
    tim = *gmtime(&(str.st_atime));
    printf("sec = %d\n", tim.tm_sec);
    printf("min = %d\n", tim.tm_min);
    printf("hour = %d\n", tim.tm_hour);
    printf("mday = %d\n", tim.tm_mday);
    printf("mon = %d\n", tim.tm_mon);
    printf("year = %d\n", tim.tm_year);
    printf("wday = %d\n", tim.tm_wday);
    printf("yday = %d\n", tim.tm_yday);
    printf("isdst = %d\n", tim.tm_isdst);

    printf("st_mtime = %u\n", str.st_mtime);
    tim = *gmtime(&(str.st_mtime));
    printf("sec = %d\n", tim.tm_sec);
    printf("min = %d\n", tim.tm_min);
    printf("hour = %d\n", tim.tm_hour);
    printf("mday = %d\n", tim.tm_mday);
    printf("mon = %d\n", tim.tm_mon);
    printf("year = %d\n", tim.tm_year);
    printf("wday = %d\n", tim.tm_wday);
    printf("yday = %d\n", tim.tm_yday);
    printf("isdst = %d\n", tim.tm_isdst);

    printf("st_ctime = %u\n", str.st_ctime);
    tim = *gmtime(&(str.st_ctime));
    printf("sec = %d\n", tim.tm_sec);
    printf("min = %d\n", tim.tm_min);
    printf("hour = %d\n", tim.tm_hour);
    printf("mday = %d\n", tim.tm_mday);
    printf("mon = %d\n", tim.tm_mon);
    printf("year = %d\n", tim.tm_year);
    printf("wday = %d\n", tim.tm_wday);
    printf("yday = %d\n", tim.tm_yday);
    printf("isdst = %d\n", tim.tm_isdst);
    printf("\n\n");
  }

  return 0;
}
