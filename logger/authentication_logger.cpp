#include "authentication_logger.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <sstream>

AuthenticationLogger::AuthenticationLogger(const std::string& filename) : Logger(filename){}

void AuthenticationLogger::logSpecificTransaction(const Transaction& transaction, bool success) const {
  const auto* authTransaction = dynamic_cast<const AuthenticationTransaction*>(&transaction);
  std::ofstream file(filename, std::ios_base::app);
  if (file.is_open()) {
    file << "[" << getCurrentTimestamp() << "] ";
    if (authTransaction->type == TransactionType::Login) {
      file << "login ";
    } else {
      file << "create ";
    }
    file << "username: " << authTransaction->username
         << " password: " << authTransaction->password;
    if (success) {
      file << " (valid)\n";
    } else {
      file << " (invalid)\n";
    }
    file.close();
  } else {
    std::cerr << "Failed to open log file: " << filename << "\n";
  }
}

