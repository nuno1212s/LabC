//
// Created by nuno on 06-04-2018.
//

#ifndef LABC_JSON_H
#define LABC_JSON_H


#include "StorageManager.h"

#include <unordered_map>

class JSON : public StorageManager {

private:

    std::string userFilePath, postsStoragePath;

    std::unordered_map<unsigned long, Post *> posts;

    std::unordered_map<unsigned long, User *> users;

    JSON () : userFilePath("~/LabC/users.json"), postsStoragePath("~/LabC/posts.json") {

    }

    void loadPosts();

    void savePosts();

    void loadUsers();

    void saveUsers();

    unsigned long nextPostID();

    unsigned long prevPostID();

public:
    std::vector<Post *> *getAllPosts() override;

    std::vector<Post *> *getAllPostsFor(const unsigned long &userID) override;

    Post *getPostWithID(const unsigned long &postID) override;

    Post *createPostWithTitle(const std::string &postTitle, const unsigned long &parentPost,
                              const unsigned long &postingUser) override;

    void updatePostText(const unsigned long &postID, const std::string &postText) override;

    void deletePost(const unsigned long &postID) override;

    Post *getPostWithTitle(const std::string &postTitle) override;

    void saveUser(User *user) override;

    User *getUser(const unsigned long &i) override;

    User *getUserByUsername(const std::string &string) override;

    User *createUserWithUserName(const std::string &string, const std::string &string1) override;

    void updateUserPassword(const unsigned long &i, const std::string &string) override;

};


#endif //LABC_JSON_H
