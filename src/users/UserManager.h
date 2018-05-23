//
// Created by nuno on 01-04-2018.
//

#ifndef LABC_USERMANAGER_H
#define LABC_USERMANAGER_H

#include <iostream>
#include <unordered_map>
#include <vector>

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

    std::vector<User *> *getAllUsers();

    void deleteUser(const unsigned long&);

    std::string generateAccessKey(const unsigned long&);

    ~UserManager();

    User *getUser(const std::string &userName);

    bool isAuthenticated(const unsigned long &userID, const std::string &accessKey);

    void discardOfAccessKey(const unsigned long &userID);

    /**
     * Posts created by user in the last X amount of seconds
     * @param user
     * @param time
     * @return
     */
    std::vector<Post *> *postsInTheLastTime(User *user, unsigned long time);

};


#endif //LABC_USERMANAGER_H
