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
		virtual void CreateTableDefinition() = 0;

    protected:
        const QSqlDatabase* m_db;
	};


}


