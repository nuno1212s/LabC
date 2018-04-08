//
// Created by nuno on 29-03-2018.
//

#include <json.hpp>
#include "PostManager.h"
#include "../storage/StorageManager.h"
#include "../Main.h"
#include "Post.h"

void Post::removeSubPost(Post *post) {

    for (auto iterator = this->subPosts->begin(); iterator < this->subPosts->end(); iterator++) {
        if ((*iterator)->getPostID() == post->getPostID()) {
            this->subPosts->erase(iterator);
            break;
        }
    }

}

void Post::deletePost() {

    if (this->getParentPost() != 0) {
        Post *post = Main::getPostManager()->getPost(this->getParentPost());

        post->removeSubPost(this);
    }

    delete this;
}

void Post::permDeletePost() {

    if (this->getParentPost() != 0) {
        Post *post = Main::getPostManager()->getPost(this->getParentPost());

        post->removeSubPost(this);
    }

    Main::getStorageManager()->deletePost(this->getPostID());

    for (Post* post : *subPosts) {
        post->permDeletePost();
    }

    delete this;
}

void Post::addSubscriber(const unsigned long &userID) {

    this->subscribers->insert(userID);

}

bool Post::removeSubscriber(const unsigned long &userID) {

    auto iter = this->subscribers->find(userID);

    if (iter != this->subscribers->end()) {

        this->subscribers->erase(iter);

        return true;
    }

    return false;
}

std::string Post::toJSON() const {

    using namespace nlohmann;

    json j = json::object();

    j["PostID"] = this->getPostID();
    j["ParentPost"] = this->getParentPost();
    j["PostingUser"] = this->getPostingUser();
    j["Title"] = this->getPostTitle();
    j["Text"] = this->getPostText();

    json subscribers = json::array(), posts = json::array();

    std::for_each(this->subscribers->begin(), this->subscribers->end(), [&subscribers](const unsigned long& userID) -> void {

        subscribers.push_back(userID);

    });

    std::for_each(this->subPosts->begin(), this->subPosts->end(), [&posts](const Post *p) -> void {

        posts.push_back(p->toJSON());

    });

    j["Subscribers"] = subscribers;
    j["SubPosts"] = posts;

    return j.dump(4);
}