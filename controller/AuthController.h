#include "../model/User.h"
#include <string>

class AuthController
{
public:
    User handleLogin(string username, string password);
    AuthController();
    ~AuthController();

private:
    
};
