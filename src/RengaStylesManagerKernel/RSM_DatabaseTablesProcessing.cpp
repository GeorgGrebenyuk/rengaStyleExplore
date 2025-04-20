#include "pch.h"
#include "RSM_DatabaseTablesProcessing.hpp"

namespace RSM_Kernel
{
    void RSM_DatabaseTablesProcessing::DeleteAllData(const QSqlDatabase* db)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare("DELETE FROM " + GetTableName());
        ExecQuerry(&databaseQuery);
    }

    void RSM_DatabaseTablesProcessing::GetRowByRowid(const QSqlDatabase* db, const qint32 rowid, QSqlQuery* query)
    {
        query->prepare(("SELECT * FROM ") + GetTableName() + " WHERE rowid = " + QString::number(rowid) + ";");
        if (!ExecQuerry(query)) return;
    }

    qint32 RSM_DatabaseTablesProcessing::GetMaxRowid(const QSqlDatabase* db)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare("SELECT MAX(rowid) FROM" + GetTableName());
        if (!ExecQuerry(&databaseQuery)) return;
        databaseQuery.next();
        qint32 val = databaseQuery.record().value(0).toInt();
        return val;
    }

    bool RSM_DatabaseTablesProcessing::ExecQuerry(const QSqlQuery* query)
    {
        QSqlQuery* databaseQuery = const_cast<QSqlQuery*>(query);
        if (databaseQuery->exec()) return true;
        throw new RSM_Exception(databaseQuery->lastError().text().toLocal8Bit().data());
        return false;
    }

    //Tables definitions

    
}
