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

    std::string getFirstName() const {
        return first_name;
    }

    std::string getLastName() const {
        return last_name;
    }
};

class Admin {
public:
    std::string admin_id;

    Admin(const std::string& id) : admin_id(id) {}
};

class GeneralAdmin : public User {
private:
    Admin admin;
    std::vector<User*> users;

public:
    GeneralAdmin(const std::string& uname, const std::string& pwd, const std::string& card,
        const std::string& adminId, const std::string& fname, const std::string& lname)
        : User(uname, pwd, card, fname, lname), admin(adminId) {}

    void addAdmin(const Admin& newAdmin) {
        std::cout << "General Admin " << username << " added Admin " << newAdmin.admin_id << "." << std::endl;
    }

    void createUser(const std::string& uname, const std::string& pwd, const std::string& card,
        const std::string& fname, const std::string& lname) {
        users.push_back(new User(uname, pwd, card, fname, lname));
        std::cout << "User created: " << uname << " (" << fname << " " << lname << ")" << std::endl;
    }

    void readUsers() {
        std::cout << "List of users:" << std::endl;
        for (size_t i = 0; i < users.size(); ++i) {
            std::cout << i + 1 << ") " << users[i]->getFirstName() << " " << users[i]->getLastName() << std::endl;
        }
    }

    void modifyUsersSubMenu() {
        int choice;
        do {
            std::cout << "\nModify Users Submenu:" << std::endl;
            std::cout << "1) Add user" << std::endl;
            std::cout << "2) Remove user" << std::endl;
            std::cout << "3) Update user" << std::endl;
            std::cout << "4) Restore user" << std::endl;
            std::cout << "0) Back to main menu" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                
                break;
            case 2:
               
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 0:
                std::cout << "Returning to main menu." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } while (choice != 0);
    }
};

int main() {
    std::string input_username, input_password;
    std::cout << "Enter your username: ";
    std::cin >> input_username;
    std::cout << "Enter your password: ";
    std::cin >> input_password;

    if (input_username == "Admin" && input_password == "Admin") {
        GeneralAdmin generalAdmin("genadmin", "genpass", "12345", "GA123", "General", "Admin");
        generalAdmin.addAdmin(Admin("A456"));
        generalAdmin.readUsers();
        generalAdmin.modifyUsersSubMenu();
        
    }
    else {
        std::cout << "Invalid username or password. Please try again." << std::endl;
    }

    return 0;
}
