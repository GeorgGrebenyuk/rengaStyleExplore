#pragma once
#include "pch.h"
#include "RSM_Internals.hpp"

namespace RSM_Kernel
{
	/**@brief Вспомогательный базовый класс с инструментами работы с отдельными таблицами в составе БД
	*/
	class RSM_DatabaseTablesProcessing
	{
	public:

		/**@brief Возвращает наименование данной таблицы
		*/
		virtual const QString GetTableName() = 0;

		/**@brief Создает определение таблицы при её отсутствии в БД
		*/
		virtual void CreateTableDefinition(const QSqlDatabase* db) = 0;

        void DeleteAllData(const QSqlDatabase* db);

        void GetRowByRowid(const QSqlDatabase* db, const qint32 rowid, QSqlQuery* query);

        qint32 GetMaxRowid(const QSqlDatabase* db);

        bool ExecQuerry(const QSqlQuery* query);
	};


}


