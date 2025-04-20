#pragma once
#include "pch.h"
#include "RSM_DatabaseTablesProcessing.hpp"


namespace RSM_Kernel
{
    /**@brief Класс для работы с таблицей БД Dbinfo (общая информация о БД)
    */
    class RSM_DatabaseTableDbinfo : public RSM_DatabaseTablesProcessing
    {
    public:
        RSM_DatabaseTableDbinfo(const QSqlDatabase* db);
        const QString GetTableName() override;
        void CreateTableDefinition() override;
        void SetData(const QString& key, const QString& value);
        void GetAllData(QMap<QString, QString>& data);
    };
}

