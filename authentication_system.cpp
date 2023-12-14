#include "authentication_system.h"
#include <fstream>
#include <coroutine>

AuthenticationSystem::AuthenticationSystem(const std::string& usersFile, AuthenticationLogger& logger)
    : usersFile(usersFile), logger(logger) {}

void AuthenticationSystem::loadUsers() {
  std::ifstream file(usersFile);
  if (file.is_open()) {
    nlohmann::json jsonData;
    file >> jsonData;
    file.close();

    users.clear();
    for (const auto& userJson : jsonData) {
      User user;
      user.id = userJson["id"];
      user.username = userJson["username"];
      user.passwordHash = userJson["passwordHash"];
      users.push_back(user);
    }
  }
}

bool AuthenticationSystem::createUser(const std::string& username, const std::string& password) {
  for (const User& user : users) {
    if (user.username == username) {
      AuthenticationTransaction transaction(username, password, TransactionType::Create);
      transaction.execute().wait();

      logger.logTransactionAsync(transaction, false).wait();
      return false; // User with the same username already exists
    }
  }

  User newUser;
  newUser.id = users.empty() ? 1 : (users.back().id + 1);
  newUser.username = username;
  newUser.passwordHash = std::to_string(polynomialHash(password)); // Convert hash to string
  users.push_back(newUser);

  // Log the transaction
  AuthenticationTransaction transaction(username, password, TransactionType::Create);
  transaction.execute().wait();

  logger.logTransactionAsync(transaction, true).wait();

  // Save the updated users to the file
  nlohmann::json jsonData;
  for (const User& user : users) {
    jsonData.push_back({
                           {"id", user.id},
                           {"username", user.username},
                           {"passwordHash", user.passwordHash}
                       });
  }

  std::ofstream outFile(usersFile);
  if (outFile.is_open()) {
    outFile << jsonData.dump(2); // Pretty-print with an indentation of 2 spaces
    outFile.close();
  }

  return true;
}

User AuthenticationSystem::loginUser(const std::string& username, const std::string& password) {
  size_t inputHash = polynomialHash(password);
  for (const User& user : users) {
    if (user.username == username && std::to_string(inputHash) == user.passwordHash) {
      // Log the transaction
      AuthenticationTransaction transaction(username, password, TransactionType::Login);
      transaction.execute().wait();
      logger.logTransactionAsync(transaction, true).wait();

      return user; // Successful login
    }
  }

  // Log the failed login attempt
  AuthenticationTransaction transaction(username, password, TransactionType::Login);
  transaction.execute().wait();
  logger.logTransactionAsync(transaction, false).wait();

  // Return a User with id = -1 to indicate failed login
  return User{-1, "", ""};
}

size_t AuthenticationSystem::polynomialHash(const std::string& str) {
  const size_t p = 31;  // Простое число
  const size_t m = 1e9 + 9;  // Большое простое число для взятия по модулю

  size_t hashValue = 0;
  size_t pPow = 1;

  for (char c : str) {
    hashValue = (hashValue + (c - 'a' + 1) * pPow) % m;
    pPow = (pPow * p) % m;
  }

  return hashValue;
}
