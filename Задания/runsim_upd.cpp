#include <cstdlib> // ��� ������� strtoull
#include <iostream> // ��� �����/������ � ����������� �����
#include <csignal> 

#include <unistd.h> // ��� ������� fork() � execl()
#include <sys/types.h> // ��� ���� pid_t
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std; // ����������� ������������ ���

unsigned long long NumberOfRunningPrograms=0; // ���������� ���������� �� ������ ������ �������� ��������

void SignalHandler(int sig){ // �������-���������� ��������
	NumberOfRunningPrograms--; // ��������� �������
};

int main(int argc, char* argv[]){
	signal(SIGCHLD, SignalHandler); // ��� �������� �������� ��������� ���������� ������� SignalHandler()
	unsigned long long N = strtoull(argv[1],NULL,10); // ����������� ���������� ���������� ������������ ���������� �������� ��������, ���������� �� ��������� ������
	char CommandName[20]; // ��� ������� ��� ����������
	pid_t ProcessIdentifier; // ������������� �������� (pid)
	while (true /*!EOF*/){ // ����������� ����
		cin >> CommandName; // ��������� ��� ������� �� �������
		if (CommandName != ""){ // ������� �� �����
			if (NumberOfRunningPrograms <= N){ // ���� ���������� ���������� �������� �� ��������� �����������
				ProcessIdentifier = fork(); // ������ �������� �������
				if (ProcessIdentifier > 0) // ���� ������� ������������
					continue; // ������ �� ������, ���� ������
				else if (ProcessIdentifier == 0){ // ���� ������� ��������
					NumberOfRunningPrograms++; // �������������� ������� ���������� ��������
					execl(CommandName, CommandName, NULL); // ��������� � �� ���������� �������
				}
				else { // � ������ ������
					cout << "������" << endl; // �������� �� ����
					continue; // ���� ������
				}
				CommandName = ""; // �������� �������
			}
			else{ // ���� �������� � ��� �������� �����
				cout << "�������� ������ ������������ ���������� ����������" << endl;
				continue;
			}
		}
	}
	return 0;
};
