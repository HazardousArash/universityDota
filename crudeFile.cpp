#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


class User {
protected:
    std::string username;
    std::string password;
    std::string security_card;
    std::string first_name;
    std::string last_name;
    bool isActive; // Added to support soft deletion

public:
    User(const std::string& uname, const std::string& pwd, const std::string& card,
        const std::string& fname, const std::string& lname)
        : username(uname), password(pwd), security_card(card), first_name(fname), last_name(lname), isActive(true) {}

    void deactivate() { isActive = false; } // Soft delete
    void reactivate() { isActive = true; }  // Restore user

    void login() {
        if (isActive) {
            std::cout << "User " << username << " logged in." << std::endl;
        }
        else {
            std::cout << "This account is inactive." << std::endl;
        }
    }

    void logout() {
        std::cout << "User " << username << " logged out." << std::endl;
    }

    std::string getFirstName() const { return first_name; }
    std::string getLastName() const { return last_name; }
    bool getIsActive() const { return isActive; }
    void setUsername(const std::string& newUsername) { username = newUsername; }
    void setPassword(const std::string& newPassword) { password = newPassword; }
    static void saveToFile(const std::vector<User*>& users, const std::string& filename) {
        std::ofstream file(filename);
        for (const auto* user : users) {
            file << user->username << "," << user->password << "," << user->first_name << "," << user->last_name << "\n";
        }
        file.close();
    }

    // New method to load user data from a file
    static void loadFromFile(std::vector<User*>& users, const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string uname, pwd, fname, lname;
            if (std::getline(iss, uname, ',') && std::getline(iss, pwd, ',') &&
                std::getline(iss, fname, ',') && std::getline(iss, lname)) {
                users.push_back(new User(uname, pwd, "12345", fname, lname)); // Replace with the correct constructor
            }
        }
        file.close();
    }
};
class Teacher : public User {
    // Teacher-specific attributes and methods
public:
    Teacher(const std::string& uname, const std::string& pwd, const std::string& card,
        const std::string& fname, const std::string& lname)
        : User(uname, pwd, card, fname, lname) {}
};

class Student : public User {
    // Student-specific attributes and methods
public:
    Student(const std::string& uname, const std::string& pwd, const std::string& card,
        const std::string& fname, const std::string& lname)
        : User(uname, pwd, card, fname, lname) {}
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
    std::vector<User*> teachers;
    std::vector<User*> students;

public:
    GeneralAdmin(const std::string& uname, const std::string& pwd, const std::string& card,
        const std::string& adminId, const std::string& fname, const std::string& lname)
        : User(uname, pwd, card, fname, lname), admin(adminId) {}
    void addUser() {
        char userType;
        std::string fname, lname, uname, pwd;
        std::cout << "Enter user type (T for Teacher, S for Student): ";
        std::cin >> userType;
        std::cout << "Enter first name: ";
        std::cin >> fname;
        std::cout << "Enter last name: ";
        std::cin >> lname;
        std::cout << "Enter username: ";
        std::cin >> uname;
        std::cout << "Enter password: ";
        std::cin >> pwd;

        if (userType == 'T' || userType == 't') {
            teachers.push_back(new Teacher(uname, pwd, "12345", fname, lname));
            std::cout << "Teacher created: " << uname << std::endl;
        }
        else if (userType == 'S' || userType == 's') {
            students.push_back(new Student(uname, pwd, "12345", fname, lname));
            std::cout << "Student created: " << uname << std::endl;
        }
        else {
            std::cout << "Invalid user type entered. Please try again." << std::endl;
        }
        User::saveToFile(teachers, "teachersinfo.txt");
        User::saveToFile(students, "studentsinfo.txt");
    }

    void listUsers() {
        std::ifstream file;
        std::string line, uname, pwd, fname, lname;

        // List Teachers
        file.open("teachersinfo.txt");
        std::cout << "List of Teachers:" << std::endl;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            if (std::getline(iss, uname, ',') && std::getline(iss, pwd, ',') &&
                std::getline(iss, fname, ',') && std::getline(iss, lname)) {
                std::cout << fname << " " << lname << std::endl;
            }
        }
        file.close();

