#include "modeldata.h"
#include "QDebug"
#include "QFileInfo"
#include "QFileIconProvider"
#include "myexceptions.h"

ModelData::ModelData(QObject *parent)
    : QAbstractTableModel(parent)
{
    header<<tr("种类")<<tr("名称")<<tr("值");
}

QVariant ModelData::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return header[section];
    return QAbstractTableModel::headerData(section,orientation,role);
}

int ModelData::rowCount(const QModelIndex &parent) const
{
    //qDebug()<<varNameList.size()+mtxNameList.size()+eqnNameList.size()+crvNameList.size()<<endl;
    return varNameList.size()+mtxNameList.size()+eqnNameList.size()+crvNameList.size();
}

int ModelData::columnCount(const QModelIndex &parent) const
{
    //qDebug()<<"columnCount:"<<endl;
    return 3;
}

QVariant ModelData::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    //列表依次显示变量，矩阵，方程，曲线
        //显示变量
        if(index.row() < varNameList.size()){
            //qDebug() << varNameList;
            if(role==Qt::DisplayRole){
                switch(index.column()){
                case 0:
                    return "变量";
                    break;
                case 1:
                    return varNameList[index.row()];
                    break;
                case 2:
                    return varValueList[index.row()];
                    break;
                default:
                    return QVariant();
                }
            }
            else if(role==Qt::DecorationRole && index.column() == 0){
                QIcon icon;
                icon = QIcon(":/var.png");
                return QVariant(icon);
            }
        }
        else if(index.row() < varNameList.size()+mtxNameList.size()){
            if(role==Qt::DisplayRole){
                switch(index.column()){
                case 0:
                    return "矩阵";
                    break;
                case 1:
                    return mtxNameList[index.row()-varNameList.size()];
                    break;
                case 2:
                    return mtxValueList[index.row()-varNameList.size()];
                    break;
                default:
                    return QVariant();
                }
            }
            else if(role==Qt::DecorationRole && index.column() == 0){
                QIcon icon;
                icon = QIcon(":/mtx.png");
                return QVariant(icon);
            }
        }
        else if(index.row() < varNameList.size()+mtxNameList.size()+eqnNameList.size()){
            if(role==Qt::DisplayRole){
                switch(index.column()){
                case 0:
                    return "方程";
                    break;
                case 1:
                    return eqnNameList[index.row()-varNameList.size()-mtxNameList.size()];
                    break;
                case 2:
                    return eqnValueList[index.row()-varNameList.size()-mtxNameList.size()];
                    break;
                default:
                    return QVariant();
                }
            }
            else if(role==Qt::DecorationRole && index.column() == 0){
                QIcon icon;
                icon = QIcon(":/eqn.png");
                return QVariant(icon);
            }
        }
        //显示方程
        else{
            if(role==Qt::DisplayRole){
                qDebug() << index.row()-varNameList.size()-mtxNameList.size()-eqnNameList.size();
                switch(index.column()){
                case 0:
                    return "曲线";
                    break;
                case 1:
                    return crvNameList[index.row()-varNameList.size()-mtxNameList.size()-eqnNameList.size()];
                    break;
                case 2:
                    return crvValueList[index.row()-varNameList.size()-mtxNameList.size()-eqnNameList.size()];
                    break;
                default:
                    return QVariant();
                }
            }
            else if(role==Qt::DecorationRole && index.column() == 0){
                QIcon icon;
                icon = QIcon(":/crv.png");
                return QVariant(icon);
            }
    }
    return QVariant();
}

void ModelData::addVarName(QString& varName){
    varNameList << varName;
    varValueList << "/";
    flashDatas();
}

void ModelData::addMtxName(QString& mtxName){
    mtxNameList << mtxName;
    mtxValueList << "/";
    flashDatas();
}

void ModelData::addEqnName(QString& eqnName){
    eqnNameList << eqnName;
    eqnValueList << "/";
    flashDatas();
}

void ModelData::addCrvName(QString& crvName){
    crvNameList << crvName;
    crvValueList << "/";
    flashDatas();
}

