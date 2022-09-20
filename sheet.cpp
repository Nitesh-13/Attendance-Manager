#include "sheet.h"
#include "ui_sheet.h"

sheet::sheet(QString month,int yearId,int date,QString tableName,int seTotal,int teTotal,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sheet)
{
    ui->setupUi(this);
    this->date = date;
    this->yearId = yearId;
    this->tableName = tableName;
    this->month = month;

    //Transparent Window
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    //Shadow
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(35);
    effect->setXOffset(0);
    effect->setYOffset(0);
    ui->background->setGraphicsEffect(effect);

    //login Database
    if(yearId == 2)
    {
        totalNo = seTotal;
        if(!connection.connectSE())
        {
            QMessageBox::critical(nullptr,"Warning","Database Connection unsucccessful! Please Check Your Internet or Restart the Application.");
            ui->status->setText("Status : Disconnected");
        }
        else{
            ui->status->setText("Status : Connected");
        }
    }
    else if(yearId == 3)
    {
        totalNo = teTotal;
        if(!connection.connectTE())
        {
            QMessageBox::critical(nullptr,"Warning","Database Connection unsucccessful! Please Check Your Internet or Restart the Application.");
            ui->status->setText("Status : Disconnected");
        }
        else{
            ui->status->setText("Status : Connected");
        }
    }

    tabcount = (totalNo%20 == 0)?(totalNo/20):(totalNo/20) + 1;
    for(int i = tabcount;i<=4;i++)
    {
        ui->tabWidget->removeTab(i);
    }

    checklist.resize(totalNo);

    query = "SELECT rollNo AS 'Roll No',name AS Name,checkbox As '' FROM "+tableName+" WHERE rollNo>=1 AND rollNo<=10";
    table1->setQuery(query);
    ui->table01->setModel(table1);
    for(int i = 0;i<table1->rowCount();i++)
    {
        QCheckBox *box = new QCheckBox();
        ui->table01->setIndexWidget(table1->index(i,2),box);
        connect(box,SIGNAL(stateChanged(int)),this,SLOT(addTab1(int)));
    }
    ui->table01->setColumnWidth(0,48);ui->table01->setColumnWidth(1,167);ui->table01->setColumnWidth(2,30);
    //table

    query = "SELECT rollNo AS 'Roll No',name AS Name,checkbox As '' FROM "+tableName+" WHERE rollNo>=11 AND rollNo<=20";
    table2->setQuery(query);
    ui->table02->setModel(table2);
    for(int i = 0;i<table2->rowCount();i++)
    {
        QCheckBox *box = new QCheckBox();
        ui->table02->setIndexWidget(table2->index(i,2),box);
        connect(box,SIGNAL(stateChanged(int)),this,SLOT(addTab2(int)));
    }
    ui->table02->setColumnWidth(0,48);ui->table02->setColumnWidth(1,167);ui->table02->setColumnWidth(2,30);
    //table

    query = "SELECT rollNo AS 'Roll No',name AS Name,checkbox As '' FROM "+tableName+" WHERE rollNo>=21 AND rollNo<=30";
    table3->setQuery(query);
    ui->table03->setModel(table3);
    for(int i = 0;i<table3->rowCount();i++)
    {
        QCheckBox *box = new QCheckBox();
        ui->table03->setIndexWidget(table3->index(i,2),box);
        connect(box,SIGNAL(stateChanged(int)),this,SLOT(addTab3(int)));
    }
    ui->table03->setColumnWidth(0,48);ui->table03->setColumnWidth(1,167);ui->table03->setColumnWidth(2,30);

    query = "SELECT rollNo AS 'Roll No',name AS Name,checkbox As '' FROM "+tableName+" WHERE rollNo>=31 AND rollNo<=40";
    table4->setQuery(query);
    ui->table04->setModel(table4);
    for(int i = 0;i<table4->rowCount();i++)
    {
        QCheckBox *box = new QCheckBox();
        ui->table04->setIndexWidget(table4->index(i,2),box);
        connect(box,SIGNAL(stateChanged(int)),this,SLOT(addTab4(int)));
    }
    ui->table04->setColumnWidth(0,48);ui->table04->setColumnWidth(1,167);ui->table04->setColumnWidth(2,30);
    //table

    query = "SELECT rollNo AS 'Roll No',name AS Name,checkbox As '' FROM "+tableName+" WHERE rollNo>=41 AND rollNo<=50";
    table5->setQuery(query);
    ui->table05->setModel(table5);
    for(int i = 0;i<table5->rowCount();i++)
    {
        QCheckBox *box = new QCheckBox();
        ui->table05->setIndexWidget(table5->index(i,2),box);
        connect(box,SIGNAL(stateChanged(int)),this,SLOT(addTab5(int)));
    }
    ui->table05->setColumnWidth(0,48);ui->table05->setColumnWidth(1,167);ui->table05->setColumnWidth(2,30);
    //table

    query = "SELECT rollNo AS 'Roll No',name AS Name,checkbox As '' FROM "+tableName+" WHERE rollNo>=51 AND rollNo<=60";
    table6->setQuery(query);
    ui->table06->setModel(table6);
    for(int i = 0;i<table6->rowCount();i++)
    {
        QCheckBox *box = new QCheckBox();
        ui->table06->setIndexWidget(table6->index(i,2),box);
        connect(box,SIGNAL(stateChanged(int)),this,SLOT(addTab6(int)));
    }
    ui->table06->setColumnWidth(0,48);ui->table06->setColumnWidth(1,167);ui->table06->setColumnWidth(2,30);
    //table

    query = "SELECT rollNo AS 'Roll No',name AS Name,checkbox As '' FROM "+tableName+" WHERE rollNo>=61 AND rollNo<=70";
    table7->setQuery(query);
    ui->table07->setModel(table7);
    for(int i = 0;i<table7->rowCount();i++)
    {
        QCheckBox *box = new QCheckBox();
        ui->table07->setIndexWidget(table7->index(i,2),box);
        connect(box,SIGNAL(stateChanged(int)),this,SLOT(addTab7(int)));
    }
    ui->table07->setColumnWidth(0,48);ui->table07->setColumnWidth(1,167);ui->table07->setColumnWidth(2,30);
    //table

    query = "SELECT rollNo AS 'Roll No',name AS Name,checkbox As '' FROM "+tableName+" WHERE rollNo>=71 AND rollNo<=80";
    table8->setQuery(query);
    ui->table08->setModel(table8);
    for(int i = 0;i<table8->rowCount();i++)
    {
        QCheckBox *box = new QCheckBox();
        ui->table08->setIndexWidget(table8->index(i,2),box);
        connect(box,SIGNAL(stateChanged(int)),this,SLOT(addTab8(int)));
    }
    ui->table08->setColumnWidth(0,48);ui->table08->setColumnWidth(1,167);ui->table08->setColumnWidth(2,30);
    //table

    query = "SELECT rollNo AS 'Roll No',name AS Name,checkbox As '' FROM "+tableName+" WHERE rollNo>=81 AND rollNo<=90";
    table9->setQuery(query);
    ui->table09->setModel(table9);
    for(int i = 0;i<table9->rowCount();i++)
    {
        QCheckBox *box = new QCheckBox();
        ui->table09->setIndexWidget(table9->index(i,2),box);
        connect(box,SIGNAL(stateChanged(int)),this,SLOT(addTab9(int)));
    }
    ui->table09->setColumnWidth(0,48);ui->table09->setColumnWidth(1,167);ui->table09->setColumnWidth(2,30);
    //table

    query = "SELECT rollNo AS 'Roll No',name AS Name,checkbox As '' FROM "+tableName+" WHERE rollNo>=91 AND rollNo<=100";
    table0->setQuery(query);
    ui->table10->setModel(table0);
    for(int i = 0;i<table0->rowCount();i++)
    {
        QCheckBox *box = new QCheckBox();
        ui->table10->setIndexWidget(table0->index(i,2),box);
        connect(box,SIGNAL(stateChanged(int)),this,SLOT(addTab10(int)));
    }
    ui->table10->setColumnWidth(0,48);ui->table10->setColumnWidth(1,167);ui->table10->setColumnWidth(2,30);
    //table

    ui->tabWidget->setCurrentIndex(0);
    ui->btnPrev->hide();
}

