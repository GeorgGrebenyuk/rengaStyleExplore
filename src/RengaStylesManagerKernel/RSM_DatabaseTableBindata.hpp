#pragma once
#include "RSM_DatabaseTablesProcessing.hpp"

namespace RSM_Kernel
{
    class RSM_DatabaseTableBindata : public RSM_DatabaseTablesProcessing
    {
    public:
        RSM_DatabaseTableBindata(const QSqlDatabase* db);
        const QString GetTableName() override;
        void CreateTableDefinition() override;

        qint32 AddData(const QString& filePath);
        qint32 AddData(const QByteArray data);
        void GetData(const qint32 rowid, QByteArray* data);
    };
}


