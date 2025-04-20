#include "pch.h"
#include "RSM_Internals.hpp"

namespace RSM_Kernel
{
    RSM_Exception::RSM_Exception(const QString& exceptionText) noexcept : mMessage(exceptionText)
    {

    }

    RSM_Exception::RSM_Exception(const RSM_Exception& other)
    {
        this->mMessage = other.mMessage;
    }

    void RSM_Exception::raise() const
    {
        throw* this;
    }

    RSM_Exception* RSM_Exception::clone() const
    {
        return new RSM_Exception(*this);
    }

    const char* RSM_Exception::what() const noexcept
    {
        return this->mMessage.toStdString().c_str();
    }
}
