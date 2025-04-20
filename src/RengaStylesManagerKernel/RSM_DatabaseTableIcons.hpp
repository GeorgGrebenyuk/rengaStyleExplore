#pragma once
#include "RSM_DatabaseTablesProcessing.hpp"

#include <QImage>

namespace RSM_Kernel
{
    class RSM_DatabaseTableIcons : public RSM_DatabaseTablesProcessing
    {
    public:
        RSM_DatabaseTableIcons(const QSqlDatabase* db);
        const QString GetTableName() override;
        void CreateTableDefinition() override;

        qint32 AddIcon(const QString& filePath);
        qint32 AddIcon(const QImage data);
        void GetIcon(const qint32 rowid, QImage* icon);
    };
}
