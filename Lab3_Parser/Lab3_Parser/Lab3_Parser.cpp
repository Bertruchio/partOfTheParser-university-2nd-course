//Написать программу, определяющую корректность применения составных операторов присваивания (например, а+=b)
//Составное присваивание (+=, -=, *=, /=, %=, >>=, <<=, &=, ^=, |=).

/* Границы задачи:
* 1. Окружение конструкции не анализируется
* 2. Допустимость выражения стоящего после составного оператора не рассматривается
* 3. Допустимость переменной стоящей до составного оператора не рассматривается
* 4. Всё, что находится внутри комментариев не рассматривается (код в них считается неактивным, 
с точки зрения реализации комментариев другими разработчиками)
*/

#include "iostream"
#include <string>
#include <fstream>

using namespace std;

class CompoundAssignmentOperatorsParser
{
private:
    //Приводим словарь всех составных операций присваивания
    string tokens[10] = { "+=", "-=", "*=", "/=", "%=", ">>=", "<<=", "&=", "^=", "|=" };
    int tokensFound[sizeof(tokens) / sizeof(*tokens)] = { 0 };
    string symbols, find, name;
    char c;

    //(на выход позиция левой границы) Функция поиска левой границы (на вход позиция курсора)
    int CheckLeftVariable(int cursorPos) {
        short checkLeftBorder = 0;
        int indx = tokensFound[cursorPos];
        while (indx >= 0) {
            if (symbols[indx] == ';') {
                checkLeftBorder = 1;
                break;
            }

            indx--;
        }
        if (checkLeftBorder) {
            //Левая граница есть, идём проверять наличие переменной после него
            return indx;

            for (int i = tokensFound[indx + 1]; i < symbols.length() && symbols[i] == ' ' && symbols[i] == '\n'; i++) {
                indx++;
            }
        }
        else {
            return 0;
            //Нет левой границы, проверка что справа одно единственное слово (переменная)
        }
    }

    int CheckRightVariable(int cursorPos) {
    
    }

public:
    CompoundAssignmentOperatorsParser(const char* nameT) : name(nameT) {}
    void FindAllOperators() {
        ifstream file(name);
        
        // Проверка на существование открываемого файла
        if (!file)
        {
            cerr << "The file with the code does not open" << endl;
            exit(1);
        }

        while (!file.eof()) {  // Прочитали файл и заполнили им строку
            file.get(c);
            symbols.push_back(c);
        }

        file.close();

        //Поочерёдно ищем операторы из словаря
        for (int i = 0; (i < (sizeof(tokens) / sizeof(*tokens))); i++) {
            tokensFound[i] = symbols.find(tokens[i]); // поиск

            if (tokensFound[i] > 0) {
                cout << "; found at " << tokensFound[CheckLeftVariable(i)] << " cursor position" << endl;
                //tokensFound[i] - 1

                cout << tokens[i] + " found at " << tokensFound[i] << " cursor position" << endl;
            }
        }
    }
};

int main() {
    CompoundAssignmentOperatorsParser parser("code.txt");
    parser.FindAllOperators();

    return 0;
}