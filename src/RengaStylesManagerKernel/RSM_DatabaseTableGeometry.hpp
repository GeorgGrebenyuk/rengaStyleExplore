#pragma once
#include "RSM_DatabaseTablesProcessing.hpp"
#include "RSM_GeometryObj.hpp"

namespace RSM_Kernel
{
    class RSM_DatabaseTableGeometry : public RSM_DatabaseTablesProcessing
    {
    public:
        RSM_DatabaseTableGeometry(const QSqlDatabase* db);
        const QString GetTableName() override;
        void CreateTableDefinition() override;

        qint32 AddGeometry(const QString& filePath);
        qint32 AddGeometry(const QByteArray& bytes);
        RSM_GeometryObj GetGeometry(const qint32 rowid);
    };
}

