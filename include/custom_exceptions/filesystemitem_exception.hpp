#pragma once

#include <stdexcept>
#include <string>

class FilesystemItemDoesNotExist : public std::exception
{
public:

   explicit FilesystemItemDoesNotExist(const char* message);

   explicit FilesystemItemDoesNotExist(const std::string& message);

   virtual ~FilesystemItemDoesNotExist() noexcept = default;

   const char* what() const noexcept override;

private:

   std::string m_message;

};