#pragma once
#include "pch.h"
#include "RSM_DatabaseTablesProcessing.hpp"

namespace RSM_Kernel
{
    class RSM_DatabaseTablePaths : public RSM_DatabaseTablesProcessing
    {
    public:
        const QString GetTableName() override;
        void CreateTableDefinition(const QSqlDatabase* db) override;
        qint32 AddFile(const QSqlDatabase* db, const QString& filePath);
        qint32 AddDirectory(const QSqlDatabase* db, const QString& dirPath);
    private:
        qint32 AddRecord(const QSqlDatabase* db, const QString& path, bool isFile);
    };

}

