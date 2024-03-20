#include <iostream> // cout cin
#include <fstream> // ifsream ofstream
#include <cstring>
using namespace std;
const int maxLenStroke = 251;

bool checkCh(char Ch, char sentence[]) {
    bool flag = 0;
    for (int i = 0; i < maxLenStroke; i++) {
        if (sentence[i] == Ch) {
            flag = 1;
            break;
        }
    }
    return flag;
}
int factLenStr(char sentence[]) {
    int i = 0;
    while (sentence[i] != '\0') {
        i++;
    }
    return i;
}
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    string fileNamein = {};
    string fileNameout = {};

    char Ch;
    if (argc < 7) {
        cout << "Введите в две строки пути входного файла и выходного файла для записи: или для отмены программы введите 1 " << endl;
        cin >> fileNamein;
        if (fileNamein == "1") {

            cout << "Программа завершена." << endl;
            system("pause");
            return 0;
        }

        cin >> fileNameout;
        if (fileNameout == "1") {
            cout << "Программа завершена." << endl;
            system("pause");
            return 0;
        }
        cout << "Введите символ для распознавания строк, содержащего его, и перенос этих строк в конец файла" << endl;
        cin >> Ch;
    }
    else {
        for (int i = 1; i < argc; ++i) {
            string arg = argv[i];

            if (arg == "/I" && i + 1 < argc) {
                fileNamein = argv[i + 1];

                ++i;
            }
            else if (arg == "/O" && i + 1 < argc) {
                fileNameout = argv[i + 1];
                ++i;
            }
            else if (arg == "/C" && i + 1 < argc) {
                Ch = argv[i + 1][0];
                ++i;
            }
        }
    }

    ifstream file;
    ofstream outFile;

    const int len_arr = 300;

    char arrSentenceCh[len_arr][maxLenStroke] = {};
    file.open(fileNamein);
    outFile.open(fileNameout);
    if (!file.is_open()) {
        cerr << "Упс... Не удалось открыть входной файл. Возможно неверно указан путь. Повторите попытку" << endl;
        system("pause");
        return 0;
    }
    if (outFile.is_open()) {
        int ch = 0;
        cout << "Этот файл уже существует. Разрешить перезапись данного файла? Введите 1 или 0:" << endl;
        cin >> ch;
        if (ch == 0) {
            cout << "Программа завершена" << endl;
            system("pause");
            return 0;
        }
    }
    else {
        cout << " Создаем файл с введенным именем" << endl;
    }
    char midstroke[maxLenStroke] = {};
    midstroke[maxLenStroke - 1] = 0;
    int bias = 0;
    cout << "Вывод на экран входных данных" << endl;
    int numOfstroke = 1;
    int page = 1;
    cout << endl << "Страница " << page << endl;
    while (!file.eof()) {
        if (numOfstroke > 20) {
            cin.get();
            numOfstroke = 1;
            page++;
            cout << endl << "Страница " << page << endl;
        }
        int y = 0;
        /* file.get
         for (int d = 1; d < 121 && midstroke[d] != '\0'; d++) {

         }*/
        file.getline(midstroke, maxLenStroke);

         if (factLenStr(midstroke) > 250) {
             cerr << "Недопустимая ширина строки. Разрешенная - " << maxLenStroke << " символов" << endl;
             system("pause");
             return 0;
         }
        cout << numOfstroke << "  " << midstroke << endl;



        if (checkCh(Ch, midstroke)) {
            for (int i = 0; i < maxLenStroke - 1; i++) {
                arrSentenceCh[bias][i] = midstroke[i];
            }


            bias++;
            if (bias == len_arr) {
                cerr << bias << "Упс... колво предложений превышает заданную величину" << endl;
                system("pause");
                return 0;
            }
        }
        else {
            int i = 0;
            while (midstroke[i] != '\0') {
                outFile.put(midstroke[i]);
                i++;

            }
            outFile.put('\n');
        }
        for (int i = 0; i < maxLenStroke - 1; i++) {
            midstroke[i] = 0;
        }
        numOfstroke++;
    }




    for (int i = 0; i < bias; i++) {
        int x = 0;
        while (arrSentenceCh[i][x] != '\0') {
            outFile.put(arrSentenceCh[i][x]);
            x++;
        }
        outFile.put('\n');
    }
    file.close();
    outFile.close();
    ifstream readOut(fileNameout);
    ifstream readIn(fileNamein);
    cout << "Вывод обработки данных:" << endl;
    numOfstroke = 1;
    page = 1;
    cout << endl << "Страница " << page << endl;
    while (!readIn.eof()) {
        if (numOfstroke > 20) {
            numOfstroke = 1;
            page++;
            cout << endl << "Страница " << page << endl;
        }
        readIn >> midstroke;
        cout << numOfstroke << " " << midstroke << endl;
        readOut >> midstroke;
        numOfstroke++;
        cout << numOfstroke << " " << midstroke << endl;
        numOfstroke++;
    }

    readIn.close();
    readOut.close();

    cout << endl << "Вывод выходных данных" << endl;
    readOut.open(fileNameout);
    while (!readOut.eof()) {
        
        readOut.getline(midstroke, maxLenStroke - 1);
        cout << midstroke << endl;
    }
    readOut.close();
    system("pause");
    return 0;
}