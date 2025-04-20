#include "pch.h"
#include "RSM_Settings.hpp"



#include "Enumerations.hpp"

namespace RSM_Kernel
{

	const QString RSM_Settings::GetAppDirectory()
	{
		QString docsDir = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first();
		QString appDirPath = QDir::cleanPath(docsDir + QDir::separator() + QString("RengaStylesManager"));
		
		if (!QDir(appDirPath).exists()) QDir().mkdir(appDirPath);

		return appDirPath;
	}

    const QString RSM_Settings::GetAppTempDirectory()
    {
        QString appTmpDirPath = QDir::cleanPath(GetAppDirectory() + QDir::separator() + QString("temp"));
        if (!QDir(appTmpDirPath).exists()) QDir().mkdir(appTmpDirPath);

        return appTmpDirPath;
    }

	const QString RSM_Settings::GetDefaultDbPath()
	{
		QString appDir = this->GetAppDirectory();
        QString defPathDb = QDir::cleanPath(appDir + QDir::separator() + QString("RSM.db"));
        return defPathDb;
	}

    const QString RSM_Settings::GetUniqueDbPath()
    {
        QString appDir = this->GetAppTempDirectory();
        QString uniquePathDb = QDir::cleanPath(appDir + QDir::separator() + QString("RSM_") + QUuid().toString() + QString(".db"));

        return uniquePathDb;
    }

    const QString RSM_Settings::GetTempPath(FileExtensionVariant mode)
    {
        QString ext = MakeExtension(mode);
        QString tmpPath = QDir::cleanPath(this->GetAppTempDirectory() + QDir::separator() + QUuid().toString() + ext);
        if (mode == FileExtensionVariant::Directory && !QDir(tmpPath).exists()) QDir().mkdir(tmpPath);
        return tmpPath;
    }


    QString RSM_Settings::MakeExtension(const FileExtensionVariant& extType)
    {
        QString ext = QString("");
        if (extType == FileExtensionVariant::File_RNP) ext = ".rnp";
        else if (extType == FileExtensionVariant::File_RNT) ext = ".rnt";
        else if (extType == FileExtensionVariant::File_LUA) ext = ".lua";
        else if (extType == FileExtensionVariant::File_JSON) ext = ".json";
        else if (extType == FileExtensionVariant::File_RST) ext = ".rst";
        return ext;
    }
}

