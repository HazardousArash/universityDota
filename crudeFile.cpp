#include <iostream>
#include <string>
#include <vector>
class User {
protected:
    std::string username;
    std::string password;
    std::string security_card; 
    std::string first_name;    
    std::string last_name;     

public:
    User(const std::string& uname, const std::string& pwd, const std::string& card,
        const std::string& fname, const std::string& lname)
        : username(uname), password(pwd), security_card(card), first_name(fname), last_name(lname) {}

    void login() {
        std::cout << "User " << username << " logged in." << std::endl;
    }

    void logout() {
        std::cout << "User " << username << " logged out." << std::endl;
    }
};