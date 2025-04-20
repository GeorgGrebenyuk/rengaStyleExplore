#pragma once
#include "RSM_DatabaseTablesProcessing.hpp"
#include <QByteArray>

namespace RSM_Kernel
{
    class RSM_DatabaseTableBindata: public RSM_DatabaseTablesProcessing
    {
    public:
        const QString GetTableName() override;
        void CreateTableDefinition(const QSqlDatabase* db) override;

        qint32 AddData(const QSqlDatabase* db, const QString& filePath);
        qint32 AddData(const QSqlDatabase* db, const QByteArray data);
        void GetData(const QSqlDatabase* db, const qint32 rowid, QByteArray* data);
    };
}

