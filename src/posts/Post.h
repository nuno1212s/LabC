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

    unsigned long postDate;

    std::string postTitle, postText;

    //Guarda os subscritores caso o Post seja um topico e os likes caso seja um post ou um comentário
    std::set<unsigned long> *subscribers;

    //Guarda todos os posts que estao abaixo deste
    std::vector<Post *> *subPosts;

    unsigned int maxSubPosts;

public:
    Post(const unsigned long &parentPost, const unsigned long &postingUser, const unsigned long &postID,
         std::string postTitle, std::string postText = "")
            : parentPost(parentPost), postingUser(postingUser), postID(postID),
              postDate((unsigned long) time(nullptr)), maxSubPosts(50) {

        this->subscribers = new std::set<unsigned long>();
        this->subPosts = new std::vector<Post *>();

        this->postTitle = std::move(postTitle);
        this->postText = std::move(postText);

    }

    Post(const unsigned long &parentPost, const unsigned long &postingUser, const unsigned long &postID,
         const unsigned long &postDate, std::string postTitle, std::string postText
            , std::set<unsigned long> *subscribers, std::vector<Post *> *subPosts, unsigned int maxSubPosts = 50)
            : parentPost(parentPost), postingUser(postingUser), postID(postID), subscribers(subscribers),
              subPosts(subPosts), postDate(postDate), maxSubPosts(maxSubPosts) {

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

    unsigned long getPostDate() const {
        return postDate;
    }

    const std::string &getPostTitle() const {
        return postTitle;
    }

    const std::string &getPostText() const {
        return postText;
    }

    void setPostText(std::string postText);

    std::set<unsigned long> *getSubscribers() const {
        return subscribers;
    }

    std::vector<Post *> *getSubPosts() const {
        return subPosts;
    }

    unsigned int getMaxSubPosts() const {
        return maxSubPosts;
    }

    void setMaxSubPosts(unsigned int posts) {
        this->maxSubPosts = posts;
    }

    void addSubPost(Post *p);

    void removeSubPost(Post *post);

    void deletePost();

    void permDeletePost();

    void addSubscriber(const unsigned long &);

    bool removeSubscriber(const unsigned long &);

    unsigned int postsInTheLastAmountOfTime(const unsigned long &);

    void sortPosts();

    std::string toJSON() const;

};

class PostBuilder {

private:
    unsigned long postID, postingUser, parentPost, postDate;

    std::string postTitle, postText;

    std::set<unsigned long> *subscribers, *subPostsTemp;

    std::vector<Post *> *subPosts;

public:
    PostBuilder(const unsigned long &postID, const unsigned long &postingUser, const unsigned long &parentPost,
                const unsigned long &postDate,
                std::string postTitle, std::string postText, std::set<unsigned long> *subscribers,
                std::set<unsigned long> *subPostsTemp)
            : postID(postID), postingUser(postingUser), parentPost(parentPost), subscribers(subscribers),
              subPostsTemp(subPostsTemp), postDate(postDate) {

        this->subPosts = new std::vector<Post *>();
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

    Post *build(std::list<PostBuilder *> *posts) {

        for (unsigned long postID : *subPostsTemp) {

            for (auto subPost : *posts) {
                if (subPost->getPostID() == postID) {

                    addSubPost(subPost->build(posts));

                    delete subPost;

                    break;
                }
            }
        }

        posts->remove_if([this](PostBuilder *post) -> bool {
            return post->getPostID() == this->getPostID() ||
                   this->getSubPosts()->find(post->getPostID()) != this->subPostsTemp->end();
        });

        Post *p = new Post(parentPost, postingUser, postID, postDate, postTitle, postText, subscribers, subPosts);

        return p;
    }

};
