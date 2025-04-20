#pragma once
#include "pch.h"

namespace RSM_Kernel
{
    class RSM_SqliteUtils
    {
    public:
        RSM_SqliteUtils(const QSqlDatabase* db);

        void DeleteAllDataFromTable(const QString& tableName);

        bool GetRowByRowid(const QString& tableName, const qint32 rowid, QSqlQuery* query);

        qint32 GetMaxRowid(const QString& tableName);

        bool ExecQuerry(const QSqlQuery* query);

        //Получение одиночных данных
        bool GetDataByRowid(const QString& tableName, const QString& column, const qint32 rowid, QByteArray* data);
        bool GetDataByRowid(const QString& tableName, const QString& column, const qint32 rowid, QString* data);
        bool GetDataByRowid(const QString& tableName, const QString& column, const qint32 rowid, qint32* data);
        bool GetDataByRowid(const QString& tableName, const QString& column, const qint32 rowid, double* data);

        //Запись данных
        qint32 InsertData(const QString& tableName, const QString& column, QByteArray data);

    private:
        qint32 InsertData2(const QString& tableName, const QString& column, const QVariant* data);
        QVariant GetDataByRowid(const QString& tableName, const QString& column, const qint32 rowid);
        const QSqlDatabase* m_db;
    };
}


