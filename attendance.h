#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <QDialog>
#include <QGraphicsDropShadowEffect>
#include <QDateEdit>
#include <QStandardPaths>
#include <QIntValidator>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include "dblogin.h"
#include "sheet.h"
#include "error.h"


namespace Ui {
class attendance;
}

class attendance : public QDialog
{
    Q_OBJECT

public:
    explicit attendance(int sub1,int sub2,int accessID,int seTotal,QWidget *parent = nullptr);
    void getTotal();

    ~attendance();

private slots:


    void on_quit_clicked();
    void setSubject(int index);
    void setName(int index);
    void setNameByRoll();
    void setDetails(int index);

    void on_btnAttendance_clicked();

    void on_btnHome_clicked();

    void on_btnUpdate_clicked();

    void on_btnView_clicked();

    void on_updateRoll_clicked();

    void on_btnLogout_clicked();

    void on_btnDownloadExcel_clicked();

    void on_btnExtraLecture_clicked();

private:
    Ui::attendance *ui;
    dblogin connection;
    QString month;
    int semarked = 0 ,temarked = 0,sePercent = 0,tePercent = 0,counter = 0;
    int accessId,seTotal = 0,teTotal = 0,sePresent = 0,tePresent = 0,yearId = 0;
    QString subject1,subject2,tableName = "none";
};

#endif // ATTENDANCE_H
