#pragma once

#include <stdexcept>
#include <string>

class BeningException : public std::exception
{
public:

   explicit BeningException(const char* message);

   explicit BeningException(const std::string& message);

   virtual ~BeningException() noexcept = default;

   const char* what() const noexcept override;

private:

   std::string m_message;

};