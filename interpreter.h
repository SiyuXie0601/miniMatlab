#ifndef INTERPRETER_H
#define INTERPRETER_H


class Interpreter
{
public:
    static String parse(const String &instruction);
    Interpreter();
    ~Interpreter();
private:
    static Type checkInsType(const String &instruction);
    static String parseMtrxPro(const String &instruction);
    static String parseSrtPro(const String &instruction);
    static String parseEqtnPro(const String &instruction);
    static String parseIntgPro(const String &instruction);
    static boolean isCurveCorrect(const String &instruction);
    static vector parseStr(const String &str);

};

#endif // INTERPRETER_H
