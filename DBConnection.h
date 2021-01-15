#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#define _CRT_SECURE_NO_WARNINGS

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <iostream>
#include <fstream>
#include <sstream>
#include  <cstdlib>
#include <filesystem>
#include <QMessageBox>
#include <QSqlQueryModel>

void CreateFolder(std::string path);
void GetSqlError(QSqlError* lcerror);
void DisplayMessage(std::string title,std::string  message,QMessageBox::Icon type);
std::string GetString(QString str);
class DBConnection
{
private:
//(localdb)\\MSSQLLocalDB


    QString DBName;
    QString Server;
    QString _connectionString ="";
    QString defaultStringConnection="Server=%1;Database=%2;Trusted_Connection=True;MultipleActiveResultSets=true";
    QSqlQuery* query = nullptr;
    std::string userPath;
    QSqlDatabase *database=nullptr;
    QSqlError* error = nullptr;
    QString defaultF;
    QSqlQueryModel* queryModel;

    QSqlQueryModel* DisplayDBConnectionMessage();
    QSqlQueryModel* CreateModel(const QString& query,QWidget* widgetHostPtr);
    bool CreateDB();
    bool SaveDBToFile(bool isNew);

    inline bool FileExist(const QString& name)
    {
        struct stat buffer;
        return (stat(name.toLocal8Bit().constData(), &buffer) == 0);
    }

    inline bool FileExist(const std::string& name)
    {
        struct stat buffer;
        return (stat(name.c_str(), &buffer) == 0);
    }


    inline const std::string BuildString()
    {
        std::stringstream ss;
        ss<< "dbstring";
        ss << GetDBCount();
        ss << " : ";
        ss<< GetConnectionString().toLocal8Bit().constData();
        std::string s  = ss.str();
        ss.clear();
        return s;
    }
    inline size_t GetDBCount()
    {
        std::ifstream file("db.txt");
        std::string str; size_t count=0;
        std::string dbKeyw="dbstring";
        size_t idx=0;
        while(std::getline(file,str))
        {
            while((idx = str.find(dbKeyw)) !=std::string::npos)
            {
                if(idx!=0)
                {
                    count++;
                    idx=0;
                    break;
                }
            }
        }
        return count;
    }

    inline bool ConnectionStringIsNotNull()
    {
        return this->GetConnectionString()!="";
    }
    inline QString GetConnectionString()
    {
        return this->_connectionString;
    }

public:

    inline const QString& GetDatabaseName(){
        return DBName;
    }
    inline const QString& GetServerName(){
        return Server;
    }
    explicit DBConnection();


    DBConnection(QString& dbName,QString& connectionString);
    DBConnection(QString& connectionString);
    void SetConnectionString(const QString& connectionString);
    void SetServerName(const QString& serverName);
    void SetDataBaseName(QString dbName);
    bool ConnectToDB();
    bool ConnectToDB(QString& connectionString,QString dbName);
    void OpenDBConnection();
    bool EnsureDBCreated();
    void DeleteModel();
    QSqlQueryModel* ExecuteQuery(const std::string& query,QWidget* widgetHostPtr);
    QSqlQueryModel* ExecuteQuery(const QString& query,QWidget* widgetHostPtr);
    inline QString GetQString(const std::string& str)
    {
       return  QString::fromUtf8(str.c_str());
    }



};

#endif // DBCONNECTION_H
