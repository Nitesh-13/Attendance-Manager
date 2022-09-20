#ifndef VIEWMYATTENDANCE_H
#define VIEWMYATTENDANCE_H

#include <QDialog>
#include <QMessageBox>
#include <QDate>
#include "dblogin.h"

namespace Ui {
class viewMyAttendance;
}

class viewMyAttendance : public QDialog
{
    Q_OBJECT

public:
    explicit viewMyAttendance(QWidget *parent = nullptr);
    void getAttendance();
    ~viewMyAttendance();

private slots:
    void on_pushButton_clicked();

private:
    Ui::viewMyAttendance *ui;
    int month,rollNo,sePresent,tePresent,seTotal,teTotal,sePercent,tePercent,yearId;
    QString tableName;
    dblogin connection;
};

#endif // VIEWMYATTENDANCE_H
