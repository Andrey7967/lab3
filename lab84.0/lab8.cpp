#include <iostream> // cout cin
#include <fstream> // ifsream ofstream
#include <cstring>
using namespace std;
const int maxLenStroke = 121;

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
       
        cin >> fileNamein;
        if (fileNamein == "1") {

          
            system("pause");
            return 0;
        }

        cin >> fileNameout;
        if (fileNameout == "1") {
          
            return 0;
        }
       
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



    char arrSentenceCh[50][maxLenStroke] = {};
    file.open(fileNamein);
    outFile.open(fileNameout);
    if (!file.is_open()) {
      
        system("pause");
        return 0;
    }
    if (!outFile.is_open()) {

        system("pause");
        return 0;
    }
    char midstroke[maxLenStroke] = {};
    int bias = 0;
 
    int numOfstroke = 1;
    int page = 1;

    while (!file.eof()) {
        if (numOfstroke > 20) {
            cin.get();
            numOfstroke = 1;
            page++;
         
        }
        int y = 0;
        /* file.get
         for (int d = 1; d < 121 && midstroke[d] != '\0'; d++) {

         }*/
        file.getline(midstroke, 120);

        if (midstroke[120] != 0) {
          
            system("pause");
            return 0;
        }
        cout << numOfstroke << "  " << midstroke << endl;

        if (checkCh(Ch, midstroke)) {
            for (int i = 0; i < 120; i++) {
                arrSentenceCh[bias][i] = midstroke[i];
            }


            bias++;
        }
        else {
            int i = 0;
            while (midstroke[i] != '\0') {
                outFile.put(midstroke[i]);
                i++;

            }
            outFile.put('\n');
        }
        for (int i = 0; i < 120; i++) {
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
 
    numOfstroke = 1;
    page = 1;
  
    while (!readIn.eof()) {
        if (numOfstroke > 20) {
            numOfstroke = 1;
            page++;
            
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

  
    readOut.open(fileNameout);
    while (!readOut.eof()) {
        ;
        ReadOut.getline(midstroke, 120);
        cout << midstroke << endl;
    }
    readOut.close();
    system("pause");
    return 0;
}
