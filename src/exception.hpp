#pragma once

#include <exception>

namespace Photochem{
  
class PhotoException : public std::exception
{
  std::string _msg;
public:
  PhotoException(const std::string& msg) : _msg(msg){}

  virtual const char* what() const noexcept override
  {
    return _msg.c_str();
  }
}; 

}