void sheet::addTab1(int checkStatus)
{
    int rollNo  = ui->table01->currentIndex().row();
    if(checkStatus == 2)
    {
        checklist[rollNo] = 1;
    }
    else if(checkStatus == 0)
    {
        checklist[rollNo] = 0;
    }
}

void sheet::addTab2(int checkStatus)
{
    int rollNo  = ui->table02->currentIndex().row();
    rollNo+=10;
    if(checkStatus == 2)
    {
        checklist[rollNo] = 1;
    }
    else if(checkStatus == 0)
    {
        checklist[rollNo] = 0;
    }
}

void sheet::addTab3(int checkStatus)
{
    int rollNo  = ui->table03->currentIndex().row();
    rollNo+=20;
    if(checkStatus == 2)
    {
        checklist[rollNo] = 1;
    }
    else if(checkStatus == 0)
    {
        checklist[rollNo] = 0;
    }
}

void sheet::addTab4(int checkStatus)
{
    int rollNo  = ui->table04->currentIndex().row();
    rollNo+=30;
    if(checkStatus == 2)
    {
        checklist[rollNo] = 1;
    }
    else if(checkStatus == 0)
    {
        checklist[rollNo] = 0;
    }
}

void sheet::addTab5(int checkStatus)
{
    int rollNo  = ui->table05->currentIndex().row();
    rollNo+=40;
    if(checkStatus == 2)
    {
        checklist[rollNo] = 1;
    }
    else if(checkStatus == 0)
    {
        checklist[rollNo] = 0;
    }
}

