#include "interpreter.h"
#include <QRegExp>
#include <QStringList>
#include <QDebug>
#include <share.h>
#include <myexceptions.h>
#include <IntergrationSolution.h>

Interpreter::Interpreter()
{
}

QStringList Interpreter::tokens;
int Interpreter::curToken = 0;

QString Interpreter::parse(const QString &instruction){
    lexScanner(instruction);
    return parseS();
}



void Interpreter::lexScanner(const QString &instruction){
    Interpreter::curToken = 0;
    QString tmp = instruction;
    int i = 0;
    QRegExp singlePtn(",|;|=|\\+|\\-|\\*|\\/|\\^|\\[|\\]|\\(|\\)");
    QRegExp doublePtn("==");
    while(i < tmp.length()){
        if(i < tmp.length()-1 && doublePtn.exactMatch(tmp.mid(i,2))){
            if(i != tmp.length()-2)
                tmp.insert(i+2,' ');
            tmp.insert(i,' ');
            i = i+3;
        }
        else if(singlePtn.exactMatch(QString(tmp.at(i)))){
            if(i != tmp.length()-1)
                tmp.insert(i+1,' ');
            tmp.insert(i,' ');
            i = i+2;
        }
        else
            i++;
    }
    Interpreter::tokens = tmp.split(" ");
    tokens.removeAll("");
    qDebug() << tokens << endl;
}

QString Interpreter::getToken(){
    if(curToken < tokens.length())
        return tokens.at(curToken);
    else
        //抛出异常
        throw myexception("grammar error");
}

void Interpreter::eat(QString shouldBe){
    if(getToken() == shouldBe)
        curToken++;
    else
        throw myexception("grammar error");
}
void Interpreter::eat(){
        curToken++;
}
//判断是否是id
bool Interpreter::isId(QString str){
    QRegExp reId("[A-Za-z][A-Za-z0-9|_]*");
    if(reId.exactMatch(str))
        return true;
    else
        return false;
}
//判断是否是数字
bool Interpreter::isNum(QString str){
    QRegExp reId("-?[0-9]+.[0-9]+|-?[0-9]+");
    if(reId.exactMatch(str))
        return true;
    else
        return false;
}
//判断是否是INT
bool Interpreter::isInt(QString str){
    QRegExp reId("\\d*");
    if(reId.exactMatch(str))
        return true;
    else
        return false;
}
void Interpreter::parseV(){
    QString token = getToken();
    int flag = 0;
    try{
        if(isId(token)){
            datas.addVarName(token);
            flag = 1;
            eat();
        }
        else{
            throw myexception("wrong variable name");
        }
        if(curToken < tokens.length()){
            eat(",");
            parseV();
        }
    }
    catch(myexception e){
        if(flag == 1)
            datas.deleteVarName();
        throw e;
    }
}

void Interpreter::parseM(){
    QString token = getToken();
    int flag = 0;
    try{
        if(isId(token)){
            datas.addMtxName(token);
            flag = 1;
            eat();
        }
        else{
            throw myexception("wrong variable name");
        }
        if(curToken < tokens.length()){
            eat(",");
            parseM();
        }
    }
    catch(myexception e){
        if(flag == 1)
            datas.deleteMtxName();
        throw e;
    }
}

void Interpreter::parseQ(){
    QString token = getToken();
    int flag = 0;
    try{
        if(isId(token)){
            datas.addEqnName(token);
            flag = 1;
            eat();
        }
        else{
            throw myexception("wrong variable name");
        }
        if(curToken < tokens.length()){
            eat(",");
            parseQ();
        }
    }
    catch(myexception e){
        if(flag == 1)
            datas.deleteEqnName();
        throw e;
    }
}

void Interpreter::parseQS(){
    QString token = getToken();
    if(datas.isInEqnList(token) != -1){
        eat();
    }
    else{
        throw myexception("no such id");
    }
    eat(",");
    if(datas.isInEqnList(getToken()) != -1){
        parseQS();
    }
}

void Interpreter::parseVS(){
    QString token = getToken();
    if(datas.isInVarList(token) != -1){
        eat();
    }
    else{
        throw myexception("no such id");
    }
    if(getToken() == ","){
        eat();
        parseVS();
    }
    else if(getToken() == ")")
        return;
    else
        throw myexception("grammar error");
}

void Interpreter::parseC(){
    QString token = getToken();
    int flag = 0;
    try{
        if(isId(token)){
            datas.addCrvName(token);
            flag = 1;
            eat();
        }
        else{
            throw myexception("wrong variable name");
        }
        if(curToken < tokens.length()){
            eat(",");
            parseC();
        }
    }
    catch(myexception e){
        if(flag == 1)
            datas.deleteCrvName();
        throw e;
    }
}

void Interpreter::parseE(){
    QString token = getToken();
    if(isId(token)){
        if(datas.isInVarList(token)!=-1){
            eat();
            parseF();
        }
        else
            throw myexception("no such id");
    }

    else if(isNum(token)){
        eat();
        parseF();
    }
    else if(token == "("){
        eat();
        parseE();
        eat(")");
        parseF();
    }
    else{
        throw myexception("wrong expression");
    }
}

void Interpreter::parseF(){
    if(curToken == tokens.length() || getToken() == "==" || getToken() == ")")
        return;
    QRegExp re("\\+|\\-|\\*|\\/");
    if(re.exactMatch(getToken())){
        eat();
        parseE();
    }
    else if(getToken() == "^"){
        eat();
        if(isNum(getToken()))
            eat();
        else
            throw myexception("cannot calculate by current version");
        parseF();
    }
    else{
        throw myexception("wrong operator");
    }
}

