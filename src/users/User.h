//
// Created by nuno on 27-03-2018.
//
#ifndef LABC_USER_H
#define LABC_USER_H

#include <string>
#include <set>

enum UserRank {

    ADMIN = 0,
    MOD = 1,
    USER = 2,
    PENDING = 3

};

class User {

private:
    unsigned long userID;

    std::string userName, password, salt;

    std::set<unsigned long> *subscribedTo, *createdPosts;

    UserRank rank;

public:
    User(const unsigned long &userID, std::string userName, std::string password, std::string salt, UserRank rank)
            : userID(userID), rank(rank) {
        this->userName = std::move(userName);
        this->password = std::move(password);
        this->salt = std::move(salt);

        this->subscribedTo = new std::set<unsigned long>();
        this->createdPosts = new std::set<unsigned long>();
    }

    User(const unsigned long &userID, std::string userName, std::string password, std::string salt, UserRank rank,
         std::set<unsigned long>* subscribedTo, std::set<unsigned long>* createdPosts)
            : userID(userID), subscribedTo(subscribedTo), createdPosts(createdPosts), rank(rank) {
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

    UserRank getRank() const {
        return rank;
    }

    void setRank(UserRank rank) {
        this->rank = rank;
    }

    void setPassword(std::string password) {
        this->password = std::move(password);
    }

    void registerCreatedPost(unsigned long &postID);

    void deletePost(unsigned long &postID);

    bool subscribeTo(unsigned long &postID);

    bool unSubscribeTo(unsigned long &postID);

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