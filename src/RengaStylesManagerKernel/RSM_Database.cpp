#include "pch.h"
#include "RSM_Database.hpp"
#include "RSM_Settings.hpp"
#include "RSM_Internals.hpp"
#include "RSM_DatabaseTablesProcessing.hpp"

namespace RSM_Kernel
{
	RSM_Database::RSM_Database()
	{
        auto db = QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));

        mRSM_db = QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
        QString dbPath = RSM_Settings().GetUniqueDbPath();
        mRSM_db.setDatabaseName(dbPath);
        mRSM_db.open();

        //Создаем определения таблиц
	}

    RSM_Database::RSM_Database(const QString& path)
    {
        QFile dbSourcePath(path);
        if (!dbSourcePath.exists()) {

            QException exc = QException();
            throw new RSM_Exception(QString("RSM. Database-file not exists for path ") + path);
            return;
        }
        mRSM_db = QSqlDatabase::addDatabase("QSQLITE");
        mRSM_db.setDatabaseName(path);
        mRSM_db.open();
        //TODO: check db schema
    }

    //----------Methods-----------------------------------------------
    const QSqlDatabase* RSM_Database::GetDatabase()
    {
        return &this->mRSM_db;
    }
    void RSM_Database::Save(const QString& path, bool Owerrite)
    {
        QString sourceDbPath = this->mRSM_db.databaseName();
        this->mRSM_db.commit();
        this->mRSM_db.close();

        QFile dbTargetPath(path);
        if (dbTargetPath.exists())
        {
            if (!Owerrite)
            {
                throw new RSM_Exception(QString("RSM. Database will not save, because file exists and no Owerrite-rule!") + path);
                return;
            }
            dbTargetPath.remove();
        }
        
        QFile::copy(sourceDbPath, path);
        QFile::remove(sourceDbPath);
    }
}
