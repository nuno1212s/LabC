//
// Created by nuno on 01-04-2018.
//

#include <algorithm>
#include <random>
#include "../storage/StorageManager.h"
#include "User.h"
#include "UserManager.h"
#include "../Main.h"

const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
const size_t max_index = (sizeof(charset) - 1);


std::default_random_engine engine;

std::uniform_int_distribution<int> distribution(0, max_index);

auto randchar = []() -> char {
    return charset[distribution(engine)];
};


std::string random_string(size_t length) {
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}


std::string UserManager::generateSalt() {

    return random_string(16);

}

std::string UserManager::generateAccessKey(const unsigned long &userID) {

    std::string accessKey = random_string(64);

    this->activeConnections.emplace(userID, accessKey);

    return accessKey;
}

bool UserManager::isAuthenticated(const unsigned long &userID, const std::string &accessKey) {

    if (this->activeConnections.find(userID) != this->activeConnections.end()) {

        return this->activeConnections[userID] == accessKey;

    }

    return false;
}

void UserManager::discardOfAccessKey(const unsigned long &userID) {

    this->activeConnections.erase(userID);

}

User *UserManager::createUserWithUsername(const std::string &userName) {

    User *user;

    if ((user = getUser(userName)) != nullptr) {

        return nullptr;

    }

    return Main::getStorageManager()->createUserWithUserName(userName, generateSalt());
}

User *UserManager::getUser(const unsigned long &userID) {

    if (this->loadedUsers.find(userID) != this->loadedUsers.end()) {

        return this->loadedUsers[userID];
    } else {

        User *user = Main::getStorageManager()->getUser(userID);

        if (user == nullptr) {
            return nullptr;
        }

        this->loadedUsers[userID] = user;

        return user;
    }
}

User *UserManager::getUser(const std::string &userName) {

    for (auto it = this->loadedUsers.begin(); it != this->loadedUsers.end(); it++) {

        if (it->second->getUserName() == userName) {

            return it->second;

        }

    }

    return Main::getStorageManager()->getUserByUsername(userName);
}


UserManager::~UserManager() {

    for (auto it = this->loadedUsers.begin(); it != this->loadedUsers.end(); it++) {

        delete it->second;

    }

}

std::vector<User *> *UserManager::getPendingUsers() {

    return Main::getStorageManager()->getUsersWithRank(UserRank::PENDING);

}

void UserManager::deleteUser(const unsigned long &userID) {

    Main::getStorageManager()->deleteUser(userID);

}