#include "AuthController.h"
#include "../data/UserDAO.h"
#include "../model/User.h"
#include <string>

AuthController::AuthController() {}

AuthController::~AuthController() {}

User AuthController::handleLogin(string username, string password) {
    UserDAO userDAO = new UserDAO();

    User user = userDAO.authenticate(username, password);

    delete userDAO;

    return user;
}