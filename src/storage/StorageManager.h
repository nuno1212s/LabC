//
// Created by nuno on 27-03-2018.
//

#ifndef LABC_MYSQLHANDLER_H
#define LABC_MYSQLHANDLER_H

#include <vector>
#include <iostream>

class User;
class Post;

class StorageManager {

public:

    StorageManager() = default;

    virtual std::vector<Post *> *getAllPosts() = 0;

    virtual std::vector<Post *> *getAllPostsFor(const unsigned long &userID) = 0;

    virtual std::vector<Post *> *getAllPostsWithParent(const unsigned long &postID) = 0;

    virtual Post *getPostWithID(const unsigned long &postID) = 0;

    virtual Post *createPostWithTitle(const std::string &postTitle, const unsigned long &parentPost, const unsigned long &postingUser) = 0;

    virtual void updatePostText(const unsigned long &postID, const std::string &postText) = 0;

    virtual void deletePost(const unsigned long &postID) = 0;

    virtual Post *getPostWithTitle(const std::string &postTitle) = 0;

    virtual void saveUser(User *) = 0;

    virtual void deleteUser(const unsigned long &userID) = 0;

    virtual User *getUser(const unsigned long &) = 0;

    virtual User *getUserByUsername(const std::string &) = 0;

    virtual User *createUserWithUserName(const std::string &, const std::string &) = 0;

    virtual void updateUserPassword(const unsigned long &, const std::string&) = 0;

};


#endif //LABC_MYSQLHANDLER_H
