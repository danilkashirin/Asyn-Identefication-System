#ifndef AUTHENTICATION_LOGGER_H
#define AUTHENTICATION_LOGGER_H

#include "logger.h"
#include "../transaction.h"

class AuthenticationLogger : public Logger {
 public:
  explicit AuthenticationLogger(const std::string& filename);

  // Переопределим виртуальную функцию для логирования AuthenticationTransaction
  void logSpecificTransaction(const Transaction& transaction, bool success) const override;
};

#endif // AUTHENTICATION_LOGGER_H
