//
// Created by nuno on 27-03-2018.
//
#ifndef LABC_USER_H
#define LABC_USER_H

#include <string>
#include <set>

class User {

private:
    unsigned long userID;

    std::string userName, password, salt;

    std::set<unsigned long> *subscribedTo, *createdPosts;

public:
    User(const unsigned long &userID, std::string userName, std::string password, std::string salt)
            : userID(userID) {
        this->userName = std::move(userName);
        this->password = std::move(password);
        this->salt = std::move(salt);

        this->subscribedTo = new std::set<unsigned long>();
        this->createdPosts = new std::set<unsigned long>();
    }

    User(const unsigned long &userID, std::string userName, std::string password, std::string salt, std::set<unsigned long>* subscribedTo, std::set<unsigned long>* createdPosts)
            : userID(userID), subscribedTo(subscribedTo), createdPosts(createdPosts) {
        this->userName = std::move(userName);
        this->password = std::move(password);
        this->salt = std::move(salt);
    }

    ~User() {

        delete subscribedTo;
        delete createdPosts;

    }

    const unsigned long getUserID() const {
        return userID;
    }

    const std::string &getUserName() const {
        return userName;
    }

    const std::string &getPassword() const {
        return password;
    }

    const std::string &getSalt() const {
        return salt;
    }

    const std::set<unsigned long> *getSubscribedTo() const {
        return subscribedTo;
    }

    const std::set<unsigned long> *getCreatedPosts() const {
        return createdPosts;
    }

    void registerCreatedPost(unsigned long &);

    void deletePost(unsigned long &);

    bool subscribeTo(unsigned long &);

    bool unSubscribeTo(unsigned long &);

    std::string toJSON();

    /**
     * Authenticate the user
     *
     * Requires a password that is already hashed and salted
     *
     * @param hashedPassword
     * @return
     */
    bool authenticate(const std::string& hashedPassword);

};

#endif //LABC_USER_H