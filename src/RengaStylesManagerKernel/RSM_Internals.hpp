#pragma once
#include "pch.h"

namespace RSM_Kernel
{
    class RSM_Exception : public QException
    {
    public:
        RSM_Exception(const QString& exceptionText = "") noexcept;
        RSM_Exception(const RSM_Exception& other);

        void raise() const override;
        RSM_Exception* clone() const override;
        const char* what() const noexcept override;
    private:
        QString mMessage;
    };
}


