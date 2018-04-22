//
// Created by nuno on 06-04-2018.
//

#include <fstream>
#include <set>
#include <thread>
#include <mutex>
#include "JSON.h"
#include <fstream>
#include "nlohmann/json.hpp"

#include "../users/User.h"
#include "../posts/Post.h"

std::vector<Post *> *JSON::getAllPosts() {

    std::vector<Post *> *posts = new std::vector<Post *>(this->posts.size());

    for (auto post = this->posts.begin(); post != this->posts.end(); post++) {

        posts->push_back(post->second);

    }

    return posts;
}

std::vector<Post *> *JSON::getAllPostsFor(const unsigned long &userID) {

    return getAllPosts();
}

std::vector<Post *> *JSON::getAllPostsWithParent(const unsigned long &parentID) {

    std::vector<Post *> *posts = new std::vector<Post *>();

    for (auto post = this->posts.begin(); post != this->posts.end(); post++) {

        if (post->second->getParentPost() == parentID) {
            posts->push_back(post->second);
        }

    }

    return posts;
}

Post *JSON::getPostWithID(const unsigned long &postID) {
    return this->posts[postID];
}

Post *JSON::createPostWithTitle(const std::string &postTitle, const unsigned long &parentPost,
                                const unsigned long &postingUser) {

    Post *post = new Post(parentPost, postingUser, nextPostID(), postTitle, "");

    this->posts[post->getPostID()] = post;

    return post;
}

void JSON::updatePostText(const unsigned long &postID, const std::string &postText) {

}

void JSON::deletePost(const unsigned long &postID) {

    this->posts.erase(postID);

}

Post *JSON::getPostWithTitle(const std::string &postTitle) {

    Post *postT = nullptr;

    for (auto post = this->posts.begin(); post != this->posts.end(); post++) {

        if (post->second->getPostTitle() == postTitle) {

            postT = post->second;

            break;
        }

    }

    return postT;
}

void JSON::saveUser(User *user) {

    this->users.emplace(user->getUserID(), user);

}

void JSON::deleteUser(const unsigned long &userID) {

    this->users.erase(userID);

}

User *JSON::getUser(const unsigned long &i) {
    return this->users[i];
}

User *JSON::getUserByUsername(const std::string &userName) {

    User *user = nullptr;

    for (auto users = this->users.begin(); users != this->users.end(); users++) {

        if (users->second->getUserName() == userName) {

            user = users->second;

            break;
        }

    }

    return user;
}

User *JSON::createUserWithUserName(const std::string &userName, const std::string &salt) {

    User *user = new User(nextUserID(), userName, "", salt, UserRank::USER);

    this->users.emplace(user->getUserID(), user);

    return user;
}

void JSON::updateUserPassword(const unsigned long &userID, const std::string &saltedPassword) {

    this->users[userID]->setPassword(saltedPassword);

}

void JSON::loadUsers() {

    using namespace nlohmann;

    std::ifstream fileStream;

    fileStream.open(this->userFilePath);

    if (!fileStream.is_open()) {
        std::cout << "File does not exist" << std::endl;

        return;
    }

    json j;

    fileStream >> j;

    this->users.reserve(j.size());

    userLock.lock();

    for (auto iterator = j.begin(); iterator != j.end(); iterator++) {

        json userJSON = *iterator;

        unsigned long userID = userJSON["UserID"];

        std::string userName = userJSON["UserName"], password = userJSON["Password"], salt = userJSON["Salt"];

        json sPosts = userJSON["SubscribedTo"], cPosts = userJSON["CreatedPosts"];

        auto *subscribed = new std::set<unsigned long>(),
                *createdPosts = new std::set<unsigned long>();

        std::for_each(sPosts.begin(), sPosts.end(), [subscribed](unsigned long postID) -> void {
            subscribed->insert(postID);
        });

        std::for_each(cPosts.begin(), cPosts.end(), [createdPosts](unsigned long postID) -> void {
            createdPosts->insert(postID);
        });

        unsigned int rank = userJSON["Rank"];

        User *user = new User(userID, userName, password, salt, static_cast<UserRank>(rank), subscribed, createdPosts);

        this->users.emplace(user->getUserID(), user);
    }

    userLock.unlock();

    fileStream.close();

}

