#include "pch.h"
#include "RSM_SqliteUtils.hpp"

#include "RSM_Internals.hpp"

namespace RSM_Kernel
{
    RSM_SqliteUtils::RSM_SqliteUtils(const QSqlDatabase* db)
    {
        this->m_db = db;
    }

    void RSM_SqliteUtils::DeleteAllDataFromTable(const QString& tableName)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare("DELETE FROM " + tableName);
        ExecQuerry(&databaseQuery);
    }

    bool RSM_SqliteUtils::GetRowByRowid(const QString& tableName, const qint32 rowid, QSqlQuery* query)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
        query = new QSqlQuery(*tmpDbPtr);

        query->prepare(("SELECT * FROM ") + tableName + " WHERE rowid = " + QString::number(rowid) + ";");
        return ExecQuerry(query);
    }

    qint32 RSM_SqliteUtils::GetMaxRowid(const QString& tableName)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare("SELECT MAX(rowid) FROM" + tableName);
        if (!ExecQuerry(&databaseQuery)) return -1;
        databaseQuery.next();
        qint32 val = databaseQuery.record().value(0).toInt();
        return val;
    }

    bool RSM_SqliteUtils::ExecQuerry(const QSqlQuery* query)
    {
        QSqlQuery* databaseQuery = const_cast<QSqlQuery*>(query);
        if (databaseQuery->exec()) return true;
        throw new RSM_Exception(databaseQuery->lastError().text().toLocal8Bit().data());
        return false;
    }

    bool RSM_SqliteUtils::GetDataByRowid(const QString& tableName, const QString& column, const qint32 rowid, QByteArray* data)
    {
        QVariant var = GetDataByRowid(tableName, column, rowid);
        if (var.isNull()) return false;

        *data = var.toByteArray();
        return true;
    }

    bool RSM_SqliteUtils::GetDataByRowid(const QString& tableName, const QString& column, const qint32 rowid, QString* data)
    {
        QVariant var = GetDataByRowid(tableName, column, rowid);
        if (var.isNull()) return false;

        *data = var.toString();
        return true;
    }

    bool RSM_SqliteUtils::GetDataByRowid(const QString& tableName, const QString& column, const qint32 rowid, qint32* data)
    {
        QVariant var = GetDataByRowid(tableName, column, rowid);
        if (var.isNull()) return false;

        *data = var.toInt();
        return true;

    }

    bool RSM_SqliteUtils::GetDataByRowid(const QString& tableName, const QString& column, const qint32 rowid, double* data)
    {
        QVariant var = GetDataByRowid(tableName, column, rowid);
        if (var.isNull()) return false;

        *data = var.toDouble();
        return true;
    }

    qint32 RSM_SqliteUtils::InsertData(const QString& tableName, const QString& column, QByteArray data)
    {
        QVariant* qdata = new QVariant(data);
        return this->InsertData2(tableName, column, qdata);
    }
    //----------------------
    QVariant RSM_SqliteUtils::GetDataByRowid(const QString& tableName, const QString& column, const qint32 rowid)
    {
        QVariant qvar(QVariant::Type::Invalid);
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare(
            QString("SELECT ") + column + QString(" FROM ") +
            tableName +
            QString(" WHERE rowid = ") + QString::number(rowid));
        if (!ExecQuerry(&databaseQuery)) return qvar;
        databaseQuery.next();
        qvar = databaseQuery.value(0);
        return qvar;
    }

    qint32 RSM_SqliteUtils::InsertData2(const QString& tableName, const QString& column, const QVariant* data)
    {
        QSqlDatabase* tmpDbPtr = const_cast<QSqlDatabase*>(m_db);
        QSqlQuery databaseQuery(*tmpDbPtr);

        databaseQuery.prepare(
            QString("INSERT INTO ") +
            tableName + QString("( ") + column + QString(") values (val_data);"));

        databaseQuery.bindValue(":val_data", data);
        if (ExecQuerry(&databaseQuery)) return GetMaxRowid(tableName);
    }
}
