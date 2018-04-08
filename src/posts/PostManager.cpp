//
// Created by nuno on 27-03-2018.
//

#include "PostManager.h"
#include "../storage/StorageManager.h"
#include "../Main.h"

Post* PostManager::getPost(const unsigned long &postID) {

    return Main::getStorageManager()->getPostWithID(postID);

}

Post *PostManager::createPost(const std::string &postTitle, const unsigned long &creatingUser, const unsigned long &parentPost) {

    Post *post = Main::getStorageManager()->getPostWithTitle(postTitle);

    if (post != nullptr) {

        delete post;

        return nullptr;

    }

    //TOOO: Create a post
    return Main::getStorageManager()->createPostWithTitle(postTitle, parentPost, creatingUser);
};

std::vector<Post *> * PostManager::loadFeedForUser(const unsigned long &userID) {

    return Main::getStorageManager()->getAllPosts();

}