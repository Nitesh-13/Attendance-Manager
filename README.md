# Attendance Manager

Attendance Manager is a Desktop application built with Qt Framework for C++ to manage the attendance of the class.

Functionalities : 

- Marking the attendance (Core)
- Updating particular student's attendance status
- Save monthly report of attendance as excel sheet
- All the data is stored on mysql database

## Installation

Download the [installer for windows](https://github.com/Nitesh-13/Attendance-Manager/releases/tag/v1.0.0)  to install Attendance Manager.

## Additional Libraries Used

QXlsx - [QXlsx](https://github.com/QtExcel/QXlsx) is excel file(*.xlsx) reader/writer library.

QXlsx comes under MIT licence.

## Getting Started with this Project

### Prerequisites
[Qt Studio (Qt C++)](https://www.qt.io/)

### Importing
1. Clone this repo
```sh
git clone https://github.com/Nitesh-13/Attendance-Manager.git
```

2. Open the folder and double click `AttendanceManagement.pro`

3. Add your mysql database credentials to `dblogin.cpp`
```cpp
// mysql credentials for SE database
bool dblogin::connectSE()
{
    loginSE = QSqlDatabase::addDatabase("QMYSQL");
    loginSE.setHostName("localhost"); // remote mysql host here
    loginSE.setUserName("");          // mysql username here
    loginSE.setPassword("");          // mysql password here
    loginSE.setDatabaseName("");      // database name here
    if (loginSE.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// mysql credentials for TE database
bool dblogin::connectTE()
{
    loginTE = QSqlDatabase::addDatabase("QMYSQL");
    loginTE.setHostName("localhost"); // remote mysql host here
    loginTE.setUserName("");          // mysql username here
    loginTE.setPassword("");          // mysql password here
    loginTE.setDatabaseName("");      // database name here
    if (loginTE.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://github.com/Nitesh-13/Attendance-Manager/blob/main/LICENCE.txt)