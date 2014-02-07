#include <fstream> // Для чтения из файла
#include <iostream> // Для вывода в консоль
#include <vector> // Для использования шаблона динамического массива - вектора
#include <algorithm> // Для сортировки вектора

#include <sys/types.h> // Для типа pid_t
#include <unistd.h> // Для функций fork(), exec() и sleep()
#include <wait.h> // Для функции waitpid()

using namespace std; // Стандартное пространство имён

struct Program{ // Структура, содержащая пары Время-Команда
	unsigned long long WaitingTime; // Время ожидания перед запуском
	char CommandName[20]; // Имя команды для выполнения
};

bool compare(Program a, Program b){ // Функция-компаратор
	return a.WaitingTime < b.WaitingTime;
};

vector<Program> Programs; // Основной вектор, в котором хранятся команды

void ReadFile(const char FileName[]){
	ifstream File(FileName); // Подключаем файл, из которого будем читать команды
	Program Temp; // Временная переменная, в которой хранится текущая команда перед добавлением в вектор
	while (!File.eof()){ // Цикл выполнется пока не достигнут конец файла
		File >> Temp.WaitingTime >> Temp.CommandName; // Считываем время и команду во временную переменную
		Programs.push_back(Temp); // Добавляем новые данные в конец вектора
	}
	// В некоторых случаях eof может работать некорректно и последняя команда считается дважды
	File.close(); // Закрываем файл на всякий случай
};

void Run(){
	vector<Program>::iterator it; // Создаём итератор для удобной работы с элементами вектора
	it = Programs.begin(); // Присваиваем итератору первый элемент вектора
	pid_t ProcessIdentifier; // Идентификатор процесса (pid)
	while (it!=Programs.end()){
		ProcessIdentifier = fork(); // Создаём дочерний процесс
		if (ProcessIdentifier > 0){ // Если процесс родительский 
			it++;
			continue; // Переходим на следующую итерацию для нового форка
		}
		else if (ProcessIdentifier == 0){ // Если процесс дочерний 
			sleep(it->WaitingTime); // Ждём перед выполнением команды
			execl(it->CommandName, it->CommandName, NULL); // Выполняем команду
		}
		else{ // В случае возникновения ошибки
			cout << "Error" << endl;
			break;
		}
	}
	Programs.clear(); // Очищаем вектор
	waitpid(ProcessIdentifier,NULL,0); // Ждём завершения последнего дочернего процесса
};

int main(){ // Основная программа
    const char s[20]="commands.txt";
    ReadFile(s); // Подпрограмма, заполняющая вектор командами из файла
	stable_sort(Programs.begin(),Programs.end(),compare); // Сортируем вектор по возрастанию времени
	Run(); // Подпрограмма, выполняющая команды из вектора
	return 0;
};