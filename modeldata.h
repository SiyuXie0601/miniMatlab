#ifndef MODELDATA_H
#define MODELDATA_H

#include <QAbstractItemModel>

class ModelData : public QAbstractTableModel
{
    //Q_OBJECT

public:
    explicit ModelData(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    // Basic functionality:

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex &index, int role) const;
    void addVarName(QString& varName);
    void addEqnName(QString& eqnName);
    void addMtxName(QString& mtxName);
    void addCrvName(QString& crvName);
    void deleteVarName(QString varName = QString("/"));
    void deleteEqnName(QString eqnName = QString("/"));
    void deleteMtxName(QString mtxName = QString("/"));
    void deleteCrvName(QString crvName = QString("/"));
    int isInVarList(QString varName);
    int isInEqnList(QString eqnName);
    int isInMtxList(QString mtxName);
    int isInCrvList(QString crvName);
    void changeVarValue(QString& varName,QString& varValue);
    void changeEqnValue(QString& eqnName,QString& eqnValue);
    void changeMtxValue(QString& mtxName,QString& mtxValue);
    void changeCrvValue(QString& crvName,QString& crvValue);
    QString getVarValue(QString varName);
    QString getEqnValue(QString eqnName);
    QString getMtxValue(QString mtxName);
    QString getCrvValue(QString crvName);
    void clearDatas();

signals:
public slots:
private:
    QStringList header;
    QStringList varNameList;
    QStringList varValueList;
    QStringList eqnNameList;
    QStringList eqnValueList;
    QStringList mtxNameList;
    QStringList mtxValueList;
    QStringList crvNameList;
    QStringList crvValueList;
    void flashDatas();
};

#endif // MODELDATA_H
