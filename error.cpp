#include "error.h"
#include <QList>
#include "ui_error.h"

error::error(QSqlQuery &test,QString query,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::error)
{
    ui->setupUi(this);
    QString error = "";
    QList<QString> list = QSqlDatabase::drivers();
    for(int i = 0;i<list.length();i++)
    {
        error = error+list[i]+" ";
    }
    ui->errorTab->setText(error);
    qDebug()<<error<<" "<<Qt::endl;
    ui->errorTab->append("\n"+test.lastError().text()+"\n\n"+query);
}

error::~error()
{
    delete ui;
}
