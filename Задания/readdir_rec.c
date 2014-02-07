#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <fcntl.h>
//#define _BSD_SOURCE


/*
int fdsHome[2];
int fdsSave[2];
struct dirent *curFileHome;
struct dirent *curFileSave;

void lock(int *fds)
{
	char test;
	if((read(fds[0], &test, 1)) < 0 ){
		perror("read");
	}
};

void unlock(int *fds)
{
	char test;
	if((write(fds[1], &test, 1)) < 0){
		perror("write");
	}
};
*/
int direc_counter = 0;

int backup(char* name, char* backup_dir ){

	int ret = 0;
	int fd_backup, fd_home;
	int test = 0, test_1 = 0;
	char path_backup_test[PATH_MAX];
	char path_home_test[PATH_MAX];
	char path_backup[PATH_MAX];
	char path_home[PATH_MAX];
	char new_name[PATH_MAX];
	char path_backup_gz[PATH_MAX];
	char* buf;
	struct stat check_backup, check_home;
	struct dirent *dp;
	struct dirent *result;
	int len = offsetof(struct dirent, d_name) + pathconf(name, _PC_NAME_MAX) + 1;
	dp = malloc(len);
	DIR* dir;
	char* name_path;
	char* path_test;

	sprintf(path_home_test, "%s/%s", name, dp->d_name);
	printf("64:Clearing path: %s\n", path_home_test);

	path_test = realpath(path_home_test, path_home);
	if(path_test == NULL){
		perror("realpath");
		ret = -1;
		goto err3;
	}
	printf("72:New path is: %s\n", path_home);


//	system("pwd");
	printf("76: opening '%s'\n", path_home);
	if(!(dir = opendir(path_home))){
		perror("opendir");
		ret = -1;
	}
	direc_counter++;
	//printf("%s :\n", name);

	while (1) {
		printf("85: Checking '%s'\n", dp->d_name);
		errno = 0;
		test = readdir_r(dir, dp, &result);
		if (result == NULL){
			printf("This is the last file\n");
			break;
		}
		if(strcmp(name, "."))
			name_path = &(name[2]);
		if((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0)){
			sprintf(path_backup, "%s/%s/%s", backup_dir, name_path, dp->d_name);
		} else {
			sprintf(path_backup, "%s/%s", backup_dir, name_path);
		}





		if(dp->d_type == DT_DIR){
			printf("99: STATing %s\n", path_backup);
			if((stat(path_backup, &check_backup) != 0) && (errno == ENOENT) && (strcmp(path_backup, backup_dir) != 0)){
				printf("101: making %s\n", path_backup);
				if((mkdir(path_backup, 0777) != 0)){
					perror("mkdir");
					ret = -1;
					goto err3;
				}

			} else {
				perror("stat");
				ret = -1;
				goto err3;
			}

			if((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0) ){
				sprintf(new_name, "%s/%s", path_home, dp->d_name);
				printf("116: backuping %s\n", new_name);
				ret = backup(new_name, backup_dir);
			}

		} else if((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0) && (strcmp(dp->d_name, " ") != 0)){
/*
		printf("122:Clearing path: %s\n", path_backup_test);

		path_test = realpath(path_backup_test, path_backup);
		if(path_test == NULL){
			perror("realpath");
			ret = -1;
			goto err3;
		}

		printf("131:New path is: %s\n", path_backup);
*/

		sprintf(path_backup_gz, "%s.gz", path_backup);

//		errno = 0;
		printf("137: STATing %s\n", path_backup_gz);
		test = stat(path_backup_gz, &check_backup);

		if(test == 0){
			printf("141: STATing %s\n", path_home);
			if((test_1 = stat(path_home, &check_home)) != 0){
				perror("stat");
				ret = -1;
				goto err3;
			}
			if(check_backup.st_ctime < check_home.st_ctime){
				printf("148: opening %s\n", path_backup);
				if((fd_backup = open(path_backup, O_RDWR|O_CREAT, /*check_home.st_mode*/0666)) == -1){
					perror("open");
					ret = -1;
					goto err1;
				}
				printf("154: opening %s\n", path_home);
				if((fd_home = open(path_home, O_RDWR)) == -1){
					perror("open");
					ret = -1;
					goto err1;
				}
				printf("156: truncate %s\n", path_backup);
				if((ftruncate(fd_backup, check_home.st_size)) < 0){
					perror("ftruncate");
					ret = -1;
					goto err2;
				}
				printf("166: copying %s\n", path_home);
				sendfile(fd_backup, fd_home, 0, check_home.st_size);
			}
		} else {
			if(errno == ENOENT){
				printf("171: opening %s\n", path_home);
				if((fd_home = open(path_home, O_RDWR)) == -1){
					perror("open");
					goto err2;
					ret = -1;
				}
				printf("177: opening %s\n", path_backup);
				if((fd_backup = open(path_backup, O_CREAT|O_RDWR, /*check_home.st_mode*/0666)) == -1){
					perror("open");
					goto err1;
					ret = -1;
				}
				printf("183: truncate %s\n", path_backup);
				if((ftruncate(fd_backup, check_home.st_size)) < 0){
					perror("ftruncate");
					ret = -1;
					goto err1;
				}
				printf("189: copying %s\n", path_home);
				sendfile(fd_backup, fd_home, 0, check_home.st_size);
			} else {
//				perror("stat");
//				ret = -1;
			}
		}
		pid_t pid;
		printf("197: Forking and GZIPing\n");
		pid = fork();
		if(pid < 0){
			perror("fork");
//			ret = -1;
//			goto err1;
		} else if(pid == 0){
			execlp("gzip", "gzip", "-n", path_backup, NULL);
			perror("execlp");
			return -1;
		}
		wait(NULL);

		}
	}
err1:
	close(fd_backup);
err2:
	close(fd_home);
err3:
	closedir(dir);
err4:
	direc_counter--;
return ret;
}

int main(int argc, char** argv){
	if(argc != 3){
		printf("Please input two names of dirrectories\nUsage: ./backup <home directory> <backup directory>\n");
		return -1;
	} else {
//		char back_up[PATH_MAX];
//		char home[PATH_MAX];
		int ret;

		printf("232:Changing path: %s\n", argv[1]);

		if((realpath(argv[1], home)) == NULL){
			perror("realpath");
			return -1;
		}
		printf("238:New name is: %s\n", home);
		printf("239:Changing path: %s\n", argv[2]);

		if((realpath(argv[2], back_up)) == NULL){
			perror("realpath");
			return -1;
		}
		printf("245:New name is %s\n", back_up);
		printf("246:Checking %s and %s\n", home, back_up);
		int len = strlen(home);
		if(strncmp(home, back_up, len) != 0)
			ret = backup(argv[1], back_up);
		else {
			printf("Backup directory shouldn't be in home directiry\n");
			ret = -1;
		}

return ret;
}
}
