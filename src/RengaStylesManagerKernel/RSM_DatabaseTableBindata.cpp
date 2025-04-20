#include "pch.h"
#include "RSM_DatabaseTableBindata.hpp"

namespace RSM_Kernel
{
    const QString RSM_DatabaseTableBindata::GetTableName()
    {
        return QString("dbinfo");
    }

    void RSM_DatabaseTableBindata::CreateTableDefinition(const QSqlDatabase* db)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare(
            QString("CREATE TABLE IF NOT EXISTS") +
            GetTableName() +
            QString("(rowid INTEGER PRIMARY KEY NOT NULL, data BLOB not null); "));
        ExecQuerry(&databaseQuery);
    }

    qint32 RSM_DatabaseTableBindata::AddData(const QSqlDatabase* db, const QString& filePath)
    {
        QFile fileDef(filePath);
        if (!fileDef.exists()) return -1;
        return AddData(db, fileDef.readAll());
    }

    qint32 RSM_DatabaseTableBindata::AddData(const QSqlDatabase* db, const QByteArray data)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare(
            QString("INSERT INTO ") +
            GetTableName() +
            QString(" (data) values (:bytesData)"));
        databaseQuery.bindValue(":bytesData", data);
        if (ExecQuerry(&databaseQuery)) return GetMaxRowid(db);
    }

    void RSM_DatabaseTableBindata::GetData(const QSqlDatabase* db, const qint32 rowid, QByteArray* data)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare(
            QString("SELECT * FROM ") +
            GetTableName() +
            QString(" WHERE rowid = ") + QString::number(rowid));
        if (!ExecQuerry(&databaseQuery)) return;
        databaseQuery.next();
        *data = databaseQuery.value(0).toByteArray();
    }
}
