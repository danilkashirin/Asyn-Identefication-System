#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <future>
#include "../transaction.h"

class Logger {
 public:
  std::string filename;

  Logger(std::string  filename);
  std::future<void> logTransactionAsync(const Transaction& transaction, bool success);
  void logTransaction(const Transaction& transaction, bool success);
  virtual void logSpecificTransaction(const Transaction& transaction, bool success) const = 0;
  std::string getCurrentTimestamp() const;
};

#endif // LOGGER_H
