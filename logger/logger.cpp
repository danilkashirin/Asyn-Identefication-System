#include "logger.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <utility>

Logger::Logger(std::string  filename) : filename(std::move(filename)) {}

std::future<void> Logger::logTransactionAsync(const Transaction& transaction, bool success) {
  return std::async(std::launch::async, [this, &transaction, success]() {
    // Simulate some processing time
    std::this_thread::sleep_for(std::chrono::seconds(1));

    logTransaction(transaction, success);
  });
}

void Logger::logTransaction(const Transaction& transaction, bool success) {
  logSpecificTransaction(transaction, success);
}

std::string Logger::getCurrentTimestamp() const {
  std::time_t now = std::time(nullptr);
  std::tm* timeInfo = std::localtime(&now);
  char buffer[80];
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
  return {buffer};
}
