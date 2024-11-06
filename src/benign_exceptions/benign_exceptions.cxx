#include "benign_exceptions/benign_exceptions.hpp"

BeningException::BeningException(const char* message) : m_message{ message } {}

BeningException::BeningException(const std::string& message) : m_message{ message } {}

const char* BeningException::what() const noexcept
{
   return m_message.c_str();
}