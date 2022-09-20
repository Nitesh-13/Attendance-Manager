#include "attendance.h"
#include "ui_attendance.h"

#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
using namespace QXlsx;

attendance::attendance(int sub1,int sub2,int accessId,int seTotal,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::attendance)
{
    ui->setupUi(this);
    QWidget::updateGeometry();
    this->accessId = accessId;
    this->seTotal = seTotal;

    QDate date = QDate::currentDate();
    ui->date->setDate(date);
    ui->date->setMaximumDate(date);
    ui->date->setMinimumDate(date);
    QIntValidator *validate = new QIntValidator(1,99);
    ui->rollInp->setValidator(validate);


    ui->btnHome->setChecked(true);
    ui->btnUpdate->setChecked(false);
    ui->btnView->setChecked(false);
    ui->homebtnSide2->hide();
    ui->homebtnSide3->hide();
    ui->btnExtraLecture->hide();
    ui->tabs->setCurrentIndex(0);

    ui->year->setParent(this);

    //Transparent Window
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    //Shadow
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(35);
    effect->setXOffset(0);
    effect->setYOffset(0);
    ui->displayLabel->setGraphicsEffect(effect);
    ui->navbar->setGraphicsEffect(effect);

    switch (sub1) {
    case 0:
        ui->year->removeItem(1);
        ui->downloadYear->removeItem(1);
        ui->updateYear->removeItem(1);
        break;
    case 1:
        subject1 = "CG";
        break;
    case 2:
        subject1 = "DELD";
        break;
    case 3:
        subject1 = "DM";
        break;
    case 4:
        subject1 = "FDS";
        break;
    case 5:
        subject1 = "OOP";
    default:
        break;
    }

    switch (sub2) {
    case 0:
        ui->year->removeItem(2);
        ui->downloadYear->removeItem(2);
        ui->updateYear->removeItem(2);
        break;
    case 1:
        subject2 = "CNS";
        break;
    case 2:
        subject2 = "DBMS";
        break;
    case 3:
        subject2 = "IoT";
        break;
    case 4:
        subject2 = "SPOS";
        break;
    case 5:
        subject2 = "TOC";
    default:
        break;
    }

    switch (ui->date->date().month()) {
    case 1:
        month = "Jan";
        break;
    case 2:
        month = "Feb";
        break;
    case 3:
        month = "Mar";
        break;
    case 4:
        month = "Apr";
        break;
    case 5:
        month = "May";
        break;
    case 6:
        month = "Jun";
        break;
    case 7:
        month = "Jul";
        break;
    case 8:
        month = "Aug";
        break;
    case 9:
        month = "Sept";
        break;
    case 10:
        month = "Oct";
        break;
    case 11:
        month = "Nov";
        break;
    case 12:
        month = "Dec";
        break;
    default:
        break;
    }
    getTotal();

    connect(ui->year,SIGNAL(currentIndexChanged(int)),SLOT(setSubject(int)));
    connect(ui->updateYear,SIGNAL(currentIndexChanged(int)),SLOT(setName(int)));
    connect(ui->rollInp,SIGNAL(returnPressed()),SLOT(setNameByRoll()));
    connect(ui->downloadYear,SIGNAL(currentIndexChanged(int)),SLOT(setDetails(int)));
}

void attendance::getTotal()
{
    connection.connectTE();
    QSqlQuery qry;
    qry.prepare("SELECT rollNo FROM dbmsTESept ORDER BY rollNo DESC LIMIT 1");
    if(!qry.exec())
    {
        qDebug()<<"error while fetching te total : "<<connection.loginTE.lastError();
    }
    qry.first();
    teTotal = qry.value(0).toInt();
    connection.disconnectTE();
}


attendance::~attendance()
{
    delete ui;
}


void attendance::on_quit_clicked()
{
    QCoreApplication::quit();
}

