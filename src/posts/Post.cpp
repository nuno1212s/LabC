//
// Created by nuno on 29-03-2018.
//

#include <json.hpp>
#include "PostManager.h"
#include "../storage/StorageManager.h"
#include "../Main.h"
#include "Post.h"

void Post::addSubPost(Post *p) {

    this->subPosts->push_back(p);

    if (this->subPosts->size() > maxSubPosts) {

        //Make sure the most recent posts are first
        this->sortPosts();

        while (this->subPosts->size() > maxSubPosts) {
            this->subPosts->pop_back();
        }
    }

}

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
    j["CreationDate"] = this->postDate;
    j["Creator"] = this->postingUser;

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

void Post::setPostText(std::string postText) {

    Main::getStorageManager()->updatePostText(getPostID(), postText);

    this->postText = std::move(postText);
}

unsigned int Post::postsInTheLastAmountOfTime(const unsigned long &amountOfTime) {

    unsigned int postsInTheLast24Hrs = 0;

    unsigned long currentTime = (unsigned long) time(nullptr);

    if (currentTime - this->postDate < amountOfTime) {
        postsInTheLast24Hrs++;
    }

    std::for_each(this->subPosts->begin(), this->subPosts->end(), [&postsInTheLast24Hrs, amountOfTime](Post *post) -> void {

        postsInTheLast24Hrs += post->postsInTheLastAmountOfTime(amountOfTime);

    });

    return postsInTheLast24Hrs;
}

void Post::sortPosts() {

    std::vector<Post *> *subPosts = this->subPosts;

    std::sort(subPosts->begin(), subPosts->end(), [](Post *p, Post *p2) -> bool {
        return p->getPostDate() > p2->getPostDate();
    });

    std::for_each(subPosts->begin(), subPosts->end(), [](Post *post) -> void {
        post->sortPosts();
    });

}