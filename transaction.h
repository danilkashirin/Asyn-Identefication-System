#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <future>

enum class TransactionType {
  Create,
  Login,
  Delete
};

class Transaction {
 public:
  virtual ~Transaction() = default;
  virtual std::future<void> execute() = 0;
  virtual TransactionType getType() const = 0;
};

class AuthenticationTransaction : public Transaction {
 public:
  std::string username;
  std::string password;
  TransactionType type;

 public:
  AuthenticationTransaction(std::string  username, std::string  password, TransactionType type);

  std::future<void> execute() override;
  [[nodiscard]] TransactionType getType() const override;
};

#endif // TRANSACTION_H
