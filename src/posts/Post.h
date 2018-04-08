//
// Created by nuno on 27-03-2018.
//
#pragma once

#include <string>
#include <vector>
#include <set>
#include <list>
#include <iostream>

class Post {

private:
    unsigned long parentPost;

    unsigned long postingUser, postID;

    std::string postTitle, postText;

    std::set<unsigned long> *subscribers;

    std::vector<Post *> *subPosts;

public:
    Post(const unsigned long &parentPost, const unsigned long &postingUser, const unsigned long &postID,
         std::string postTitle, std::string postText)
            : parentPost(parentPost), postingUser(postingUser), postID(postID) {

        this->subscribers = new std::set<unsigned long>();
        this->subPosts = new std::vector<Post *>();

        this->postTitle = std::move(postTitle);
        this->postText = std::move(postText);

    }

    Post(const unsigned long &parentPost, const unsigned long &postingUser, const unsigned long &postID,
         std::string postTitle, std::string postText, std::set<unsigned long> *subscribers,
         std::vector<Post *> *subPosts)
            : parentPost(parentPost), postingUser(postingUser), postID(postID), subscribers(subscribers),
              subPosts(subPosts) {

        this->postTitle = std::move(postTitle);
        this->postText = std::move(postText);

    }

    ~Post() {

        std::cout << "Deleting post " << postID << std::endl;

        //auto begin = subPosts->begin();

        //subPosts->clear();

        delete subPosts;
        delete subscribers;

    }

    bool isMainPost() const {
        return parentPost == 0;
    }

    bool isSubPost() const {
        return parentPost != 0;
    }

    unsigned long getParentPost() const {
        return parentPost;
    }

    unsigned long getPostingUser() const {
        return postingUser;
    }

    unsigned long getPostID() const {
        return postID;
    }

    const std::string &getPostTitle() const {
        return postTitle;
    }

    const std::string &getPostText() const {
        return postText;
    }

    void setPostText(std::string postText) {
        this->postText = std::move(postText);
    }

    std::set<unsigned long> *getSubscribers() const {
        return subscribers;
    }

    std::vector<Post *> *getSubPosts() const {
        return subPosts;
    }

    void addSubPost(Post *p) {
        this->subPosts->push_back(p);
    }

    void removeSubPost(Post *post);

    void deletePost();

    void permDeletePost();

    void addSubscriber(const unsigned long &);

    bool removeSubscriber(const unsigned long &);

    std::string toJSON() const;

};

class PostBuilder {

private:
    unsigned long postID, postingUser, parentPost;

    std::string postTitle, postText;

    std::set<unsigned long> *subscribers, *subPostsTemp;

    std::vector<Post *> *subPosts;

public:
    PostBuilder(const unsigned long &postID, const unsigned long &postingUser, const unsigned long &parentPost,
                std::string postTitle, std::string postText, std::set<unsigned long> *subscribers,
                std::set<unsigned long> *subPostsTemp)
            : postID(postID), postingUser(postingUser), parentPost(parentPost), subscribers(subscribers),
              subPostsTemp(subPostsTemp) {

        this->subPosts = new std::vector<Post *>(subPostsTemp->size());
        this->postTitle = std::move(postTitle);
        this->postText = std::move(postText);

    }

    ~PostBuilder() {

        delete subPostsTemp;

    }

    unsigned long getPostID() const {
        return postID;
    }

    unsigned long getParentPost() const {
        return parentPost;
    }

    std::set<unsigned long> *getSubPosts() const {
        return subPostsTemp;
    }

    PostBuilder *addSubPost(Post *p) {

        this->subPosts->push_back(p);

        return this;
    }

    Post *build(std::list<PostBuilder*> *posts) {

        for (unsigned long postID : *subPostsTemp) {

            for (auto subPost : *posts) {
                if (subPost->getPostID() == postID) {

                    addSubPost(subPost->build(posts));

                    delete subPost;

                    break;
                }
            }
        }

        posts->remove_if([this](PostBuilder*& post) -> bool {
            return post->getPostID() == this->getPostID() || this->getSubPosts()->find(post->getPostID()) != this->subPostsTemp->end();
        });

        Post *p = new Post(parentPost, postingUser, postID, postTitle, postText, subscribers, subPosts);

        return p;
    }

};
