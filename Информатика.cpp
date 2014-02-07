Семинар 1 {
	chmod - смена прав доступа
	Sample {
		#include <stdio.h>
		#include <unistd.h>
		#include <sys/types.h>
		int main() {
			printf("My uid = %d\n, My gid = %d\n", getuid(), getdid());
			return 0;
		}
	}
}

Семинар 2 {
	Sample {
		#include <unistd.h>
		int main(int argc,char** argv) {
			if (argc != 3)
				return -1;
			int id = fork();
			if (id == -1)
				printf("Error in forking");
			if (id > 0) {
				prinft("Parent, ppid = %d, my ppid = ", getppid(), getpid());
				execvp("ps", "");
			}
			if (id == 0)
				prinft("Child, ppid = %d, my ppid = ", getppid(), getpid());
			return 0;
		}
	}
}

Семинар 3 {
	IP - 192.168.7.8
	env - просмотр окружения
	
	Sample { 
		#include <unistd.h>
		int main(int srgc, char* argv[]) {
			int pid = fork();
			if (pid == -1)
				return -1;
			if (pid == 0) {
				if (argc >= 3) {
					execvp(argv[1], &argv[1]); // Да, Hell, 1, а не 2!!!
				}
				if(argc >= 4) {
					execlp(argv[1], argv[1], argv[2], argv[3], NULL); //под вызов temp ls -al /
				}
			} else {
			
			}
			return 0;
		}
	}
	
	echo $USER - user == переменная
	MYVAR=home - добавление переменной в локальное окружение
	export MYVAR - экспорт переменной
	int main(int argc, char** argv, char** envp) - получение переменных окружения
	
	Sample {
		#include <stdio.h>
		int main(int argc, char** argv, char** envp) {
			int i;
			for (i = 0; envp[i] != NULL; printf("%s \n", envp[i++]);
			return 0;
		}
	}
	
	Sample {
		#include <stdio.h>
		int main(int argc, char** argv, char** envp) {
			FILE* fd = fopen(argv[1], "w+");
			fprintf(fd, "argv[2] = %s \n", argv[2]);
			fclose(fd);
			return 0;
		}
	}
	
	
}

Семинар 4 и т.д. {
	 Sample: {
		на флешке
	 }
}


