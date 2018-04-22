//
// Created by nuno on 30-03-2018.
//

#include <iostream>
#include "User.h"

#include "nlohmann/json.hpp"

#define MAX_SUBSCRIBED 30

bool User::subscribeTo(unsigned long &postID) {

    unsigned long size = this->subscribedTo->size();

    if (size >= MAX_SUBSCRIBED) {
        return false;
    }

    this->subscribedTo->insert(postID);

}

bool User::unSubscribeTo(unsigned long &postID) {

    this->subscribedTo->erase(postID);

}

void User::registerCreatedPost(unsigned long &postID) {

    this->createdPosts->insert(postID);

}

void User::deletePost(unsigned long &postID) {

    this->createdPosts->erase(postID);

}

bool User::authenticate(const std::string &hashedPassword) {

    return password == hashedPassword;

}

std::string User::toJSON() {

    using namespace nlohmann;

    json jsonUser;

    jsonUser["UserID"] = this->userID;
    jsonUser["UserName"] = this->userName;

    json j = json::array();

    for (auto iterator = this->createdPosts->begin(); iterator != this->createdPosts->end(); iterator++) {
        j.push_back(*iterator);
    }

    jsonUser["CreatedPosts"] = j;

    j = json::array();

    for (auto iterator = this->subscribedTo->begin(); iterator != this->subscribedTo->end(); iterator++) {
        j.push_back(*iterator);
    }

    jsonUser["SubscribedTo"] = j;

    jsonUser["Salt"] = this->salt;

    return jsonUser.dump(4);
}