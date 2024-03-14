#include <iostream>
#include <stdlib.h> 
#include <iomanip>
#include <ctime>
using namespace std;
const int maxSize = 10;
int s = 0;
int numS = 0;
double matrix[10][10] = {};
bool checkZeroLine(double matrix[10][10], int size) {
	bool res = 1;
	for (int x = 0; x < size; x++) {
		res = 1;
		for (int y = 0; y < size; y++) {
			if (matrix[x][y] != 0) {
				res = 0;
				break;
			}

		}
		if (res == 1) {
			return res;
		}
	}
	for (int x = 0; x < size; x++) {
		res = 1;
		for (int y = 0; y < size; y++) {
			if (matrix[y][x] != 0) {
				res = 0;
				break;
			}

		}
		if (res == 1) {
			return res;
		}
	}
	return res;

}
int inpData(int& size, int& numStroke) {
	cout << "Введите  размер квадратной матрицы не больше 10, а также номер строки " << endl;

	cin >> size;
	cin >> numStroke;
	if (size > 10) {
		cout << "Неверно задан размер матрицы" << endl;
		system("pause");
		return 0;
	}
	if (size < numStroke) {
		cout << "Неверно задана строка разложения" << endl;
		system("pause");
		return 0;
	}
}
void fillKey() {
	cout << "Введите числа в виде таблицы: " << endl;
	for (int x = 0; x < s; x++) { // двойной цикл для заполнения массива
		for (int y = 0; y < s; y++) {
			cin >> matrix[y][x]; // ввод посредством консоли
		}
	}
}
void fillRand() {
	for (int x = 0; x < s; x++) {// двойной цикл для заполнения массива
		for (int y = 0; y < s; y++) {
			matrix[y][x] = rand();// ввод посредством рандома
		}
	}
}
void fillNat() {
	int count = 1;
	for (int x = 0; x < s; x++) { // двойной цикл для заполнения массива
		for (int y = 0; y < s; y++) {
			matrix[y][x] = count;// ввод посредством переменной изменяющейся с итерациями цикла и явся натуральным числом
			count++;
		}
	}
}
void fillMatrix(int size) {
	short int method = 0;
	cout << "Введите номер способа заполнения массива, он заполнится по столбцам сверху вниз: " << endl;
	cout << "1 для ввода с клавиатуры" << endl;
	cout << "2 для заполнения случайными числами" << endl;
	cout << "3 для заполнения натуральными числами" << endl;
	cin >> method;
	if (method == 1) {
		fillKey();
	}
	else if (method == 2) {
		fillRand();
	}
	else if (method == 3) {
		fillNat();
	}
	else {
		cerr << "Неверно введен способ. Повторите попытку:" << endl;
	}


}
void outMatrix(int size, double matrix[10][10]) { // (размер матрицы, матрица)
	cout << setw(3) << " ";
	for (int y = 1; y <= size; y++) {
		cout << setw(15) << right << y; //вывод номеров столбцов
	}
	cout << endl;
	for (int x = 0; x < size; x++) {
		cout << setw(3) << x + 1 << "  ";//вывод номеров строк

		for (int y = 0; y < size; y++) {

			cout << setw(15) << right << matrix[x][y];//вывод элементов матриц

		}
		cout << endl;
	}
}