        // List Students
        file.open("studentsinfo.txt");
        std::cout << "List of Students:" << std::endl;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            if (std::getline(iss, uname, ',') && std::getline(iss, pwd, ',') &&
                std::getline(iss, fname, ',') && std::getline(iss, lname)) {
                std::cout << fname << " " << lname << std::endl;
            }
        }
        file.close();
    }
    void addAdmin(const Admin& newAdmin) {
        std::cout << "General Admin " << username << " added Admin " << newAdmin.admin_id << "." << std::endl;
    }
    void addAdmin() {
        std::string uname, pwd, fname, lname;
        std::cout << "Enter new admin's first name: ";
        std::cin >> fname;
        std::cout << "Enter new admin's last name: ";
        std::cin >> lname;
        std::cout << "Enter new admin's username: ";
        std::cin >> uname;
        std::cout << "Enter new admin's password: ";
        std::cin >> pwd;

        // Assuming security_card is not needed at this point
        // Add the new admin to the list of admins
        // You might want to store the new admin in a collection or database
        std::cout << "New admin added: " << uname << " (" << fname << " " << lname << ")" << std::endl;
    }
    void createUser() {
        std::string fname, lname, uname, pwd;
        std::cout << "Enter first name: ";
        std::cin >> fname;
        std::cout << "Enter last name: ";
        std::cin >> lname;
        std::cout << "Enter username: ";
        std::cin >> uname;
        std::cout << "Enter password: ";
        std::cin >> pwd;
        users.push_back(new User(uname, pwd, "12345", fname, lname)); // Assuming security_card is not needed at this point
        std::cout << "User created: " << uname << " (" << fname << " " << lname << ")" << std::endl;
    }

    void readUsers() {
        std::ifstream file("usersinfo.txt");
        std::string line, uname, pwd, fname, lname, isActiveStr;
        bool isActive;

        std::cout << "List of Active Users:" << std::endl;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            if (std::getline(iss, uname, ',') && std::getline(iss, pwd, ',') &&
                std::getline(iss, fname, ',') && std::getline(iss, lname, ',') &&
                std::getline(iss, isActiveStr)) {
                std::istringstream activeStream(isActiveStr);
                activeStream >> std::boolalpha >> isActive;
                if (isActive) {
                    std::cout << fname << " " << lname << std::endl;
                }
            }
        }
        file.close();
    }


    void removeUser() {
        readUsers();
        int index;
        std::cout << "Enter the number of the user you want to deactivate: ";
        std::cin >> index;
        if (index > 0 && index <= users.size() && users[index - 1]->getIsActive()) {
            users[index - 1]->deactivate();
            std::cout << "User " << users[index - 1]->getFirstName() << " " << users[index - 1]->getLastName() << " has been deactivated." << std::endl;
        }
        else {
            std::cout << "Invalid selection or user already inactive." << std::endl;
        }
        User::saveToFile(teachers, "teachersinfo.txt");
        User::saveToFile(students, "studentsinfo.txt");
        User::saveToFile(users, "usersinfo.txt");
    }

    void updateUser() {
        readUsers();
        int index;
        std::string newUsername, newPassword;
        std::cout << "Enter the number of the user you want to update: ";
        std::cin >> index;
        if (index > 0 && index <= users.size() && users[index - 1]->getIsActive()) {
            std::cout << "Enter new username: ";
            std::cin >> newUsername;
            std::cout << "Enter new password: ";
            std::cin >> newPassword;
            users[index - 1]->setUsername(newUsername);
            users[index - 1]->setPassword(newPassword);
            std::cout << "User updated: " << newUsername << std::endl;
        }
        else {
            std::cout << "Invalid selection or user is inactive." << std::endl;
        }
        User::saveToFile(teachers, "teachersinfo.txt");
        User::saveToFile(students, "studentsinfo.txt");
        User::saveToFile(users, "usersinfo.txt");

    }

    void restoreUser() {
        std::cout << "List of inactive users:" << std::endl;
        for (size_t i = 0; i < users.size(); ++i) {
            if (!users[i]->getIsActive()) {
                std::cout << i + 1 << ") " << users[i]->getFirstName() << " " << users[i]->getLastName() << std::endl;
            }
        }
        int index;
        std::cout << "Enter the number of the user you want to reactivate: ";
        std::cin >> index;
        if (index > 0 && index <= users.size() && !users[index - 1]->getIsActive()) {
            users[index - 1]->reactivate();
            std::cout << "User " << users[index - 1]->getFirstName() << " " << users[index - 1]->getLastName() << " has been reactivated." << std::endl;
        }
        else {
            std::cout << "Invalid selection or user already active." << std::endl;
        }
    }
    void hardDeleteUser() {
        readUsers();
        int index;
        std::cout << "Enter the number of the user you want to permanently delete: ";
        std::cin >> index;
        if (index > 0 && index <= users.size()) {
            delete users[index - 1]; // Deallocate memory
            users.erase(users.begin() + (index - 1)); // Remove from vector
            std::cout << "User has been permanently deleted." << std::endl;
        }
        else {
            std::cout << "Invalid selection." << std::endl;
        }
    }
    void mainMenu() {
        int choice;
        do {
            std::cout << "\nMain Menu:" << std::endl;
            std::cout << "1) Modify users" << std::endl;
            std::cout << "2) List of users" << std::endl;
            std::cout << "3) Add other admins" << std::endl;
            std::cout << "4) Activity log" << std::endl;
            std::cout << "5) Messages" << std::endl;
            std::cout << "6) Log out" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                modifyUsersSubMenu();
                break;
            case 2:
                listUsers(); // This method needs to be implemented
                break;
            case 3:
                addAdmin(); // This method needs to be implemented
                break;
            case 4:
                //viewActivityLog(); // This method needs to be implemented
                break;
            case 5:
                //viewMessages(); // This method needs to be implemented
                break;
            case 6:
                std::cout << "Logging out..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } while (choice != 6);
    }
    void modifyUsersSubMenu() {
        int choice;
        do {
            std::cout << "\nModify Users Submenu:" << std::endl;
            std::cout << "1) Add user" << std::endl;
            std::cout << "2) Remove user (soft delete)" << std::endl;
            std::cout << "3) Update user" << std::endl;
            std::cout << "4) Restore user" << std::endl;
            std::cout << "5) Remove user (hard delete)" << std::endl; // New option added
            std::cout << "0) Back to main menu" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            if (choice == 5 && dynamic_cast<GeneralAdmin*>(this) == nullptr) {
                std::cout << "You do not have permission to perform a hard delete." << std::endl;
                continue;
            }
            switch (choice) {
            case 1:
                addUser(); 
                break;
            case 2:
                removeUser();
                break;
            case 3:
                updateUser();
                break;
            case 4:
                restoreUser();
                break;
            case 5:
                hardDeleteUser();
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
        //generalAdmin.readUsers();
        //generalAdmin.modifyUsersSubMenu();
         generalAdmin.mainMenu();

        
    }
    else {
        std::cout << "Invalid username or password. Please try again." << std::endl;
    }

    return 0;
}