void ModelData::deleteVarName(QString varName){
    //删除最新插入的
    if(varName == "/"){
        varNameList.pop_back();
        varValueList.pop_back();
    }
    //删除指定的
    else{

    }
    flashDatas();
}

void ModelData::deleteEqnName(QString eqnName){
    //删除最新插入的
    if(eqnName == "/"){
        eqnNameList.pop_back();
        eqnValueList.pop_back();
    }
    //删除指定的
    else{

    }
    flashDatas();
}

void ModelData::deleteMtxName(QString mtxName){
    //删除最新插入的
    if(mtxName == "/"){
        mtxNameList.pop_back();
        mtxValueList.pop_back();
    }
    //删除指定的
    else{

    }
    flashDatas();
}

void ModelData::deleteCrvName(QString crvName){
    //删除最新插入的
    if(crvName == "/"){
        crvNameList.pop_back();
        crvValueList.pop_back();
    }
    //删除指定的
    else{

    }
    flashDatas();
}

int ModelData::isInVarList(QString varName){//返回变量位置，没有找到返回-1
    for(int i = 0; i < varNameList.size();i++){
        if(varName == varNameList.at(i))
            return i;
    }
    return -1;
}

int ModelData::isInEqnList(QString eqnName){
    for(int i = 0; i < eqnNameList.size();i++){
        if(eqnName == eqnNameList.at(i))
            return i;
    }
    return -1;
}

int ModelData::isInMtxList(QString mtxName){
    for(int i = 0; i < mtxNameList.size();i++){
        if(mtxName == mtxNameList.at(i))
            return i;
    }
    return -1;
}

int ModelData::isInCrvList(QString crvName){
    for(int i = 0; i < crvNameList.size();i++){
        if(crvName == crvNameList.at(i))
            return i;
    }
    return -1;
}

void ModelData::changeVarValue(QString& varName,QString& varValue){
    int pos = isInVarList(varName);
    if(pos != -1){
        varValueList.replace(pos,varValue);
    }
    flashDatas();
}

void ModelData::changeEqnValue(QString& eqnName,QString& eqnValue){
    int pos = isInEqnList(eqnName);
    if(pos != -1){
        eqnValueList.replace(pos,eqnValue);
    }
    flashDatas();
}

void ModelData::changeMtxValue(QString& mtxName,QString& mtxValue){
    int pos = isInMtxList(mtxName);
    if(pos != -1){
        if(mtxValue == "")
            throw myexception("matrx value cannot be none");
        QStringList rows = mtxValue.split(";");
        int column;
        int flag = 0;
        for(QString row: rows){
            QStringList items = row.split(",");
            if(flag == 0){//第一行
                column = items.length();
                flag = 1;
            }
            else{
                if(column != items.length())
                    throw myexception("matrx value error");
            }
        }
        mtxValueList.replace(pos,mtxValue);
    }
    flashDatas();
}

void ModelData::changeCrvValue(QString& crvName,QString& crvValue){
    int pos = isInCrvList(crvName);
    if(pos != -1){
        crvValueList.replace(pos,crvValue);
    }
    flashDatas();
}

void ModelData::clearDatas(){
    varNameList.clear();
    varValueList.clear();
    mtxNameList.clear();
    mtxValueList.clear();
    eqnNameList.clear();
    eqnValueList.clear();
    crvNameList.clear();
    crvValueList.clear();
    flashDatas();
}

void ModelData::flashDatas(){
    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(columnCount(),rowCount());
    emit layoutChanged();
    emit dataChanged(topLeft,bottomRight);
}

QString ModelData::getVarValue(QString varName){
    int pos = isInVarList(varName);
    return varValueList.at(pos);
}

QString ModelData::getEqnValue(QString eqnName){
    int pos = isInEqnList(eqnName);
    return eqnValueList.at(pos);
}

QString ModelData::getMtxValue(QString mtxName){
    int pos = isInMtxList(mtxName);
    return mtxValueList.at(pos);
}

QString ModelData::getCrvValue(QString crvName){
    int pos = isInCrvList(crvName);
    return crvValueList.at(pos);
}

