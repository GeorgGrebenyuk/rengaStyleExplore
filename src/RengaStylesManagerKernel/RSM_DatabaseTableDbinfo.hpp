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
        const QString GetTableName() override;
        void CreateTableDefinition(const QSqlDatabase* db) override;
        void SetData(const QSqlDatabase* db, const QString& key, const QString& value);
        void GetAllData(const QSqlDatabase* db, QMap<QString, QString>& data);
    };
}

