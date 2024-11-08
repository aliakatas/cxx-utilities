#include "custom_exceptions/filesystemitem_exception.hpp"

FilesystemItemDoesNotExist::FilesystemItemDoesNotExist(const char* message) : m_message{ message } {}

FilesystemItemDoesNotExist::FilesystemItemDoesNotExist(const std::string& message) : m_message{ message } {}

const char* FilesystemItemDoesNotExist::what() const noexcept
{
   return m_message.c_str();
}
