#include "pch.h"
#include "RSM_DatabaseTableDbinfo.hpp"
#include "RSM_SqliteUtils.hpp"

namespace RSM_Kernel
{
    RSM_DatabaseTableDbinfo::RSM_DatabaseTableDbinfo(const QSqlDatabase* db)
    {
        this->m_db = db;
    }

    const QString RSM_DatabaseTableDbinfo::GetTableName()
    {
        return QString("dbinfo");
    }

    void RSM_DatabaseTableDbinfo::CreateTableDefinition()
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
        RSM_SqliteUtils sqliteUtils(m_db);
        QSqlQuery databaseQuery(*tmpDbPtr);
        databaseQuery.prepare(
            QString("CREATE TABLE IF NOT EXISTS") +
            GetTableName() +
            QString("(key TEXT not null, value TEXT not null); "));
        sqliteUtils.ExecQuerry(&databaseQuery);
    }

    void RSM_DatabaseTableDbinfo::SetData(const QString& key, const QString& value)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
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
        RSM_SqliteUtils sqliteUtils(m_db);
        sqliteUtils.ExecQuerry(&databaseQuery);
    }

    void RSM_DatabaseTableDbinfo::GetAllData(QMap<QString, QString>& data)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare("SELECT * FROM " + GetTableName() + " ;");
        RSM_SqliteUtils sqliteUtils(m_db);
        if (!sqliteUtils.ExecQuerry(&databaseQuery)) return;

        int id_TableDbinfo_key = databaseQuery.record().indexOf("key");
        int id_TableDbinfo_value = databaseQuery.record().indexOf("value");

        data = QMap<QString, QString>();
        while (databaseQuery.next())
        {
            data.insert(databaseQuery.value(id_TableDbinfo_key).toString(), databaseQuery.value(id_TableDbinfo_value).toString());
        }
    }
}