void sheet::addTab6(int checkStatus)
{
    int rollNo  = ui->table06->currentIndex().row();
    rollNo+=50;
    if(checkStatus == 2)
    {
        checklist[rollNo] = 1;
    }
    else if(checkStatus == 0)
    {
        checklist[rollNo] = 0;
    }
}

void sheet::addTab7(int checkStatus)
{
    int rollNo  = ui->table07->currentIndex().row();
    rollNo+=60;
    if(checkStatus == 2)
    {
        checklist[rollNo] = 1;
    }
    else if(checkStatus == 0)
    {
        checklist[rollNo] = 0;
    }
}

void sheet::addTab8(int checkStatus)
{
    int rollNo  = ui->table08->currentIndex().row();
    rollNo+=70;
    if(checkStatus == 2)
    {
        checklist[rollNo] = 1;
    }
    else if(checkStatus == 0)
    {
        checklist[rollNo] = 0;
    }
}

void sheet::addTab9(int checkStatus)
{
    int rollNo  = ui->table09->currentIndex().row();
    rollNo+=80;
    if(checkStatus == 2)
    {
        checklist[rollNo] = 1;
    }
    else if(checkStatus == 0)
    {
        checklist[rollNo] = 0;
    }
}

void sheet::addTab10(int checkStatus)
{
    int rollNo  = ui->table10->currentIndex().row();
    rollNo+=90;
    if(checkStatus == 2)
    {
        checklist[rollNo] = 1;
    }
    else if(checkStatus == 0)
    {
        checklist[rollNo] = 0;
    }
}

void sheet::saveAttendance()
{
    if(connection.loginSE.isOpen())
        connection.disconnectSE();

    if(connection.loginTE.isOpen())
        connection.disconnectTE();


    query = "UPDATE "+tableName+" SET day"+QString::number(date)+" = CASE rollNo ";
    for(int i = 0;i<totalNo;i++)
    {
        if(checklist[i] == 1)
            query= query + "WHEN "+ QString::number(i+1) + " THEN 'P' ";
        else
            query = query + "WHEN "+QString::number(i+1) + " THEN 'A' ";
    }
    query = query + "END WHERE rollNo BETWEEN 1 AND " + QString::number(totalNo);

    (yearId == 2)?connection.connectSE():connection.connectTE();
    QSqlQuery qry;
    qry.prepare(query);
    bool status = qry.exec();
    if(status)
    {
        (yearId == 2)?connection.disconnectSE():connection.disconnectTE();
        QMessageBox::information(nullptr,"Saved","Attendance Marked Successfully!");
        std::fill(checklist.begin(),checklist.end(),0);
        accept();
    }
    else{
        QMessageBox::critical(nullptr,"Error","Something Went Wrong!");
        error show(qry,query);
        show.setModal(true);
        show.exec();
        (yearId == 2)?connection.disconnectSE():connection.disconnectTE();
        reject();
    }
}

sheet::~sheet()
{
    delete ui;
}

void sheet::on_exit_clicked()
{
    reject();
}


void sheet::on_btnNext_clicked()
{
    ui->btnPrev->show();
    int ind = ui->tabWidget->currentIndex();
    int max = ui->tabWidget->count()-1;
    ind++;
    if(ind >= max)
    {
        ui->btnNext->setText("Save");
    }
    if(ind == max+1)
    {
        saveAttendance();
    }
    ui->tabWidget->setCurrentIndex(ind);
}


void sheet::on_btnPrev_clicked()
{
    if(ui->tabWidget->currentIndex() == 1)
        ui->btnPrev->hide();
    ui->btnNext->setText("Next");
    int ind = ui->tabWidget->currentIndex();
    int min = 0;
    ind--;
    if(ind<min)
        ind = min;
    ui->tabWidget->setCurrentIndex(ind);
}