void attendance::setSubject(int index)
{
    if(index == 0)
    {
        ui->btnAttendance->setText("Select Subject");
        ui->btnAttendance->setEnabled(false);
        ui->subjectlbl->setText("");
        ui->totalNo->setText("0");
        ui->presentNo->setText("0");
        ui->percent->setText("0");
        ui->btnExtraLecture->hide();
        tableName = "none";
    }
    else{
        if(ui->year->currentText() == "SE Attendance")
        {
            tableName = subject1.toLower() + "SE" + month;
            if(semarked== 0)
            {
                QFile config("config.cnfg");
                if(config.exists())
                {
                    config.open(QIODevice::ReadOnly);
                    while(!config.atEnd())
                    {
                        QString line = config.readLine();
                        QString check = subject1+" = 1-"+QString::number(ui->date->date().day()) +"\n";
                        if(line == check)
                        {
                            semarked = 1;
                            connection.connectSE();
                            QString qrypresent = "SELECT COUNT(*) FROM "+tableName+" WHERE day"+QString::number(ui->date->date().day())+" = 'P'";
                            QSqlQuery getpresent;
                            getpresent.prepare(qrypresent);
                            if(!getpresent.exec())
                            {
                                qDebug()<<"Error while fetching present count of se : "<<connection.loginSE.lastError();
                            }
                            getpresent.first();
                            sePresent = getpresent.value(0).toInt();
                            sePercent = (sePresent * 100)/seTotal;
                            connection.disconnectSE();
                        }
                    }
                }
            }

            ui->presentNo->setText(QString::number(sePresent));
            ui->percent->setText(QString::number(sePercent));
            ui->totalNo->setText(QString::number(this->seTotal));
            if(semarked == 0)
            {
                ui->btnAttendance->setText("Start Attendance");
                ui->btnAttendance->setEnabled(true);
            }
            else{
                ui->btnAttendance->setText("Marked");
                ui->btnAttendance->setEnabled(false);
                ui->btnExtraLecture->show();
            }
            ui->subjectlbl->setText(subject1);
            yearId = 2;
        }
        else if(ui->year->currentText() == "TE Attendance")
        {
            tableName = subject2.toLower() + "TE" + month;
            if(temarked == 0)
            {
                QFile config("config.cnfg");
                if(config.exists())
                {
                    config.open(QIODevice::ReadOnly);
                    while(!config.atEnd())
                    {
                        QString line = config.readLine();
                        QString check = subject2 +" = 1-"+QString::number(ui->date->date().day())+"\n";
                        if(line == check)
                        {
                            temarked = 1;
                            connection.connectTE();
                            QString qrypresent = "SELECT COUNT(*) FROM "+tableName+" WHERE day"+QString::number(ui->date->date().day())+" = 'P'";
                            QSqlQuery getpresent;
                            getpresent.prepare(qrypresent);
                            if(!getpresent.exec())
                            {
                                qDebug()<<"Error while fetching present count of te : "<<connection.loginTE.lastError();
                            }
                            getpresent.first();
                            tePresent = getpresent.value(0).toInt();
                            tePercent = (tePresent * 100)/teTotal;
                            connection.disconnectTE();
                        }
                    }
                }
            }

            ui->presentNo->setText(QString::number(tePresent));
            ui->percent->setText(QString::number(tePercent));
            ui->totalNo->setText(QString::number(this->teTotal));

            if(temarked == 0)
            {
                ui->btnAttendance->setText("Start Attendance");
                ui->btnAttendance->setEnabled(true);
            }
            else{
                ui->btnAttendance->setText("Marked");
                ui->btnAttendance->setEnabled(false);
                ui->btnExtraLecture->show();
            }
            ui->subjectlbl->setText(subject2);
            yearId = 3;
        }
    }
}

