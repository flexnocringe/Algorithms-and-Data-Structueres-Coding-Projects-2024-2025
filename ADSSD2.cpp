#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;
queue<bool> fracToBin(double var, queue<bool> bin) {
    int boundary = 16; // kiek skaiciu po kablelio
    for (int i = 0; i < boundary; i++) {
        var *= 2;
        bin.push(trunc(var));
        if (var > 1) {
            var--;
        }
    }
    return bin;
}
queue<char> fraqToHex(double var, queue<char> hex)
{
    int boundary = 16; //kiek skaiciu po kablelio
    int varInt = 0;
    for (int i = 0; i < boundary; i++)
    {
        var *= 16;
        varInt = var;
        if (varInt >= 10)
        {
            switch (varInt)
            {
            case 10:
                hex.push('A');
                break;
            case 11:
                hex.push('B');
                break;
            case 12:
                hex.push('C');
                break;
            case 13:
                hex.push('D');
                break;
            case 14:
                hex.push('E');
                break;
            case 15:
                hex.push('F');
                break;
            }
        }
        else
        {
            hex.push(varInt + '0');
        }
        var -= varInt * 1.;
    }
    return hex;
}
void inputMenu() {
    cout << "Pasirinkite pradinio skaicio reiksmes ivedimo buda: ";
    cout << "\n1. Ivestis per konsole";
    cout << "\n2. Ivestis is failo";
    cout << "\nIvedimo budas: ";
}
void nextActMenu() {
    cout << "Norint kartoti programos vykdyma iveskite R, norint baigti darba "
        "iveskite Q";
    cout << "\nIvestis: ";
}
void binHexMenu() {
    cout << "Pasirinkite skaiciavimo sistema i kuria bus konvertuojamas skacius:";
    cout << "\n1. Devejetaine";
    cout << "\n2. Sesioliktaine";
    cout << "\nPasirinkimas: ";
}
void outputMenu() {
    cout << "Pasirinkite rezultato reiksmes isvedimo buda: ";
    cout << "\n1. Isvestis i ekrana";
    cout << "\n2. Ivestis i faila";
    cout << "\nIsvedimo budas: ";
}
int main() {
    string fileName = {};
    double decVar = 0;
    bool binHex;
    char choice = NULL, choice2 = NULL;
    while (true) {
        queue<char> hexDecimal;
        queue<bool> binDecimal;
        inputMenu();
        cin >> choice;
        if (choice == '1') {
            cout << "Iveskite reiksme: ";
            cin >> decVar;
        }
        else if (choice == '2') {
            cout << "Iveskite failo varda: ";
            cin >> fileName;
            ifstream inputFile(fileName);
            inputFile >> decVar;
            inputFile.close();
        }
        binHexMenu();
        cin >> choice;
        if (choice == '1') {
            binHex = 0;
            binDecimal = fracToBin(decVar, binDecimal);
            outputMenu();
            cin >> choice2;
            queue<bool> temp = binDecimal;
            if (choice2 == '1') {
                cout << "Konvertuotas skaicius = .";
                while (!temp.empty()) {
                    cout << temp.front();
                    temp.pop();
                }
                cout << endl;
            }
            else if (choice2 == '2') {
                cout << "Iveskite failo varda: ";
                cin >> fileName;
                ofstream outputFile(fileName);
                outputFile << ".";
                while (!temp.empty()) {
                    outputFile << temp.front();
                    temp.pop();
                }
                outputFile.close();
            }
        }
        else if (choice == '2')
        {
            binHex = 1;
            hexDecimal = fraqToHex(decVar, hexDecimal);
            outputMenu();
            cin >> choice2;
            queue<char> temp = hexDecimal;
            if (choice2 == '1') {
                cout << "Konvertuotas skaicius = .";
                while (!temp.empty()) {
                    cout << temp.front();
                    temp.pop();
                }
                cout << endl;
            }
            else if (choice2 == '2') {
                cout << "Iveskite failo varda: ";
                cin >> fileName;
                ofstream outputFile(fileName);
                outputFile << ".";
                while (!temp.empty()) {
                    outputFile << temp.front();
                    temp.pop();
                }
                outputFile.close();
            }
        }
        nextActMenu();
        cin >> choice;
        if (choice == 'Q' || choice == 'q')
        {
            if (binHex)
            {
                ofstream outputFile("last.txt");
                outputFile << decVar << endl;
                outputFile << "0.";
                while (!hexDecimal.empty()) {
                    outputFile << hexDecimal.front();
                    hexDecimal.pop();
                }
                outputFile.close();
            }
            else
            {
                ofstream outputFile("last.txt");
                outputFile << decVar << endl;
                outputFile << "0.";
                while (!binDecimal.empty()) {
                    outputFile << binDecimal.front();
                    binDecimal.pop();
                }
                outputFile.close();
            }
            break;
        }
    }
}