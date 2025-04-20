#include "RSM_Settings.hpp"

#include <QStandardPaths>
#include <QUuid>

namespace RSM_Kernel
{

	const QString RSM_Settings::GetAppDirectory()
	{
		QString docsDir = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first();
		QString appDirPath = QDir::cleanPath(docsDir + QDir::separator() + QString("RengaStylesManager"));
		
		if (!QDir(appDirPath).exists()) QDir().mkdir(appDirPath);

		return appDirPath;
	}

	const QString RSM_Settings::GetDefaultDbPath()
	{
		QString appDir = this->GetAppDirectory();
        QString defPathDb = QDir::cleanPath(appDir + QDir::separator() + QString("RSM.db"));
        return defPathDb;
	}

    const QString RSM_Settings::GetUniqueDbPath()
    {
        QString appDir = this->GetAppDirectory();
        QString uniquePathDb = QDir::cleanPath(appDir + QDir::separator() + QString("RSM_") + QUuid().toString() + QString(".db"));

        return uniquePathDb;
    }
}