void attendance::setName(int index)
{
    if(index == 0)
    {
        ui->nameDisp->setText("");
    }
    else if(!ui->rollInp->text().isEmpty() && index!=0)
    {
        QString query,subj,rolln;
        if(ui->updateYear->currentText() == "SE Attendance")
        {
            connection.connectSE();
            subj = subject1.toLower() + "SE" + month;
        }
        else if(ui->updateYear->currentText() == "TE Attendance")
        {
            connection.connectTE();
            subj = subject2.toLower() + "TE" + month;
        }
        rolln = ui->rollInp->text();
        query = "SELECT name FROM "+subj+" WHERE rollNo = "+rolln;

        QSqlQuery qry;
        qry.prepare(query);
        if(!qry.exec())
        {
            if(ui->updateYear->currentText() == "SE Attendance")
                qDebug()<<"Error while fetching name of se : "<<connection.loginSE.lastError();

            if(ui->updateYear->currentText() == "TE Attendance")
                qDebug()<<"Error while fetching name of te : "<<connection.loginTE.lastError();
        }
        qry.first();
        ui->nameDisp->setText(qry.value(0).toString());
        if(ui->updateYear->currentText() == "SE Attendance")
        {
            connection.disconnectSE();
        }
        else if(ui->updateYear->currentText() == "TE Attendance")
        {
            connection.disconnectTE();
        }
    }
}
void attendance::setNameByRoll()
{
    if(ui->updateYear->currentIndex() == 0)
    {
        ui->nameDisp->setText("");
    }
    else if(!ui->rollInp->text().isEmpty())
    {
        if(ui->updateYear->currentText() != "Select")
        {
            QString query,subj,rolln;
            if(ui->updateYear->currentText() == "SE Attendance")
            {
                connection.connectSE();
                subj = subject1.toLower() + "SE" + month;
            }
            else if(ui->updateYear->currentText() == "TE Attendance")
            {
                connection.connectTE();
                subj = subject2.toLower() + "TE" + month;
            }
            rolln = ui->rollInp->text();
            query = "SELECT name FROM "+subj+" WHERE rollNo = "+rolln;

            QSqlQuery qry;
            qry.prepare(query);
            qry.exec();
            qry.first();
            ui->nameDisp->setText(qry.value(0).toString());
            if(ui->updateYear->currentText() == "SE Attendance")
            {
                connection.disconnectSE();
            }
            else if(ui->updateYear->currentText() == "TE Attendance")
            {
                connection.disconnectTE();
            }
        }
    }
}

void attendance::setDetails(int index)
{
    QString monthshow;
    switch (ui->date->date().month()) {
    case 1:
        monthshow = "January";
        break;
    case 2:
        monthshow = "February";
        break;
    case 3:
        monthshow = "March";
        break;
    case 4:
        monthshow = "April";
        break;
    case 5:
        monthshow = "May";
        break;
    case 6:
        monthshow = "June";
        break;
    case 7:
        monthshow = "July";
        break;
    case 8:
        monthshow = "August";
        break;
    case 9:
        monthshow = "September";
        break;
    case 10:
        monthshow = "October";
        break;
    case 11:
        monthshow = "November";
        break;
    case 12:
        monthshow = "December";
        break;
    default:
        break;
    }
    if(index == 0)
    {
        ui->showsubject->setText("");
        ui->showmonth->setText("");
    }
    else if(ui->downloadYear->currentText() == "SE Comp")
    {
        ui->showsubject->setText(subject1);
        ui->showmonth->setText(monthshow);
    }
    else if(ui->downloadYear->currentText() == "TE Comp")
    {
        ui->showsubject->setText(subject2);
        ui->showmonth->setText(monthshow);
    }
}


