#include "DBConnection.h"
#include "stringhelper.h"
#include <QDebug>
#include <QMessageBox>


DBConnection::DBConnection(QString& dbName,QString& server)
{
 DBName = dbName;
 Server = server;
 database = new  QSqlDatabase();
 *database =QSqlDatabase::addDatabase("QODBC");
 defaultF ="db.txt";
 auto path = std::string(std::getenv("USERPROFILE"))  + std::string("\\Dbe");
 CreateFolder((userPath = path));
 queryModel =nullptr;
}

DBConnection::DBConnection()
{

database = new  QSqlDatabase();
*database =QSqlDatabase::addDatabase("QODBC");
 defaultF ="db.txt";
 auto path = std::string(std::getenv("USERPROFILE"))  + std::string("\\Dbe");
 CreateFolder((userPath = path));
 queryModel =nullptr;
}

void CreateFolder(std::string path)
{
    std::filesystem::create_directory(path);
}

bool DBConnection::CreateDB()
{
    auto queryStr  = QString("CREATE DATABASE %1 ON PRIMARY (NAME = MyDatabase_Data, FILENAME = '%1\\%2.mdf', SIZE = 4MB, MAXSIZE = 20MB, FILEGROWTH = 10%) LOG ON (NAME = MyDatabase_Log, FILENAME = '%1\\%2.ldf', SIZE = 2MB, MAXSIZE = 16MB, FILEGROWTH = 10%)").arg(userPath.c_str()).arg(this->DBName);
    query =  new QSqlQuery(*database);
    return query->exec(queryStr);
}

void DBConnection::SetConnectionString(const QString& connectionString)
{
    this->_connectionString = connectionString;
}

void  DBConnection::SetDataBaseName(QString dbName)
{
    this->DBName =dbName;
}

void  DBConnection::SetServerName(const QString& serverName)
{
     this->Server = serverName;
}

void GetSqlError(QSqlError* lcerror)
{
    const char* message  = (*lcerror).text().toLocal8Bit().constData();
    QMessageBox msgWarning;
    msgWarning.setText(message);
    msgWarning.setIcon(QMessageBox::Warning);
    msgWarning.setWindowTitle("Error while opening db");
    msgWarning.exec();
    delete message;
}

bool DBConnection::ConnectToDB()
{
    if(ConnectionStringIsNotNull())
    {

        database->setDatabaseName(_connectionString);
        if(!database->open())
        {
            *error = database->lastError().text();
            GetSqlError(error);
            return false;
        }

        return true;
    }
    else
    {
        _connectionString =  QString(defaultStringConnection).arg(this->Server).arg(this->DBName);
        database->setDatabaseName(_connectionString);

        if(!database->open())
        {
            *error = database->lastError().text();
            GetSqlError(error);
            return false;
        }

        return true;
    }
    return false;
}

bool DBConnection::EnsureDBCreated()
{
    std::string fileName = this->userPath + QString("\\%1.mdf").arg(DBName).toLocal8Bit().constData();
    bool created =true;
    if((created = !FileExist(fileName)))
    {
        created  =  CreateDB();

        if(created)
        {
            if(ConnectionStringIsNotNull())
            {
              created  = SaveDBToFile(FileExist(defaultF));

            }
            return created;
        }
        else
        {
            DisplayMessage("Error creating Database",(std::string("Error Creating Database","Couldn't create db because there is a database with ") + GetString(DBName)),QMessageBox::Icon::Critical);
            return created;
        }
        return created;
    }
    return created;
}


bool DBConnection::SaveDBToFile(bool isNew)
{
    try
    {
        std::ofstream  openWrite;
        if(isNew)
        openWrite.open ("test.txt", std::ofstream::out);
        else
        openWrite.open(defaultF.toLocal8Bit().constData(), std::ios::out | std::ios::app);

        openWrite <<BuildString();
        openWrite.close();
        return true;
    }
    catch (std::exception& e)
    {
        std::string s(e.what());

        DisplayMessage("Error writing db list","Error while writing db list on file",QMessageBox::Icon::Critical);
        qDebug()<<s.c_str();

        return false;
    }

}

void DBConnection::DeleteModel()
{
    delete queryModel;
    queryModel = nullptr;
}
QSqlQueryModel* DBConnection::DisplayDBConnectionMessage()
{
    DisplayMessage("Database connection is not open","check the database connection on DBConnection object",QMessageBox::Icon::Critical);
    return queryModel;
}
QSqlQueryModel* DBConnection::CreateModel(const QString& query,QWidget* widgetHostPtr)
{
    queryModel  =  new QSqlQueryModel(widgetHostPtr);
    queryModel->setQuery(query);
    return queryModel;
}

 QSqlQueryModel* DBConnection::ExecuteQuery(const QString& query,QWidget* widgetHostPtr)
 {
     DeleteModel();
    return this->database->isOpen() ? CreateModel(query,widgetHostPtr): DisplayDBConnectionMessage() ;
 }


 QSqlQueryModel* DBConnection::ExecuteQuery(const std::string& query,QWidget* widgetHostPtr)
 {
    DeleteModel();
    if(database->isOpen())
    {
        queryModel  =  new QSqlQueryModel(widgetHostPtr);
        queryModel->setQuery(GetQString(query));
        return queryModel;
    }


    DisplayMessage("Database connection is not open","check the database connection on DBConnection object",QMessageBox::Icon::Critical);
    return nullptr;
 }

std::string GetString(QString str)
{
    return std::string(str.toLocal8Bit().data());
}

void DisplayMessage(std::string title,std::string  message,QMessageBox::Icon type)
{
    QMessageBox msgWarning;
    msgWarning.setText(message.data());
    msgWarning.setIcon(type);
    msgWarning.setWindowTitle(title.c_str());
    msgWarning.exec();
}



