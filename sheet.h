#ifndef SHEET_H
#define SHEET_H

#include <QDialog>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QCheckBox>
#include <vector>
#include "dblogin.h"
#include "error.h"

namespace Ui {
class sheet;
}

class sheet : public QDialog
{
    Q_OBJECT

public:
    explicit sheet(QString month,int yearId,int date,QString tableName,int seTotal,int teTotal,QWidget *parent = nullptr);
    void saveAttendance();
    ~sheet();

private slots:
    void addTab1(int checkStatus);
    void addTab2(int checkStatus);
    void addTab3(int checkStatus);
    void addTab4(int checkStatus);
    void addTab5(int checkStatus);
    void addTab6(int checkStatus);
    void addTab7(int checkStatus);
    void addTab8(int checkStatus);
    void addTab9(int checkStatus);
    void addTab10(int checkStatus);
    void on_exit_clicked();
    void on_btnNext_clicked();
    void on_btnPrev_clicked();

private:
    Ui::sheet *ui;
    int date,tabcount = 0;
    dblogin connection;
    QString query,month;
    QString tableName;
    std::vector<int> checklist;
    int totalNo,yearId;
    QSqlQueryModel *table1 = new QSqlQueryModel();
    QSqlQueryModel *table2 = new QSqlQueryModel();
    QSqlQueryModel *table3 = new QSqlQueryModel();
    QSqlQueryModel *table4 = new QSqlQueryModel();
    QSqlQueryModel *table5 = new QSqlQueryModel();
    QSqlQueryModel *table6 = new QSqlQueryModel();
    QSqlQueryModel *table7 = new QSqlQueryModel();
    QSqlQueryModel *table8 = new QSqlQueryModel();
    QSqlQueryModel *table9 = new QSqlQueryModel();
    QSqlQueryModel *table0 = new QSqlQueryModel();
};

#endif // SHEET_H
