#pragma once
#include "pch.h"
#include "RSM_DatabaseTablesProcessing.hpp"
#include "Enumerations.hpp"

namespace RSM_Kernel
{
    struct RSM_DatabaseTablePaths_RowDefinition
    {
    public:
        qint32 rowid = -1;
        QString path;
        qint32 ext;
    };
    class RSM_DatabaseTablePaths : public RSM_DatabaseTablesProcessing
    {
    public:
        RSM_DatabaseTablePaths(const QSqlDatabase* db);
        const QString GetTableName() override;
        void CreateTableDefinition() override;
        qint32 AddFile(const QString& filePath);
        qint32 AddDirectory(const QString& dirPath);
        RSM_DatabaseTablePaths_RowDefinition GetData(const qint32& rowid);
    private:
        qint32 AddRecord(const QString& path, FileExtensionVariant extType);
    };

}

