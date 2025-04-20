#include "pch.h"
#include "RSM_DatabaseTableGeometry.hpp"

#include "RSM_SqliteUtils.hpp"

namespace RSM_Kernel
{
    RSM_DatabaseTableGeometry::RSM_DatabaseTableGeometry(const QSqlDatabase* db)
    {
        this->m_db = db;
    }

    const QString RSM_DatabaseTableGeometry::GetTableName()
    {
        return QString("geometry");
    }

    void RSM_DatabaseTableGeometry::CreateTableDefinition()
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        RSM_SqliteUtils sqliteUtils(m_db);
        databaseQuery.prepare(
            QString("CREATE TABLE IF NOT EXISTS") +
            GetTableName() +
            QString("(rowid INTEGER PRIMARY KEY NOT NULL, data BLOB not null); "));
        sqliteUtils.ExecQuerry(&databaseQuery);
    }

    qint32 RSM_DatabaseTableGeometry::AddGeometry(const QString& filePath)
    {
        QFile fileDef(filePath);
        if (!fileDef.exists()) return -1;
        RSM_SqliteUtils sqliteUtils(m_db);
        return sqliteUtils.InsertData(GetTableName(), "data", fileDef.readAll());
    }

    qint32 RSM_DatabaseTableGeometry::AddGeometry(const QByteArray& bytes)
    {
        RSM_SqliteUtils sqliteUtils(m_db);
        return sqliteUtils.InsertData(GetTableName(), "data", bytes);
    }

    RSM_GeometryObj RSM_DatabaseTableGeometry::GetGeometry(const qint32 rowid)
    {
        RSM_SqliteUtils sqliteUtils(m_db);
        QByteArray arr = QByteArray();
        RSM_GeometryObj objGeometry;

        if (!sqliteUtils.GetDataByRowid(GetTableName(), "data", rowid, &arr)) return objGeometry;        
        //TODO

        return objGeometry;
    }
}