double computeDetofLittle(double matrix[10][10], int size) { //(матрица,размер матрицы)
	if (checkZeroLine(matrix, size)) { // проверка на наличие нулевой строки столбца
		return 0;
	}
	if (size == 3) { // вычисления определителя 3 порядка
		return
			matrix[0][0] * matrix[1][1] * matrix[2][2] +
			matrix[0][2] * matrix[1][0] * matrix[2][1] +
			matrix[2][0] * matrix[0][1] * matrix[1][2] -
			matrix[2][0] * matrix[1][1] * matrix[0][2] -
			matrix[0][0] * matrix[2][1] * matrix[1][2] -
			matrix[2][2] * matrix[1][0] * matrix[0][1];
	}
	else if (size == 2) {// вычисления определителя 2 порядка

		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else {// вычисления определителя 1 порядка
		return matrix[0][0];
	}
}

double computeDet(double matrix[10][10], int numofStroke, int size) { //(матрица,номер строки для разложения, размер матрицы)
	if (checkZeroLine(matrix, size)) {// проверка на наличие нулевой строки столбца
		return 0;
	}
	numofStroke -= 1; // смещение
	double result = 0; // переменная результата

	if (size < 4) { // проверка на размер массива 
		result = computeDetofLittle(matrix, size);
	}
	else {
		double arr[maxSize][maxSize] = {}; // массив меньшей размерности для разложения

		for (int i = 0; i < size; i++) {
			int biasX = 0;

			for (int x = 0; x < size - 1; x++) {
				int biasY = 0;
				for (int y = 0; y < size - 1; y++) {
					if (x == numofStroke) {


						biasX = 1;

					}
					if (y == i) {
						biasY = 1;

					}
					arr[x][y] = matrix[x + biasX][y + biasY]; // заполнения массива всех элементов кроме элементов на пересечении главного элемента
				}
			}
			if ((i + numofStroke) % 2 == 0) { // знак алгебраического дополнения 
				result += matrix[numofStroke][i] * computeDet(arr, 1, size - 1); // рекурсивный вызов функции для вычисления определителя массива меньшей размерности и умножить на алг дополнение и прибавка к результату
			}
			else {
				result += -(matrix[numofStroke][i]) * computeDet(arr,1, size - 1);
			}
		}
	}
	
	return result; 
}

double toGauss(double matrix[10][10], int size) {
	double res = 1; // переменная результата
	double temp = 0; // переменная для  перестановки
	for (int y = 0; y < size; y++) {
		double mainVar = matrix[y][y]; // элемент главной диагонали
		if (mainVar == 0) {
			temp = 0;
			for (int i = 0; i < size; i++) {
				if (matrix[i][y] != 0) { //нахождение ненулевого элемента
					bool flag = 1;
					for (int f = 0; f < y + 1; f++) {

						if (matrix[i][f] != 0) {
							flag = 0;
							break;
						}
					}
					if (flag == 1) {
						for (int p = 0; p < size; p++) {
							temp = matrix[i][p]; //перестановка строк
							matrix[i][p] = matrix[y][p];
							matrix[y][p] = temp;

						}
						break;
					}


				}
			}
		}
		mainVar = matrix[y][y]; // элемент главной диагонали
		double k = 0; 
		if (mainVar != 0) {
			for (int i = y + 1; i < size; i++) {
				k = -matrix[i][y] / mainVar; // вычисление коэффициента для строк
				for (int j = 0; j < size; j++) {
					matrix[i][j] += k * matrix[y][j]; // прибавка к строкам
				}
			}
		}
	}
	for (int l = 0; l < size; l++) {
		res *= matrix[l][l]; // нахождения определителя путем умножения элементов главной диагонали
	}
	for (int x = 1; x < size; x++) { // приведение Гаусса к нормальному виду
		for (int y = 0; y < x; y++) {
			if (matrix[x][y] < 6e-10) {
				matrix[x][y] = 0;
			}
		}
	}
	return res;
}

int main() {
	setlocale(LC_ALL, "Russian");
	inpData(s, numS); 
	fillMatrix(s);
	outMatrix(s, matrix);
	int time1 = clock();
	
	double det1 = computeDet(matrix, numS, s);
	int time2 = clock();
	double sec = (10e3 * (time2 - time1)) / CLOCKS_PER_SEC;

	cout << "Время при вычислении определителя: " << sec << " mc" << endl;
	
	double det2 = toGauss(matrix, s);
	int time4 = clock();
	double secD = (10e3 * (time4 - time2)) / CLOCKS_PER_SEC;
	cout << "Время при вычислении определителя Гаусса: " << secD << " mc" << endl;

	double diff = det2 - det1;
	cout << "Вывод Матрицы Гаусса:" << endl;
	outMatrix(s, matrix);
	cout << "Определитель входной матрицы: " << det1 << endl;
	cout << "Определитель матрицы Гаусса: " << det2 << endl;
	cout << "Разность между двумя определителями: " << diff << endl;
	system("pause");
	return 0;
}

