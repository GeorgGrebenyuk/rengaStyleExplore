#include "pch.h"
#include "RSM_DatabaseTableDbinfo.hpp"

namespace RSM_Kernel
{
    const QString RSM_DatabaseTableDbinfo::GetTableName()
    {
        return QString("dbinfo");
    }

    void RSM_DatabaseTableDbinfo::CreateTableDefinition(const QSqlDatabase* db)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare(
            QString("CREATE TABLE IF NOT EXISTS") +
            GetTableName() +
            QString("(key TEXT not null, value TEXT not null); "));
        ExecQuerry(&databaseQuery);
    }

    void RSM_DatabaseTableDbinfo::SetData(const QSqlDatabase* db, const QString& key, const QString& value)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare(
            QString("DELET FROM ") +
            GetTableName() +
            QString(" WHERE key = ") + key + "; \n " +
            QString("INSERT INTO ") +
            GetTableName() +
            QString(" values (") +
            key +
            ", " +
            value);
        ExecQuerry(&databaseQuery);
    }

    void RSM_DatabaseTableDbinfo::GetAllData(const QSqlDatabase* db, QMap<QString, QString>& data)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare("SELECT * FROM " + GetTableName() + " ;");
        if (!ExecQuerry(&databaseQuery)) return;

        int id_TableDbinfo_key = databaseQuery.record().indexOf("key");
        int id_TableDbinfo_value = databaseQuery.record().indexOf("value");

        data = QMap<QString, QString>();
        while (databaseQuery.next())
        {
            data.insert(databaseQuery.value(id_TableDbinfo_key).toString(), databaseQuery.value(id_TableDbinfo_value).toString());
        }
    }
}


