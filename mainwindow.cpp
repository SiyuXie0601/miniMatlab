#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QTextLayout>
#include <QTextBlock>
#include <interpreter.h>
#include <share.h>
#include <myexceptions.h>
#include <QDialog>
#include <qcustomplot.h>
#include <function1.h>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->installEventFilter(this);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setModel(&datas);
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(on_textEdit_textChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_textEdit_textChanged()
{
    disconnect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(on_textEdit_textChanged()));
    QStringList contents = ui->textEdit->toPlainText().split("\n");
    QString last = contents.last();
    contents.removeLast();
    QString others = contents.join("\n");
    if(last.length()<4){
        if(contents.length() == 0)
            ui->textEdit->setText("<span style='font:32px'><b><i>fx</i></b></span><span style='font:25px'><b>>></b></span>");
        else{
            ui->textEdit->setText(others);
            ui->textEdit->append("<span style='font:32px'><b><i>fx</i></b></span><span style='font:25px'><b>>></b></span>");
        }
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->textEdit->setTextCursor(cursor);
    }
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(on_textEdit_textChanged()));
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->textEdit) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            //如果输入是回车，则开始处理输入
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
                QStringList commands = ui->textEdit->toPlainText().split("\n");
                QString curCmd = commands.last();
                QString tmpCmd = curCmd.mid(4,-1);
                for(int i = 0; i < commands.length(); i++)
                    if(commands[i].at(0) == 'f' && commands[i].at(1) == 'x'){
                        commands[i].replace(0,1,' ');
                        commands[i].replace(1,1,' ');
                    }
                try{
                    QString result = Interpreter::parse(tmpCmd);
                    commands.append(result);
                    ui->textEdit->setText(commands.join('\n'));
                    if(result == "绘制曲线"){
                        QString crvName = tmpCmd.split(" ").at(1);
                        QString crvValue = datas.getCrvValue(crvName);
                        string tempstring = crvValue.toStdString();
                        const char* express = tempstring.c_str();
                        QDialog *dialog = new QDialog(this);
                        QCustomPlot * plot = new QCustomPlot(dialog);
                        QGridLayout * layout = new QGridLayout(dialog);
                        layout->addWidget(plot);
                        function1 test(express);
                        this->generategraph(plot, test.length(),test.getfunc(),-150,150);
                        this->setAttribute(Qt::WA_QuitOnClose, false);
                        int r = dialog->exec();
                        if(r == QDialog::Accepted){
                            qDebug() << "Accepted";
                        }
                        else{
                            qDebug() << "";
                        }
                    }
                }
                catch(myexception e){
                    ui->textEdit->insertHtml("<br><font color=\"red\">"+QString(e.what())+"</font>");
                }
                ui->textEdit->append("<span style='font:32px'><b><i>fx</i></b></span><span style='font:25px'><b>>></b></span>");
                QTextCursor cursor = ui->textEdit->textCursor();
                cursor.movePosition(QTextCursor::End);
                ui->textEdit->setTextCursor(cursor);
                return true;
            }
        }
    }
    else
        return MainWindow::eventFilter(obj,event);
}

void MainWindow::on_textEdit_cursorPositionChanged()
{
      QTextCursor tc = ui->textEdit->textCursor();
      int curPosX = tc.position() - tc.block().position();
      int curPosY = tc.block().firstLineNumber();
      int lastLine = ui->textEdit->document()->lineCount() - 1;
      //如果光标不在最后一行提示符后，则不能修改文本框内容
      if(curPosX <= 3 || curPosY < lastLine){
          ui->textEdit->setReadOnly(true);
      }
      else
          ui->textEdit->setReadOnly(false);
}

void MainWindow::on_pushButton_clicked()
{
    datas.clearDatas();
}


void MainWindow::generategraph(QCustomPlot *customPlot,int max, double* func, double start, double end)
{
  // generate some data:
  //double start = -150,  end = 150;
  double n = 1001;
  QVector<double> x(n), y(n),x1(n),y1(n),x2(n),y2(n); // initialize with entries 0..100
  //double func[101] = {2,2,0,0,0,0,0};
  //int max = a->length();
  double range = (end - start)/(n-1);
  for (int i=0; i<n; ++i)
  {
    x[i] =  i*range + start; // x goes from -1 to 1
    x1[i] = i*range + end;
    x2[i] = -i*range + start;
    for(int j = 0; j <= max; j++){
        y[i] += func[j]*pow(x[i],j);
        y1[i] += func[j]*pow(x1[i],j);
        y2[i] += func[j]*pow(x2[i],j);
    }

  }

  customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::blue)); // line color blue for second graph
  customPlot->addGraph();
  customPlot->graph(2)->setPen(QPen(Qt::blue)); // line color blue for third graph


  customPlot->graph(0)->setData(x, y);
  customPlot->graph(0)->rescaleAxes();
  customPlot->graph(1)->setData(x1, y1);
  customPlot->graph(2)->setData(x2, y2);

  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
  customPlot->replot();
}
