//
// Created by nuno on 01-04-2018.
//

#ifndef LABC_USERMANAGER_H
#define LABC_USERMANAGER_H

#include <iostream>
#include <unordered_map>

class User;

class UserManager {

private:

    std::unordered_map<unsigned long, User*> loadedUsers;

    std::unordered_map<unsigned long, std::string> activeConnections;

public:
    /**
     * Returns a 16 char random string
     * @return
     */
    std::string generateSalt();

    User* createUserWithUsername(const std::string&);

    User* getUser(const unsigned long&);

    std::vector<User*> *getPendingUsers();

    void deleteUser(const unsigned long&);

    std::string generateAccessKey(const unsigned long&);

    ~UserManager();

    User *getUser(const std::string &userName);

    bool isAuthenticated(const unsigned long &userID, const std::string &accessKey);

    void discardOfAccessKey(const unsigned long &userID);
};


#endif //LABC_USERMANAGER_H
