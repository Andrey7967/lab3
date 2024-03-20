#include <iostream> // cout, cin
#include <fstream> // ifstream, ofstream
using namespace std;
const
int LPG = 10, // размер страницы
LSTR = 80, // максимальная длина строки
NLEN = 20; // максимальная длина имени файла
ifstream Prg; // входной и
ofstream List; // выходной файлы
char Name[NLEN], // имя файла
Chr; // рабочий символ
int I = 1;
int Len, NoExist = 0; // рабочие переменные
int NextChar; // для обнаружения конца файла
int numPage = 0;
int main() {
	setlocale(LC_ALL, "Russian");
	// открытие выходного файла
	List.open("PRN1.cpp");
	do // начало цикла входных файлов
	{
		cout << "\n Введите имя файла ";
		cin >> Name;
		Prg.open(Name);// открытие входного файла
		I = 1;
		if (Prg) // обработка, если файл существует
		{
			cout << "File name - " << Name << endl;
			cout << I << " ";
			List << "File name - " << Name << endl;
			List << I << " ";
			while (Prg.get(Chr)) // цикл страниц
			{
				cout << Chr;
				List << Chr;
				if (I == 10) {
					I = 0;
					cin.get(); // press enter to go next page

				}
				if (Chr == '\n') {
					I++;
					cout << I << " ";
					List  << I << " ";
				}
				
				
				
			}
			cout << endl;
			List << endl;
			cout << "КОНЕЦ ВЫДАЧИ ОДНОГО ФАЙЛА";
		}
		else NoExist = 1;
		Prg.close();
	} while (!NoExist); // конец цикла входных файлов
	List.close();
	cout << "Прием файлов завершен, в связи с неверным именем входного файла" << endl;
	system("pause");
	return 0;
}