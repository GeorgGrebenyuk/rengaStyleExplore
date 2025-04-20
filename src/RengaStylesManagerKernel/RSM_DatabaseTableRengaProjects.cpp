#include "pch.h"
#include "RSM_DatabaseTableRengaProjects.hpp"
#include "RSM_DatabaseTablePaths.hpp"
#include "RSM_SqliteUtils.hpp"
#include "RSM_Settings.hpp"

namespace RSM_Kernel
{
    RSM_DatabaseTableRengaProjects::RSM_DatabaseTableRengaProjects(const QSqlDatabase* db)
    {
        this->m_db = db;
    }

    const QString RSM_DatabaseTableRengaProjects::GetTableName()
    {
        return QString("renga_projects");
    }

    void RSM_DatabaseTableRengaProjects::CreateTableDefinition()
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        RSM_SqliteUtils sqliteUtils(m_db);
        databaseQuery.prepare(
            QString("CREATE TABLE IF NOT EXISTS") +
            GetTableName() +
            QString("(rowid INTEGER PRIMARY KEY NOT NULL, bindata_rowid INTEGER REFERENCES bindata, paths_rowid INTEGER REFERENCES paths, version TEXT NOT NULL); "));
        sqliteUtils.ExecQuerry(&databaseQuery);
    }

    qint32 RSM_DatabaseTableRengaProjects::AddRengaProject(const QString& projectPath)
    {
        QFile fileDef(projectPath);
        if (!fileDef.exists()) return -1;
        RSM_SqliteUtils sqliteUtils(m_db);

        //вставляем BLOB
        qint32 blob_rowid = sqliteUtils.InsertData(GetTableName(), "data", fileDef.readAll());
        //вставляем путь
        RSM_DatabaseTablePaths* tablePaths = new RSM_DatabaseTablePaths(m_db);
        qint32 paths_rowid = tablePaths->AddFile(projectPath);

        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare(
            QString("INSERT INTO ") +
            GetTableName() +
            QString(" (bindata_rowid, paths_rowid) values (:val_paths_rowid, :val_paths_rowid);"));
        databaseQuery.bindValue(":val_paths_rowid", blob_rowid);
        databaseQuery.bindValue(":val_paths_rowid", paths_rowid);

       
        if (!sqliteUtils.ExecQuerry(&databaseQuery))
        {
            return -1;
        };
        return sqliteUtils.GetMaxRowid(this->GetTableName());
    }

    QString RSM_DatabaseTableRengaProjects::GetProjectFile(const qint32& rowid)
    {
        QString ret("");
        RSM_SqliteUtils sqliteUtils(m_db);
        //файл
        qint32 bindata_rowid = -1;
        if (!sqliteUtils.GetDataByRowid(GetTableName(), "bindata_rowid", rowid, &bindata_rowid)) return ret;
        //запрос расширения
        qint32 paths_rowid = -1;
        if (!sqliteUtils.GetDataByRowid(GetTableName(), "paths_rowid", rowid, &paths_rowid)) return ret;

        //запрос пути
        RSM_DatabaseTablePaths_RowDefinition pathInfo = RSM_DatabaseTablePaths(m_db).GetData(paths_rowid);
        //запрос проекта
        QByteArray fileData;
        sqliteUtils.GetDataByRowid("bindata", "data", bindata_rowid, &fileData);

        //Путь, по которому будет сохранен файл
        QString tmpProjectPath = RSM_Settings().GetTempPath(FileExtensionVariant::File_RNP);
        QFile tmpProjectDef(tmpProjectPath);
        tmpProjectDef.write(fileData);

        return ret;
    }
}
