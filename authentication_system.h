#ifndef AUTHENTICATION_SYSTEM_H
#define AUTHENTICATION_SYSTEM_H

#include <string>
#include <vector>
#include <future>
#include "user.h"
#include "logger/authentication_logger.h"
#include "nlohmann/json.hpp"

class AuthenticationSystem {
 private:
  std::string usersFile;
  std::vector<User> users;
  AuthenticationLogger& logger;

  // Простая реализация полиномиального хеширования
  size_t polynomialHash(const std::string& str);

 public:
  AuthenticationSystem(const std::string& usersFile, AuthenticationLogger& logger);

  void loadUsers();
  bool createUser(const std::string& username, const std::string& password);
  User loginUser(const std::string& username, const std::string& password);
};

#endif // AUTHENTICATION_SYSTEM_H
