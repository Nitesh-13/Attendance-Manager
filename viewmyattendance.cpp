#include "viewmyattendance.h"
#include "ui_viewmyattendance.h"

viewMyAttendance::viewMyAttendance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewMyAttendance)
{
    ui->setupUi(this);
}

void viewMyAttendance::getAttendance()
{
    (yearId == 2)?connection.connectSE():connection.connectTE();
    QString query = "SELECT";
    for(int i = 0;i<month;i++)
    {
        if(i<month-1)
        {
            query = query + " CASE WHEN day"+QString::number(i+1)+" = 'P' THEN 1 ELSE 0 END +";
        }
        else{
            query = query + " CASE WHEN day"+QString::number(i+1)+" = 'P' THEN 1 ELSE 0 END FROM "+tableName+" WHERE rollNo = "+QString::number(rollNo);
        }
    }
    QSqlQuery qry;
    qry.prepare(query);
    if(!qry.exec())
    {
        QMessageBox::critical(nullptr,tr("Warning"),"Something Went Wrong!");
    }
    qry.first();
    (yearId == 2)?sePresent = qry.value(0).toInt():tePresent = qry.value(0).toInt();
    qry.clear();
    qry.prepare("SELECT COUNT(*) FROM "+tableName);
    qry.exec();
    (yearId == 2)?seTotal = qry.value(0).toInt():teTotal = qry.value(0).toInt();
    qry.clear();
    (yearId == 2)?connection.disconnectSE():connection.disconnectTE();
    (yearId == 2)?sePercent = (sePresent/seTotal)*100:(tePresent/teTotal)*100;
}

viewMyAttendance::~viewMyAttendance()
{
    delete ui;
}

void viewMyAttendance::on_pushButton_clicked()
{
    rollNo = ui->rollView->text().toInt();

    if(ui->yearView->currentIndex() == 1)
        yearId = 2;
    else if(ui->yearView->currentIndex() == 2)
        yearId = 3;

    month = QDate::currentDate().month();
    tableName = ui->subjectView->currentText();

    if(yearId == 2)
    {
        tableName += "SE";
    }
    else if(yearId == 3)
    {
        tableName += "TE";
    }

    switch (month) {
    case 1:
        tableName += "Jan";
        break;
    case 2:
        tableName += "Feb";
        break;
    case 3:
        tableName += "Mar";
        break;
    case 4:
        tableName += "Apr";
        break;
    case 5:
        tableName += "May";
        break;
    case 6:
        tableName += "Jun";
        break;
    case 7:
        tableName += "Jul";
        break;
    case 8:
        tableName += "Aug";
        break;
    case 9:
        tableName += "Sept";
        break;
    case 10:
        tableName += "Oct";
        break;
    case 11:
        tableName += "Nov";
        break;
    case 12:
        tableName += "Dec";
        break;
    default:
        break;
    }

    getAttendance();


}

