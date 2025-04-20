#include "pch.h"
#include "RSM_DatabaseTablePaths.hpp"
#include "RSM_SqliteUtils.hpp"

namespace RSM_Kernel
{
    RSM_DatabaseTablePaths::RSM_DatabaseTablePaths(const QSqlDatabase* db)
    {
        this->m_db = db;
    }

    const QString RSM_DatabaseTablePaths::GetTableName()
    {
        return QString("paths");
    }

    void RSM_DatabaseTablePaths::CreateTableDefinition()
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        RSM_SqliteUtils sqliteUtils(m_db);
        databaseQuery.prepare(
            QString("CREATE TABLE IF NOT EXISTS") +
            GetTableName() +
            QString("(rowid INTEGER PRIMARY KEY NOT NULL, path TEXT not null, ext INTEGER NOT NULL); "));
        sqliteUtils.ExecQuerry(&databaseQuery);
    }

    qint32 RSM_DatabaseTablePaths::AddFile(const QString& filePath)
    {
        FileExtensionVariant extType = FileExtensionVariant::_Unknown;
        QFile fileDef(filePath);
        if (fileDef.exists())
        {
            QFileInfo fileDefInfo(filePath);
            QString suff = fileDefInfo.completeSuffix().toLower();
            if (suff == ".rnp") extType = FileExtensionVariant::File_RNP;
            else if (suff == ".rnt") extType = FileExtensionVariant::File_RNT;
            else if (suff == ".lua") extType = FileExtensionVariant::File_LUA;
            else if (suff == ".json") extType = FileExtensionVariant::File_JSON;
            else if (suff == ".rst") extType = FileExtensionVariant::File_RST;
            else if (suff == ".obj") extType = FileExtensionVariant::File_OBJ;
        }
        return AddRecord(filePath, extType);
    }

    qint32 RSM_DatabaseTablePaths::AddDirectory(const QString& dirPath)
    {
        return AddRecord(dirPath, FileExtensionVariant::Directory);
    }

    RSM_DatabaseTablePaths_RowDefinition RSM_DatabaseTablePaths::GetData(const qint32& rowid)
    {
        RSM_DatabaseTablePaths_RowDefinition def = RSM_DatabaseTablePaths_RowDefinition();
        RSM_SqliteUtils sqliteUtils(m_db);

        QSqlQuery query;
        if (sqliteUtils.GetRowByRowid(GetTableName(), rowid, &query))
        {
            query.next();
            def.rowid = query.value("rowid").toInt();
            def.path = query.value("path").toString();
            def.ext = query.value("ext").toInt();
        }

        return def;
    }

    //internal
    qint32 RSM_DatabaseTablePaths::AddRecord(const QString& path, FileExtensionVariant extType)
    {
        if ((extType != FileExtensionVariant::Directory && QFile(path).exists()) || (extType == FileExtensionVariant::Directory && QDir(path).exists()))
        {
            QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
            QSqlQuery databaseQuery(*tmpDbPtr);
            RSM_SqliteUtils sqliteUtils(m_db);

            //проверить, что такого пути уже не было занесено

            databaseQuery.prepare(
                QString("SELECT FROM ") +
                GetTableName() +
                QString(" WHERE path = ") + path);
            if (!sqliteUtils.ExecQuerry(&databaseQuery))
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
                QString(" (path, ext) values (:val_path, :val_ext);"));
            databaseQuery.bindValue(":val_path", path);
            databaseQuery.bindValue(":val_ext", extType);

            if (!sqliteUtils.ExecQuerry(&databaseQuery))
            {
                return -1;
            };

            return sqliteUtils.GetMaxRowid(GetTableName());
        }
    }

}
