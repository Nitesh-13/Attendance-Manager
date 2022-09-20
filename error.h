#ifndef ERROR_H
#define ERROR_H

#include <QDialog>
#include "dblogin.h"

namespace Ui {
class error;
}

class error : public QDialog
{
    Q_OBJECT

public:
    explicit error(QSqlQuery &test,QString query,QWidget *parent = nullptr);
    ~error();

private:
    Ui::error *ui;
};

#endif // ERROR_H
