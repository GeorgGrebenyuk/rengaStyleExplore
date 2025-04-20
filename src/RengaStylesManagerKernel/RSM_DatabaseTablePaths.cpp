#include "pch.h"
#include "RSM_DatabaseTablePaths.hpp"

namespace RSM_Kernel
{
    const QString RSM_DatabaseTablePaths::GetTableName()
    {
        return QString("paths");
    }

    void RSM_DatabaseTablePaths::CreateTableDefinition(const QSqlDatabase* db)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare(
            QString("CREATE TABLE IF NOT EXISTS") +
            GetTableName() +
            QString("(rowid INTEGER PRIMARY KEY NOT NULL, path TEXT not null, isfile INTEGER NOT NULL); "));
    }

    qint32 RSM_DatabaseTablePaths::AddFile(const QSqlDatabase* db, const QString& filePath)
    {
        return AddRecord(db, filePath, 1);
    }

    qint32 RSM_DatabaseTablePaths::AddDirectory(const QSqlDatabase* db, const QString& dirPath)
    {
        return AddRecord(db, dirPath, 0);
    }

    //internal
    qint32 RSM_DatabaseTablePaths::AddRecord(const QSqlDatabase* db, const QString& path, bool isFile)
    {
        if ((isFile && QFile(path).exists()) || (!isFile && QDir(path).exists()))
        {
            int isFileColumn = 1;
            if (!isFile) isFileColumn = 0;
            QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(db);
            QSqlQuery databaseQuery(*tmpDbPtr);

            //проверить, что такого пути уже не было занесено

            databaseQuery.prepare(
                QString("SELECT FROM ") +
                GetTableName() +
                QString(" WHERE path = ") + path);
            if (!ExecQuerry(&databaseQuery))
            {
                return -1;
            };

            if (databaseQuery.record().count() == 2) 
            {
                databaseQuery.next();
                return databaseQuery.value(0).toInt();
            }

            databaseQuery.prepare(
                QString("INSERT INTO ") +
                GetTableName() +
                QString(" (path, isfile) values (") +
                path + ", " + QString::number(isFileColumn) + ");");
            if (!ExecQuerry(&databaseQuery))
            {
                return -1;
            };

            return GetMaxRowid(db);
        }
    }
}
