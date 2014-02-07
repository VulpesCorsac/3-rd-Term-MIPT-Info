#include <cstdlib> // Для функции strtoull
#include <iostream> // Для ввода/вывода в стандартный поток
#include <csignal> 

#include <unistd.h> // Для функций fork() и execl()
#include <sys/types.h> // Для типа pid_t
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std; // Стандартное пространство имён

unsigned long long NumberOfRunningPrograms=0; // Количество работающих на данный момент дочерних программ

void SignalHandler(int sig){ // Функция-обработчик сигналов
	NumberOfRunningPrograms--; // Уменьшаем счётчик
};

int main(int argc, char* argv[]){
	signal(SIGCHLD, SignalHandler); // При закрытии дочерней программы вызывается функция SignalHandler()
	unsigned long long N = strtoull(argv[1],NULL,10); // Максимально допустимое количество одновременно работающих дочерних программ, полученное из командной строки
	char CommandName[20]; // Имя команды для выполнения
	pid_t ProcessIdentifier; // Идентификатор процесса (pid)
	while (true /*!EOF*/){ // Бесконечный цикл
		cin >> CommandName; // Считываем имя команды из консоли
		if (CommandName != ""){ // Команда не пуста
			if (NumberOfRunningPrograms <= N){ // Если количество запущенных программ не превышает допустимого
				ProcessIdentifier = fork(); // Создаём дочерний процесс
				if (ProcessIdentifier > 0) // Если процесс родительский
					continue; // Ничего не делаем, едем дальше
				else if (ProcessIdentifier == 0){ // Если процесс дочерний
					NumberOfRunningPrograms++; // Инкрементируем счётчик запущенных программ
					execl(CommandName, CommandName, NULL); // Выполняем в нём полученную команду
				}
				else { // В случае ошибки
					cout << "Ошибка" << endl; // Сообщаем об этом
					continue; // Едем дальше
				}
				CommandName = ""; // Обнуляем команду
			}
			else{ // Если программ и так запущено много
				cout << "Превышен предел одновременно запущенных приложений" << endl;
				continue;
			}
		}
	}
	return 0;
};
