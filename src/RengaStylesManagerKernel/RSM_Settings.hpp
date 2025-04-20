#pragma once
#include "pch.h"
#include "Enumerations.hpp"

namespace RSM_Kernel
{
	/**@brief Настройки программы, пути и прочее
	*/
	class RSM_Settings
	{
	public:
		RSM_Settings() {};

		/**@brief Возвращает абсолютный путь до папки с данными приложения (папка пользователя, документы ...), не APPDATA
		*/
		const QString GetAppDirectory();

        /**@brief Возвращает абсолютный путь до папки с временными данными
        */
        const QString GetAppTempDirectory();

		/**@brief Возвращает абсолютный файловый путь до файла sqlite с БД
		*/
		const QString GetDefaultDbPath();

        /**@brief Возвращает абсолютный файловый путь файла sqlite c БД с уникальным именем (uuid)
        */
        const QString GetUniqueDbPath();

        /**@brief Возвращает временный путь к файлу или папке
        */
        const QString GetTempPath(FileExtensionVariant mode);

        QString MakeExtension(const FileExtensionVariant& extType);
	};
}