void JSON::saveUsers() {

    using namespace nlohmann;

    json j = json::array();

    std::ofstream fileStream;

    fileStream.open(this->userFilePath);

//    fileStream.exceptions(std::ostream::failbit | std::ostream::badbit);

    this->userLock.lock();

    for (auto iterator = this->users.begin(); iterator != this->users.end(); iterator++) {
        json userJSON = json::object();

        User *user = iterator->second;

        json subscribedTo = json::array(), createdPosts = json::array();

        std::copy(user->getSubscribedTo()->begin(), user->getSubscribedTo()->end(), std::back_inserter(subscribedTo));

        std::copy(user->getCreatedPosts()->begin(), user->getCreatedPosts()->end(), std::back_inserter(createdPosts));

        userJSON["UserID"] = user->getUserID();
        userJSON["UserName"] = user->getUserName();
        userJSON["Password"] = user->getPassword();
        userJSON["Salt"] = user->getSalt();
        userJSON["Rank"] = user->getRank();
        userJSON["SubscribedTo"] = subscribedTo;
        userJSON["CreatedPosts"] = createdPosts;

        j.push_back(userJSON);
    }

    this->userLock.unlock();

    fileStream << j.dump(3);

    fileStream.flush();

    fileStream.close();
}

Post *loadPost(nlohmann::json);

nlohmann::json savePost(Post *post);

void JSON::loadPosts() {

    std::ifstream fileStream;

    fileStream.open(postsStoragePath);

    if (!fileStream.is_open()) {
        std::cout << "File does not exist" << std::endl;

        return;
    }

    using namespace nlohmann;

    json j;

    fileStream >> j;

    this->posts.reserve(j.size());

    postLock.lock();

    for (auto iterator = j.begin(); iterator != j.end(); iterator++) {

        Post *p = loadPost(*iterator);

        this->posts.emplace(p->getPostID(), p);

    }

    postLock.unlock();

    fileStream.close();

}

void JSON::savePosts() {

    std::ofstream fileStream;

    fileStream.open(postsStoragePath);

    using namespace nlohmann;

    json j = json::array();

    this->postLock.lock();

    for (auto iterator = this->posts.begin(); iterator != this->posts.end(); iterator++) {

        Post *post = iterator->second;

        j.push_back(savePost(post));

    }

    this->postLock.unlock();

    fileStream << j.dump(3);

    fileStream.flush();
    fileStream.close();
}

nlohmann::json savePost(Post *post) {

    nlohmann::json postJSON = {};

    postJSON["PostID"] = post->getPostID();
    postJSON["ParentPost"] = post->getParentPost();
    postJSON["PostingUser"] = post->getPostingUser();
    postJSON["PostTitle"] = post->getPostTitle();
    postJSON["PostText"] = post->getPostText();

    nlohmann::json subPosts = nlohmann::json::array(),
            subscribers = nlohmann::json::array();

    for (Post *p : *post->getSubPosts()) {

        subPosts.push_back(savePost(p));

    }

    for (unsigned long subscriber : *post->getSubscribers()) {

        subscribers.push_back(subscriber);

    }

    postJSON["SubPosts"] = subPosts;
    postJSON["Subscribers"] = subscribers;

    return postJSON;
}

Post *loadPost(nlohmann::json j) {

    unsigned long postID = j["PostID"], parentPost = j["ParentPost"], postingUser = j["PostingUser"];

    std::string postTitle = j["PostTitle"], postText = j["PostText"];

    Post *p = new Post(parentPost, postingUser, postID, postTitle, postText);

    nlohmann::json subPost = j["SubPosts"], subscribers = j["Subscribers"];

    for (auto post = subPost.begin(); post != subPost.end(); post++) {

        p->addSubPost(loadPost(*post));

    }

    for (auto subscriber = subscribers.begin(); subscriber != subscribers.end(); subscriber++) {

        p->addSubscriber(*subscriber);

    }

    return p;
}

void JSON::loadAux() {

    using namespace nlohmann;

    json j;

    std::ifstream fileStream;

    fileStream.open(auxStoragePath);

    if (!fileStream.is_open()) {
        this->currentPostID = 1;
        this->currentUserID = 1;
        std::cout << "File does not exist" << std::endl;

        return;
    }

    fileStream >> j;

    this->currentPostID = j["CurrentPostID"];
    this->currentUserID = j["CurrentUserID"];

    fileStream.close();

}

void JSON::saveAux() {

    using namespace nlohmann;

    json j = json::object();

    std::ofstream fileStream;

    fileStream.open(this->auxStoragePath);

    j["CurrentPostID"] = this->currentPostID;
    j["CurrentUserID"] = this->currentUserID;

    fileStream << j.dump(3);

    fileStream.flush();
    fileStream.close();

}