void attendance::on_btnAttendance_clicked()
{
    if(tableName == "none")
    {
        QMessageBox::critical(nullptr,"Warning","Please Select A Valid Subject!");
    }
    else{
        connection.disconnectTE();
        int date = ui->date->date().day();


        sheet attendance(month,yearId,date,tableName,seTotal,teTotal);
        attendance.setModal(true);
        auto acceptStatus = attendance.exec();
        if(acceptStatus == QDialog::Accepted)
        {
            (yearId == 2)?connection.connectSE():connection.connectTE();
            QString qrypresent = "SELECT COUNT(*) FROM "+tableName+" WHERE day"+QString::number(date)+" = 'P'";
            QSqlQuery getpresent;
            getpresent.prepare(qrypresent);
            getpresent.exec();
            getpresent.first();
            if(yearId == 2)
            {
                sePresent = getpresent.value(0).toInt();
                sePercent = (sePresent * 100)/seTotal;
                ui->presentNo->setText(QString::number(sePresent));
                ui->percent->setText(QString::number(sePercent));
                QFile config("config.cnfg");
                if(config.open(QIODevice::WriteOnly | QIODeviceBase::Append))
                {
                    QString str = subject1 + " = 1-" + QString::number(ui->date->date().day()) + "\n";
                    QByteArray mark = str.toUtf8();
                    config.write(mark);
                }

                config.close();
                semarked = 1;
            }
            else{
                tePresent = getpresent.value(0).toInt();
                tePercent = (tePresent * 100)/teTotal;
                ui->presentNo->setText(QString::number(tePresent));
                ui->percent->setText(QString::number(tePercent));
                QFile config("config.cnfg");
                if(config.open(QIODevice::WriteOnly | QIODeviceBase::Append))
                {
                    QString str = subject2 + " = 1-" + QString::number(ui->date->date().day()) + "\n";
                    QByteArray mark = str.toUtf8();
                    config.write(mark);
                }

                config.close();
                temarked = 1;
            }

            ui->btnAttendance->setText("Marked");
            ui->btnAttendance->setEnabled(false);
            ui->btnExtraLecture->show();
            (yearId == 2)?connection.disconnectSE():connection.disconnectTE();
        }
        else{
            (yearId == 2)?semarked = 0:temarked = 0;
            ui->btnAttendance->setText("Start Attendance");
            ui->btnAttendance->setEnabled(true);
        }
    }

}


void attendance::on_btnHome_clicked()
{
    ui->homebtnSide->show();
    ui->homebtnSide2->hide();
    ui->homebtnSide3->hide();

    ui->year->show();

    ui->btnHome->setChecked(true);
    ui->btnUpdate->setChecked(false);
    ui->btnView->setChecked(false);
    ui->tabs->setCurrentIndex(0);
}


void attendance::on_btnUpdate_clicked()
{
    ui->homebtnSide2->show();
    ui->homebtnSide->hide();
    ui->homebtnSide3->hide();

    ui->year->hide();

    ui->btnUpdate->setChecked(true);
    ui->btnHome->setChecked(false);
    ui->btnView->setChecked(false);
    ui->tabs->setCurrentIndex(1);
}


void attendance::on_btnView_clicked()
{
    ui->homebtnSide3->show();
    ui->homebtnSide2->hide();
    ui->homebtnSide->hide();

    ui->year->hide();

    ui->btnView->setChecked(true);
    ui->btnHome->setChecked(false);
    ui->btnUpdate->setChecked(false);
    ui->tabs->setCurrentIndex(2);
}

void attendance::on_btnLogout_clicked()
{
    accept();
}


void attendance::on_updateRoll_clicked()
{
    int date = ui->date->date().day();
    bool present = ui->presentCheck->isChecked();
    bool absent = ui->absentCheck->isChecked();

    QString state,subtab,extranum;
    if(present)
    {
        state = "P";
    }
    else if(absent)
    {
        state = "A";
    }

    if(ui->rollInp->text().isEmpty())
    {
        QMessageBox::warning(nullptr,"Warning","Roll No Field can't be Empty!");
    }
    else{
        extranum = ui->rollInp->text();

        if(ui->updateYear->currentText()!="Select")
        {
            if(ui->updateYear->currentText() == "SE Attendance")
            {
                connection.connectSE();
                subtab = subject1.toLower() + "SE" + month;
            }
            else if(ui->updateYear->currentText() == "TE Attendance")
            {
                connection.connectTE();
                subtab = subject2.toLower() + "TE" + month;
            }
            QString query = "UPDATE "+subtab+" SET day"+QString::number(date)+" = '"+state+"' WHERE rollNo = "+extranum;
            QSqlQuery qry;
            qry.prepare(query);
            if(qry.exec())
            {
                QMessageBox::information(nullptr,"Success","Roll No "+extranum+" Attendance Marked Successfully!");
                ui->rollInp->clear();
                ui->nameDisp->setText("");
                if(ui->updateYear->currentText() == "SE Attendance")
                {
//                    semarked = 0;
                    connection.disconnectSE();
                }
                else if(ui->updateYear->currentText() == "TE Attendance")
                {
//                    temarked = 0;
                    connection.disconnectTE();
                }

            }
            else{
                QMessageBox::critical(nullptr,"Error","Something went wrong, please try again!");
                if(ui->updateYear->currentText() == "SE Attendance")
                {
                    connection.disconnectSE();
                }
                else if(ui->updateYear->currentText() == "TE Attendance")
                {
                    connection.disconnectTE();
                }

            }
        }
        else{
            QMessageBox::warning(nullptr,"Warning","Please select a valid year!");
        }
    }

}

