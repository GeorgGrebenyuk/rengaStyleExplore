#pragma once
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>

#include "RSM_DatabaseTablesProcessing.hpp"
#include "RSM_DatabaseTableDbinfo.hpp"
#include "RSM_DatabaseTablePaths.hpp"

namespace RSM_Kernel
{
	/**@brief Описывает базу данных со стилями
	*/
	class RSM_Database
	{
	public:
		//----------Constructors------------------------------------------
        /**@brief Создает новое определение БД
        */
        RSM_Database();

		/**@brief Открывает БД по пути
		*/
		RSM_Database(const QString& path);

		

		//----------Methods-----------------------------------------------
		//Работа с данными
        const RSM_DatabaseTableDbinfo* GetTableDbInfo();

		/**@brief Сохраняет БД в файл
		*/
		void Save(const QString& path, bool Owerrite = true);
    protected:
        const QSqlDatabase* GetDatabase();
    private:
        const RSM_DatabaseTableDbinfo* mTableDbInfo = nullptr;
        QSqlDatabase mRSM_db;
	};
}


