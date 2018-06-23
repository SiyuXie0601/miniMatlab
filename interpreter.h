#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <string>
#include <vector>
#include <QString>
using namespace std;
class Interpreter
{
public:
    enum Type
        {
            Mtrx, Srt, Eqtn, Intg
        };
    static QString parse(const QString &instruction);
    Interpreter();
    ~Interpreter();

private:
    static bool isCurveCorrect(const string &instruction);
    static QString parseS();
    static void lexScanner(const QString &instruction);
    static QString getToken();
    static void eat(QString shouldBe);
    static void eat();
    static bool isId(QString str);
    static bool isNum(QString str);
    static bool isInt(QString str);
    static void parseV();
    static void parseM();
    static void parseQ();
    static void parseC();
    static void parseE();
    static void parseN();
    static void parseF();
    static void parseT();
    static void parseQS();
    static void parseVS();

    static QStringList tokens;
    static int curToken;
};

#endif // INTERPRETER_H
