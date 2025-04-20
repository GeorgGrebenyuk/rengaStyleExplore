#pragma once
#include <QString>

namespace RSM_Kernel
{
    /**@brief Вспомгательный класс для чтения данных файла Renga
    */
    class RSM_RengaFileReading
    {
    public:
        RSM_RengaFileReading(const QString& path);
        //QString GetVersion();
        //void Close();
    private:
        QString mPath;
        
    };
}

