#include "pch.h"
#include "RSM_DatabaseTableBindata.hpp"
#include "RSM_SqliteUtils.hpp"

namespace RSM_Kernel
{
    RSM_DatabaseTableBindata::RSM_DatabaseTableBindata(const QSqlDatabase* db)
    {
        this->m_db = db;
    }

    const QString RSM_DatabaseTableBindata::GetTableName()
    {
        return QString("bindata");
    }

    void RSM_DatabaseTableBindata::CreateTableDefinition()
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        RSM_SqliteUtils sqliteUtils(m_db);
        databaseQuery.prepare(
            QString("CREATE TABLE IF NOT EXISTS ") +
            GetTableName() +
            QString("(rowid INTEGER PRIMARY KEY NOT NULL, data BLOB not null); "));
        sqliteUtils.ExecQuerry(&databaseQuery);
    }

    qint32 RSM_DatabaseTableBindata::AddData(const QString& filePath)
    {
        QFile fileDef(filePath);
        if (!fileDef.exists()) return -1;
        RSM_SqliteUtils sqliteUtils(m_db);
        return sqliteUtils.InsertData(GetTableName(), "data", fileDef.readAll());
    }

    qint32 RSM_DatabaseTableBindata::AddData(const QByteArray data)
    {
        RSM_SqliteUtils sqliteUtils(m_db);
        return sqliteUtils.InsertData(GetTableName(), "data", data);
    }

    void RSM_DatabaseTableBindata::GetData(const qint32 rowid, QByteArray* data)
    {
        RSM_SqliteUtils sqliteUtils(m_db);
        sqliteUtils.GetDataByRowid(GetTableName(), "data", rowid, data);
    }
}