void Interpreter::parseT(){
    if(curToken == tokens.length())
        return;
    if(getToken() == "+" || getToken() == "-"){
        eat();
        if(isId(getToken()) && datas.isInMtxList(getToken()) != -1){
            eat();
            parseT();
        }
        else{
            throw myexception("wrong variable name");
        }
    }
    else if(getToken() == "*"){
        eat();
        if((isId(getToken()) && datas.isInMtxList(getToken()) != -1) || isNum(getToken())){
            eat();
            parseT();
        }
        else{
            throw myexception("wrong variable name");
        }
    }
    else{
        throw myexception("wrong operator");
    }
}

void Interpreter::parseN(){
    if(curToken == tokens.length()-1)
        return;
    else{
        if(isNum(getToken())){
            eat();
            if(curToken == tokens.length()-1)
                return;
            else if(getToken() == "," || getToken() == ";"){
                eat();
                parseN();
            }
            else
                throw myexception("wrong variable name");
        }
        else{
            throw myexception("wrong variable name");
        }
    }
}

QString Interpreter::parseS(){
    QString token = getToken();
    //这里应该捕获异常
    if(token == "var"){
        eat();parseV();//保存变量
        return "变量创建成功";
    }
    else if(token == "mtx"){
        eat();
        parseM();//保存矩阵
        return "矩阵创建成功";
    }
    else if(token == "eqn"){
        eat();parseQ();//保存方程
        return "方程创建成功";
    }
    else if(token == "crv"){
        eat();parseC();//保存曲线
        return "曲线创建成功";
    }
    else if(token == "solve"){
        eat();
        eat("(");
        parseQS();
        parseVS();
        eat(")");
        //解方程
        return "解方程成功";
    }
    else if(token == "sort"){
        eat();
        eat("(");
        if(datas.isInMtxList(getToken()) != -1){
            eat();
        }
        else
            throw myexception("no such matrix");
        if(getToken() == ","){
            eat();
            token = getToken();
            if(isInt(token)){
                switch(token.toInt()){
                    case 1:
                        eat();
                        eat(")");
                        //调用升序排序；
                        return "调用升序排序";
                        break;
                    case 2:
                        eat();
                        eat(")");
                        //调用降序排序
                        return "调用降序排序";
                        break;
                    default:
                        throw myexception("no such sort method");
                        break;
                }
            }
            else{
                throw myexception("no such sort method");
            }
        }
        else if(getToken() == ")"){
            eat(")");
            //调用升序排序；
            return "调用升序排序";
        }
        else{
            throw myexception("grammar error");
        }
    }
    else if(token == "int"){
        eat();
        eat("(");
        QString crvName;
        QString varName;
        double bgn;
        double end;
        if(datas.isInCrvList(getToken()) != -1){
            crvName = getToken();
            eat();
        }
        else
            throw myexception("no such id");
        eat(",");
        if(datas.isInVarList(getToken()) != -1){
            varName = getToken();
            eat();
        }
        else
            throw myexception("no such id");
        eat(",");
        if(isNum(getToken())){
            bgn = getToken().toDouble();
            eat();
        }
        else
            throw myexception("grammar error, not a number");
        eat(",");
        if(isNum(getToken())){
            end = getToken().toDouble();
            eat();
        }
        else
            throw myexception("grammar error, not a number");
        eat(")");
        //求积分
        QString crvValue = datas.getCrvValue(crvName);
        QString result = QString::number(IntergrationSolution::integrate(crvValue,bgn,end),'f',10);
        datas.changeVarValue(varName,result);
        return result;
    }
    else if(token == "draw"){
        eat();
        if(datas.isInCrvList(getToken()) != -1){
            QString crvName = getToken();
            if(datas.getCrvValue(crvName) != "/"){
                return "绘制曲线";
            }
            else{
                throw myexception("curve not be initialized");
            }
        }
        else{
            throw myexception("no such id");
        }
    }
    else if(isId(token)){
        //方程赋值
        if(datas.isInEqnList(token) != -1){
            eat();
            eat("=");
            int start = curToken;
            parseE();
            qDebug() << curToken;
            qDebug() << getToken();
            eat("==");
            parseE();
            int end = curToken-1;
            QStringList exps;
            for(int i = start; i <= end; i++)
                exps.append(tokens.at(i));
            QString exp = exps.join("");
            datas.changeEqnValue(token,exp);
            return "方程赋值成功";
        }
        //矩阵赋值
        else if(datas.isInMtxList(token) != -1){
            eat();
            QString nextToken = getToken();
            QRegExp re("\\+|\\-|\\*");
            if(nextToken == "="){
                eat();
                eat("[");
                int start = curToken;
                parseN();
                int end = curToken-1;
                eat("]");
                QStringList exps;
                for(int i = start; i <= end; i++)
                    exps.append(tokens.at(i));
                QString exp = exps.join("");
                datas.changeMtxValue(token,exp);
                return "矩阵赋值成功";
            }
            else if(re.exactMatch(nextToken)){
                parseT();
                //调用矩阵计算，在计算矩阵表达式时判断是否能计算
                return "矩阵表达式正确";
            }
            else{
                throw myexception("wrong variable name");
            }
        }
        //曲线赋值
        else if(datas.isInCrvList(token) != -1){
            eat();
            eat("=");
            int start = curToken;
            parseE();
            int end = curToken-1;
            QStringList exps;
            for(int i = start; i <= end; i++)
                exps.append(tokens.at(i));
            QString exp = exps.join("");
            datas.changeCrvValue(token,exp);
            return "曲线赋值正确";
        }
        else{
            throw myexception("no such id");
        }
    }
    else{
        throw myexception("grammar error");
    }

}