void attendance::on_btnDownloadExcel_clicked()
{
    QString queryname;
    if(ui->downloadYear->currentText() == "SE Comp")
    {
       connection.connectSE();
       queryname = subject1.toLower() + "SE" + month;
    }
    else if(ui->downloadYear->currentText() == "TE Comp")
    {
        connection.connectTE();
        queryname = subject2.toLower() + "TE" + month;
    }


    Format format;

    format.setHorizontalAlignment(Format::AlignHCenter);
    format.setFontBold(true);

    QString quest = "SELECT name FROM " + queryname;

    QSqlQuery name;
    name.prepare(quest);
    name.exec();

    quest = "SELECT rollNo FROM " + queryname;

    QSqlQuery rollNo;
    rollNo.prepare(quest);
    rollNo.exec();


     QXlsx::Document xlsx;

     xlsx.setColumnWidth(1,8);
     xlsx.setColumnWidth(2,30);
     xlsx.setColumnFormat(1,format);
     xlsx.setRowFormat(1,format);

     xlsx.write("A1","Roll No");
     xlsx.write("B1","Name");
     int i = 2;
     QString cell;
       while(rollNo.next())
       {
           cell = "A"+QString::number(i);
           i++;

           xlsx.write(cell,rollNo.value(0).toInt());
       }
       i = 2;
       while(name.next())
       {
           cell = "B" + QString::number(i);
           i++;

           xlsx.write(cell,name.value(0).toString());
       }


       char col = 'C';
       QString nextcol;

       int flag = 0;
       for(int i = 0;i<ui->date->date().day();i++)
       {
           if(col<='Z' && flag == 0 )
           {
               nextcol = col;
           }
           else if(col > 'Z')
           {
               col = 'A';
               flag = 1;
               nextcol = "A";
               nextcol.append(col);
           }
           else{
               nextcol = "A";
               nextcol.append(col);
           }
           quest = "SELECT day"+QString::number(i+1)+" FROM " + queryname;

           QSqlQuery days;
           days.prepare(quest);
           days.exec();
           int row = 2;


            int flg = 0,addcol = 0;
           while(days.next())
           {
               if(days.value(0).toString() == "H"){
                   addcol = 1;
                break;
               }
               addcol = 0;
                cell = nextcol + QString::number(row);
                row++;
                xlsx.write(cell,days.value(0).toString());
                if(flg == 0)
                {
                    cell = nextcol + "1";
                    QString date = QString::number(i+1) + "/"+QString::number(ui->date->date().month())+"/2022";

                    xlsx.write(cell,date);
                    flg = 1;
                }
           }
           if(addcol == 0)
               col++;
       }
        QString saveto =  QFileDialog::getExistingDirectory(this,tr("Save To"), "C://",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        saveto = saveto +"/"+month+"-Month-"+ queryname + "-Attendance.xlsx";
        xlsx.saveAs(saveto);

       if(ui->downloadYear->currentText() == "SE Comp")
       {
          connection.disconnectSE();
       }
       else if(ui->downloadYear->currentText() == "TE Comp")
       {
           connection.disconnectTE();
       }
}

void attendance::on_btnExtraLecture_clicked()
{
    QString extralecSub;
    if(yearId == 2)
    {
        connection.connectSE();
        extralecSub = subject1;
    }
    else if(yearId == 3)
    {
        connection.connectTE();
        extralecSub = subject2;
    }
    QFile config("config.cnfg");
    if(config.exists())
    {
        config.open(QIODevice::ReadOnly);
        while(!config.atEnd())
        {
            QString line = config.readLine();
            QString lec1 = extralecSub+"COUNTER-"+QString::number(ui->date->date().day()) +"-1\n";
            QString lec2 = extralecSub+"COUNTER-"+QString::number(ui->date->date().day()) +"-2\n";
            QString lec3 = extralecSub+"COUNTER-"+QString::number(ui->date->date().day()) +"-3\n";
            QString lec4 = extralecSub+"COUNTER-"+QString::number(ui->date->date().day()) +"-4\n";
            QString lec5 = extralecSub+"COUNTER-"+QString::number(ui->date->date().day()) +"-5\n";
            QString lec6 = extralecSub+"COUNTER-"+QString::number(ui->date->date().day()) +"-6\n";

            if(line == lec1)
            {
                counter = 1;
            }
            else if(line == lec2)
            {
                counter = 2;
            }
            else if(line == lec3)
            {
                counter = 3;
            }
            else if(line == lec4)
            {
                counter = 4;
            }
            else if(line == lec5)
            {
                counter = 5;
            }
            else if(line == lec6)
            {
                counter = 6;
            }
        }
    }
    config.close();
    counter++;
    int extradate = (ui->date->date().day() * 100) + counter;
    int prevTable = ui->date->date().day();
    if(counter>=2)
        prevTable = (ui->date->date().day()*100) + (counter-1);
    QString query = "ALTER TABLE "+tableName+" ADD day"+QString::number(extradate)+" VARCHAR(10) DEFAULT 'H' AFTER day"+QString::number(prevTable);
    QSqlQuery qry;
    qry.prepare(query);
    if(!qry.exec())
    {
        QMessageBox::critical(nullptr,"Error","Something Went Wrong!");
        error show(qry,query);
        show.setModal(true);
        show.exec();
    }
    (yearId == 2)?connection.disconnectSE():connection.disconnectTE();

    sheet attendance(month,yearId,extradate,tableName,seTotal,teTotal);
    attendance.setModal(true);
    auto acceptStatus = attendance.exec();
    if(acceptStatus == QDialog::Accepted)
    {
        (yearId == 2)?connection.connectSE():connection.connectTE();
        QString qrypresent = "SELECT COUNT(*) FROM "+tableName+" WHERE day"+QString::number(extradate)+" = 'P'";
        QSqlQuery getpresent;
        getpresent.prepare(qrypresent);
        getpresent.exec();
        getpresent.first();
        if(yearId == 2)
        {
            sePresent = getpresent.value(0).toInt();
            sePercent = (sePresent * 100)/seTotal;
            ui->presentNo->setText(QString::number(sePresent));
            ui->percent->setText(QString::number(sePercent));
            connection.disconnectSE();
        }
        else{
            tePresent = getpresent.value(0).toInt();
            tePercent = (tePresent * 100)/teTotal;
            ui->presentNo->setText(QString::number(tePresent));
            ui->percent->setText(QString::number(tePercent));
            connection.disconnectTE();
        }

        if(config.open(QIODevice::WriteOnly | QIODeviceBase::Append))
        {
            QString str = extralecSub + "COUNTER-" + QString::number(ui->date->date().day()) + "-"+QString::number(counter)+"\n";
            QByteArray mark = str.toUtf8();
            config.write(mark);
        }
        config.close();
    }
    else{
        (yearId == 2)?connection.connectSE():connection.connectTE();
        QString drop = "ALTER TABLE "+tableName+" DROP COLUMN day"+QString::number(extradate);
        QSqlQuery dropTable;
        dropTable.prepare(drop);
        dropTable.exec();
        (yearId == 2)?connection.disconnectSE():connection.disconnectTE();
        counter--;
        config.close();
    }
}

