#include "pch.h"
#include "RSM_DatabaseTableIcons.hpp"
#include "RSM_SqliteUtils.hpp"

namespace RSM_Kernel
{
    RSM_DatabaseTableIcons::RSM_DatabaseTableIcons(const QSqlDatabase* db)
    {
        this->m_db = db;
    }

    const QString RSM_DatabaseTableIcons::GetTableName()
    {
        return QString("icons");
    }

    void RSM_DatabaseTableIcons::CreateTableDefinition()
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        RSM_SqliteUtils sqliteUtils(m_db);
        databaseQuery.prepare(
            QString("CREATE TABLE IF NOT EXISTS") +
            GetTableName() +
            QString("(rowid INTEGER PRIMARY KEY NOT NULL, data BLOB not null, resolution INTEGER); "));
        sqliteUtils.ExecQuerry(&databaseQuery);
    }

    qint32 RSM_DatabaseTableIcons::AddIcon(const QString& filePath)
    {
        QFile fileDef(filePath);
        if (!fileDef.exists()) return -1;
        RSM_SqliteUtils sqliteUtils(m_db);
        return sqliteUtils.InsertData(GetTableName(), "data", fileDef.readAll());
    }

    qint32 RSM_DatabaseTableIcons::AddIcon(const QImage data)
    {
        QByteArray arr(data.byteCount(), Qt::Uninitialized);
        memcpy(arr.data(), data.constBits(), data.byteCount());
        RSM_SqliteUtils sqliteUtils(m_db);

        return sqliteUtils.InsertData(GetTableName(), "data", arr);
    }

    void RSM_DatabaseTableIcons::GetIcon(const qint32 rowid, QImage* icon)
    {
        QByteArray arr = QByteArray();
        RSM_SqliteUtils sqliteUtils(m_db);
        if (!sqliteUtils.GetDataByRowid(GetTableName(), "data", rowid, &arr)) return;

        QPixmap mPixmap;
        mPixmap.loadFromData(arr, "PNG");
        *icon = mPixmap.toImage();
    }

}
