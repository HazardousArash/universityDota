#ifndef USER_H
#define USER_H


#include <string>

class User {
protected:
    std::string firstname;
    std::string lastname;
    std::string username;
    std::string password;
    int status;  // 1 for active, 0 for removed
public:
    User(std::string fn, std::string ln, std::string un, std::string pw, int status = 1);
    std::string getFirstname() const;
    std::string getLastname() const;
    std::string getUsername() const;
    std::string getPassword() const;
    int getStatus() const;
    void setUsername(std::string un);
    void setPassword(std::string pw);
    void setStatus(int status);
};
#endif
