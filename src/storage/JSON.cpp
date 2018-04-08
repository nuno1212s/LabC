//
// Created by nuno on 06-04-2018.
//

#include "JSON.h"

#include "../users/User.h"
#include "../posts/Post.h"

std::vector<Post *> *JSON::getAllPosts() {

    std::vector<Post *> * posts = new std::vector<Post *>(this->posts.size());

    for (auto post = this->posts.begin(); post != this->posts.end(); post++) {

        posts->push_back(post->second);

    }

    return posts;
}

std::vector<Post *> *JSON::getAllPostsFor(const unsigned long &userID) {

    return getAllPosts();
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

    Post *post = getPostWithID(postID);

    if (post == nullptr) {
        return;
    }

    post->setPostText(postText);

}

void JSON::deletePost(const unsigned long &postID) {

    this->posts.erase(postID);

}

Post *JSON::getPostWithTitle(const std::string &postTitle) {

    Post *postT = nullptr;

    for (auto post = this->posts.begin(); post != this->posts.end(); post++) {

        if (post->second->getTitle() == postTitle) {

            postT = post->second;

            break;
        }

    }

    return postT;
}

void JSON::saveUser(User *user) {

    this->users.insert(user->getUserID(), user);

}

User *JSON::getUser(const unsigned long &i) {
    return this->users[i];
}

User *JSON::getUserByUsername(const std::string &string) {

    User *user = nullptr;



    return nullptr;
}

User *JSON::createUserWithUserName(const std::string &string, const std::string &string1) {
    return nullptr;
}

void JSON::updateUserPassword(const unsigned long &i, const std::string &string) {

}
