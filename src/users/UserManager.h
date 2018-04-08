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

public:
    /**
     * Returns a 16 char random string
     * @return
     */
    std::string generateSalt();

    User* createUserWithUsername(const std::string&);

    User* getUser(const unsigned long&);

    std::string generateAccessKey(const unsigned long&);

    ~UserManager();

    User *getUser(const std::string &userName);
};


#endif //LABC_USERMANAGER_H
