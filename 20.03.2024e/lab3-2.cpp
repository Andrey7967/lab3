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
		for (int y = 0; y < size && res == 1; y++) {
			if (matrix[x][y] != 0) {
				res = 0;
				
			}

		}
		if (res == 1) {
			return res;
		}
	}
	for (int x = 0; x < size; x++) {
		res = 1;
		for (int y = 0; y < size && res == 1; y++) {
			if (matrix[y][x] != 0) {
				res = 0;
			
			}

		}
		if (res == 1) {
			return res;
		}
	}
	return res;

}
int inpData(int& size, int& numStroke) {
	cout << "�������  ������ ���������� ������� �� ������ 10, � ����� ����� ������ " << endl;

	cin >> size;
	cin >> numStroke;
	if (size > 10) {
		cout << "������� ����� ������ �������" << endl;
		system("pause");
		return 0;
	}
	if (size < numStroke) {
		cout << "������� ������ ������ ����������" << endl;
		system("pause");
		return 0;
	}
}
void fillKey() {
	cout << "������� ����� � ���� �������: " << endl;
	for (int x = 0; x < s; x++) { // ������� ���� ��� ���������� �������
		for (int y = 0; y < s; y++) {
			cin >> matrix[y][x]; // ���� ����������� �������
		}
	}
}
void fillRand() {
	for (int x = 0; x < s; x++) {// ������� ���� ��� ���������� �������
		for (int y = 0; y < s; y++) {
			matrix[y][x] = rand();// ���� ����������� �������
		}
	}
}
void fillNat() {
	int count = 1;
	for (int x = 0; x < s; x++) { // ������� ���� ��� ���������� �������
		for (int y = 0; y < s; y++) {
			matrix[y][x] = count;// ���� ����������� ���������� ������������ � ���������� ����� � ���� ����������� ������
			count++;
		}
	}
}
void fillMatrix(int size) {
	short int method = 0;
	cout << "������� ����� ������� ���������� �������, �� ���������� �� �������� ������ ����: " << endl;
	cout << "1 ��� ����� � ����������" << endl;
	cout << "2 ��� ���������� ���������� �������" << endl;
	cout << "3 ��� ���������� ������������ �������" << endl;
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
		cerr << "������� ������ ������. ��������� �������:" << endl;
	}


}
void outMatrix(int size, double matrix[10][10]) { // (������ �������, �������)
	cout << setw(3) << " ";
	for (int y = 1; y <= size; y++) {
		cout << setw(15) << right << y; //����� ������� ��������
	}
	cout << endl;
	for (int x = 0; x < size; x++) {
		cout << setw(3) << x + 1 << "  ";//����� ������� �����

		for (int y = 0; y < size; y++) {

			cout << setw(15) << right << matrix[x][y];//����� ��������� ������

		}
		cout << endl;
	}
}



double computeDetofLittle(double matrix[10][10], int size) { //(�������,������ �������)
	if (checkZeroLine(matrix, size)) { // �������� �� ������� ������� ������ �������
		return 0;
	}
	if (size == 3) { // ���������� ������������ 3 �������
		return
			matrix[0][0] * matrix[1][1] * matrix[2][2] +
			matrix[0][2] * matrix[1][0] * matrix[2][1] +
			matrix[2][0] * matrix[0][1] * matrix[1][2] -
			matrix[2][0] * matrix[1][1] * matrix[0][2] -
			matrix[0][0] * matrix[2][1] * matrix[1][2] -
			matrix[2][2] * matrix[1][0] * matrix[0][1];
	}
	else if (size == 2) {// ���������� ������������ 2 �������

		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else {// ���������� ������������ 1 �������
		return matrix[0][0];
	}
}

double computeDet(double matrix[10][10], int numofStroke, int size) { //(�������,����� ������ ��� ����������, ������ �������)
	if (checkZeroLine(matrix, size)) {// �������� �� ������� ������� ������ �������
		return 0;
	}
	numofStroke -= 1; // ��������
	double result = 0; // ���������� ����������

	if (size < 4) { // �������� �� ������ ������� 
		result = computeDetofLittle(matrix, size);
	}
	else {
		double arr[maxSize][maxSize] = {}; // ������ ������� ����������� ��� ����������

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
					arr[x][y] = matrix[x + biasX][y + biasY]; // ���������� ������� ���� ��������� ����� ��������� �� ����������� �������� ��������
				}
			}
			if ((i + numofStroke) % 2 == 0) { // ���� ��������������� ���������� 
				result += matrix[numofStroke][i] * computeDet(arr, 1, size - 1); // ����������� ����� ������� ��� ���������� ������������ ������� ������� ����������� � �������� �� ��� ���������� � �������� � ����������
			}
			else {
				result += -(matrix[numofStroke][i]) * computeDet(arr, 1, size - 1);
			}
		}
	}

	return result;
}

double toGauss(double matrix[10][10], int size) {
	double res = 1; // ���������� ����������
	double temp = 0; // ���������� ���  ������������
	for (int y = 0; y < size; y++) {
		double mainVar = matrix[y][y]; // ������� ������� ���������
		if (mainVar == 0) {
			temp = 0;
			bool flag = 0;
			for (int i = 0; i < size && flag == 0; i++) {
				if (matrix[i][y] != 0) { //���������� ���������� ��������
					flag = 1;
					for (int f = 0; (f < y + 1 ) && flag == 1; f++) {

						if (matrix[i][f] != 0) {
							flag = 0;
							
						}
					}
					if (flag == 1) {
						for (int p = 0; p < size; p++) {
							temp = matrix[i][p]; //������������ �����
							matrix[i][p] = matrix[y][p];
							matrix[y][p] = temp;

						}
						
					}


				}
			}
		}
		mainVar = matrix[y][y]; // ������� ������� ���������
		double k = 0;
		if (mainVar != 0) {
			for (int i = y + 1; i < size; i++) {
				k = -matrix[i][y] / mainVar; // ���������� ������������ ��� �����
				for (int j = 0; j < size; j++) {
					matrix[i][j] += k * matrix[y][j]; // �������� � �������
				}
			}
		}
	}
	for (int l = 0; l < size; l++) {
		res *= matrix[l][l]; // ���������� ������������ ����� ��������� ��������� ������� ���������
	}
	for (int x = 1; x < size; x++) { // ���������� ������ � ����������� ����
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

	cout << "����� ��� ���������� ������������: " << sec << " mc" << endl;

	double det2 = toGauss(matrix, s);
	int time4 = clock();
	double secD = (10e3 * (time4 - time2)) / CLOCKS_PER_SEC;
	cout << "����� ��� ���������� ������������ ������: " << secD << " mc" << endl;

	double diff = det2 - det1;
	cout << "����� ������� ������:" << endl;
	outMatrix(s, matrix);
	cout << "������������ ������� �������: " << det1 << endl;
	cout << "������������ ������� ������: " << det2 << endl;
	cout << "�������� ����� ����� ��������������: " << diff << endl;
	system("pause");
	return 0;
}
