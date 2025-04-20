#pragma once
#include "pch.h"
#include <QString>

namespace RSM_Kernel
{
    class RSM_Exception : public QException
    {
    public:
        RSM_Exception(const QString& exceptionText = "") noexcept : mMessage(exceptionText) {};
        RSM_Exception(const RSM_Exception& other) { this->mMessage = other.mMessage; }

        void raise() const override { throw* this; }
        void raise() const override{ throw * this; }
        RSM_Exception* clone() const override { return new RSM_Exception(*this); }
        const char* what() const noexcept { return this->mMessage.toStdString().c_str(); }
    private:
        QString mMessage;
    };
}


