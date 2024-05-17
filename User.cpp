#include "User.h"

User::User(std::string fn, std::string ln, std::string un, std::string pw, int status)
    : firstname(fn), lastname(ln), username(un), password(pw), status(status) {}

std::string User::getFirstname() const {
    return firstname;
}

std::string User::getLastname() const {
    return lastname;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

int User::getStatus() const {
    return status;
}

void User::setUsername(std::string un) {
    username = un;
}

void User::setPassword(std::string pw) {
    password = pw;
}

void User::setStatus(int status) {
    this->status = status;
}