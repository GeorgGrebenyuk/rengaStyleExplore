#pragma once
#include "pch.h"
#include "RSM_DatabaseTablesProcessing.hpp"

namespace RSM_Kernel
{
    class RSM_DatabaseTableRengaProjects : public RSM_DatabaseTablesProcessing
    {
    public:
        RSM_DatabaseTableRengaProjects(const QSqlDatabase* db);
        const QString GetTableName() override;
        void CreateTableDefinition() override;

        qint32 AddRengaProject(const QString& projectPath);
        QString GetProjectFile(const qint32& rowid);
    };
}


