#include <iostream>
#include "authentication_system.h"
#include "logger/authentication_logger.h"

int main() {
  // Create an instance of AuthenticationLogger
  AuthenticationLogger logger("log.txt");

  // Create an instance of AuthenticationSystem with the logger
  AuthenticationSystem authSystem("users.json", logger);

  // Load existing users
  authSystem.loadUsers();

  // Allow the user to register or log in
  while (true) {
    std::cout << "Choose an option:\n";
    std::cout << "1. Register\n";
    std::cout << "2. Log In\n";
    std::cout << "3. Exit\n";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
      // Register a new user
      std::string username, password;
      std::cout << "Enter username: ";
      std::cin >> username;
      std::cout << "Enter password: ";
      std::cin >> password;

      if (authSystem.createUser(username, password)) {
        std::cout << "User created successfully.\n";
      } else {
        std::cout << "Failed to create user. Username may already exist.\n";
      }
    } else if (choice == 2) {
      // Log in
      std::string username, password;
      std::cout << "Enter username: ";
      std::cin >> username;
      std::cout << "Enter password: ";
      std::cin >> password;

      User loggedInUser = authSystem.loginUser(username, password);
      if (loggedInUser.id != -1) {
        std::cout << "Login successful. Welcome, " << loggedInUser.username << "!\n";
      } else {
        std::cout << "Login failed. Invalid username or password.\n";
      }
    } else if (choice == 3) {
      // Exit the program
      break;
    } else {
      std::cout << "Invalid choice. Please try again.\n";
    }
  }

  return 0;
}
