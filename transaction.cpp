#include "transaction.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <utility>

AuthenticationTransaction::AuthenticationTransaction(std::string  username, std::string  password, TransactionType type)
    : username(std::move(username)), password(std::move(password)), type(type) {}

std::future<void> AuthenticationTransaction::execute() {
  return std::async(std::launch::async, [this]() {
    // Simulate some processing time
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Perform transaction-specific actions (e.g., logging to console)
    if (getType() == TransactionType::Create) {
      std::cout << "Creating user: " << username << "\n";
    } else if (getType() == TransactionType::Login) {
      std::cout << "Logging in user: " << username << "\n";
    }

    // Add more actions as needed

  });
}

TransactionType AuthenticationTransaction::getType() const {
  // Return the transaction type
  return TransactionType::Login; // You may want to customize this based on the actual transaction type
}
