#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    //Shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(35);
    shadow->setXOffset(0);
    shadow->setYOffset(0);
    ui->gradient->setGraphicsEffect(shadow);
    ui->formLogin->setGraphicsEffect(shadow);

    int id = QFontDatabase::addApplicationFont(":/new/assets/assets/Mountain.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont mountain(family,125);
    ui->mountain->setFont(mountain);

    //Checking The Databse Connection
    if(connection.connectSE())
    {
        ui->status->setText("Status: Connected");
        qDebug()<<"Main Window Status Fetched Successfully!";
    }
    else{
        ui->status->setText("Status: Disconnected");
        qDebug() << "Error on main window : " <<connection.loginSE.lastError();
    }
    connection.disconnectSE();

    connect(ui->username, SIGNAL(returnPressed()),ui->password,SLOT(setFocus()));
    connect(ui->password, SIGNAL(returnPressed()),ui->btnLogin,SIGNAL(clicked()));
}

void MainWindow::start(int seTotal)
{
    attendance form(sub1Id,sub2Id,accessId,seTotal);
    form.setModal(true);
    auto status = form.exec();
    if(status == QDialog::Accepted)
    {
        this->show();
        ui->username->clear();
        ui->password->clear();
        ui->username->setFocus();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnLogin_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();

    connection.connectSE();
    QSqlQuery qry;
    if(qry.exec("SELECT * FROM loginInfo WHERE username='"+username+"' and password='"+password+"'"))
    {
        qDebug()<<"Username and Password fetched successfully!";
        int count = 0;
        while(qry.next())
        {
            count++;
        }
        if(count<1)
        {
            QMessageBox::critical(nullptr,"Warning","Username Or Password Incorrect, Please Try Again!");
            connection.disconnectSE();
        }
        else if(count==1)
        {
            QSqlQuery qry;
            qry.prepare("SELECT accessId  FROM loginInfo WHERE username = '"+username+"'");
            qry.exec();
            qry.first();
            accessId = qry.value(0).toInt();
            qry.clear();

            qry.prepare("SELECT sub1 FROM loginInfo WHERE username = '"+username+"'");
            qry.exec();
            qry.first();
            sub1Id = qry.value(0).toInt();
            qry.clear();

            qry.prepare("SELECT sub2 FROM loginInfo WHERE username = '"+username+"'");
            qry.exec();
            qry.first();
            sub2Id = qry.value(0).toInt();
            qry.clear();

            qry.prepare("SELECT rollNo FROM oopSESept ORDER BY rollNo DESC LIMIT 1");
            qry.exec();
            qry.first();
            int seTotal = qry.value(0).toInt();
            qry.clear();


            connection.disconnectSE();
            this->hide();
            start(seTotal);
        }
        else{
            QMessageBox::critical(nullptr,"Warning","Duplicate User Detected!");
            connection.disconnectSE();
        }
    }
    else{
        QMessageBox::critical(nullptr,"Warning","Please check the connection and try again!");
        qDebug()<<"Main Window Password error : "<<connection.loginSE.lastError();
    }
}


void MainWindow::on_exit_clicked()
{
    QCoreApplication::quit();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->position().x();
    m_nMouseClick_Y_Coordinate = event->position().y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalPosition().x()-m_nMouseClick_X_Coordinate,event->globalPosition().y()-m_nMouseClick_Y_Coordinate);
}

