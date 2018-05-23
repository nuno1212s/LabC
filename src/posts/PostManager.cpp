//
// Created by nuno on 27-03-2018.
//

#include <iostream>
#include <algorithm>
#include "PostManager.h"
#include "Post.h"
#include "../storage/StorageManager.h"
#include "../users/UserManager.h"
#include "../Main.h"
#include "../users/User.h"

Post *PostManager::getPost(const unsigned long &postID) {

    return Main::getStorageManager()->getPostWithID(postID);

}

Post *PostManager::createPost(const std::string &postTitle, const unsigned long &creatingUser,
                              const unsigned long &parentPost) {

    Post *post = Main::getStorageManager()->getPostWithTitle(postTitle);

    if (post != nullptr) {

        return nullptr;

    }

    User *user = Main::getUserManager()->getUser(creatingUser);

    post = Main::getStorageManager()->createPostWithTitle(postTitle, parentPost, creatingUser);

    if (post->getParentPost() != 0) {

        Post *parentPost = getPost(post->getParentPost());

        parentPost->addSubPost(post);

    }

    user->registerCreatedPost(post->getPostID());

    return post;
};

Post *PostManager::getPostWithTitle(const std::string &title) {

    return Main::getStorageManager()->getPostWithTitle(title);
}

void PostManager::deletePost(const unsigned long &postID) {

    Main::getStorageManager()->deletePost(postID);

}

std::vector<Post *> *PostManager::getTopics() {

    return Main::getStorageManager()->getAllPostsWithParent(0);

}

std::vector<Post *> *PostManager::loadFeedForUser(const unsigned long &userID) {

    std::vector<Post *> *posts = Main::getStorageManager()->getAllPosts(), *postsForUser = new std::vector<Post *>();

    for (auto it = posts->begin(); it != posts->end(); it++) {
        Post *post = *(it);

        //Verifica se o post é um topico
        if (post->isMainPost()) {

            //Verifica se o utilizador está subscrito no post
            if (post->getSubscribers()->find(userID) != post->getSubscribers()->end()) {

                post->sortPosts();

                postsForUser->push_back(post);

            }

        }

    }

    delete posts;

    return postsForUser;
}

std::vector<Post *> *PostManager::loadUnsubscribedTopicsForUser(const unsigned long &userID) {
    std::vector<Post *> *posts = Main::getStorageManager()->getAllPosts(), *postsForUser = new std::vector<Post *>();

    for (auto it = posts->begin(); it != posts->end(); it++) {
        Post *post = *(it);

        //Verifica se o post é um topico
        if (post->isMainPost()) {

            //Verifica se o utilizador está subscrito no post
            if (post->getSubscribers()->find(userID) == post->getSubscribers()->end()) {

                //Adicionar o topico em que o utilizador não está subscrito
                postsForUser->push_back(post);

            }

        }

    }

    delete posts;

    return postsForUser;
}

std::vector<Post *> *PostManager::getMostActiveTopics(unsigned int amount, unsigned long duration) {

    std::vector<Post *> *allPosts = Main::getStorageManager()->getAllPosts(), *postsByOrder = new std::vector<Post *>();

    postsByOrder->reserve(amount);

    //Organizar por ordem de quantos posts nas ultimas 24 hrs tem no topico
    std::sort(allPosts->begin(), allPosts->end(), [duration](Post *p1, Post *p2) -> bool {

        return p1->postsInTheLastAmountOfTime(duration) < p2->postsInTheLastAmountOfTime(duration);

    });

    if (allPosts->size() >= amount) {

        postsByOrder->insert(postsByOrder->begin(), allPosts->begin(), allPosts->begin() + amount);

    } else {

        postsByOrder->insert(postsByOrder->begin(), allPosts->begin(), allPosts->end());

    }

    //Organizar todos os subposts.
    std::for_each(postsByOrder->begin(), postsByOrder->end(), [](Post *post) -> void {
        post->sortPosts();
    });

    delete allPosts;

    return postsByOrder;
}

void PostManager::subscribeToPost(const unsigned long &postID, const unsigned long &userID) {

    Post *post = getPost(postID);

    if (post != nullptr) {

        post->addSubscriber(userID);

        User *user = Main::getUserManager()->getUser(userID);

        user->subscribeTo(postID);

    }

}

std::vector<Post *> *PostManager::getPostsInTheLastTime(Post *post, unsigned long time) {

    auto *postsInTheLast = new std::vector<Post *>();

    std::vector<Post *> *posts = nullptr;

    if (post == nullptr) {

        posts = Main::getStorageManager()->getAllPosts();

    } else {

        posts = post->getSubPosts();

    }

    for (Post *post : *post->getSubPosts()) {

        if (((unsigned long) time_t(nullptr)) - post->getPostDate() < time) {
            postsInTheLast->push_back(post);
        }

    }

    return postsInTheLast;
}

unsigned int PostManager::postsInTheLastTime(Post *post, unsigned long time) {

    std::vector<Post *> *posts = nullptr;

    if (post == nullptr) {

        posts = Main::getStorageManager()->getAllPosts();

    } else {
        posts = post->getSubPosts();
    }

    unsigned int postsIn = 0;

    for (Post *post : *posts) {

        if (time_t(nullptr) - post->getPostDate() < time) {
            postsIn++;

            postsIn += postsInTheLastTime(post, time);
        }
        //Se o post não pertence aos posts das ultimas X hrs então todos os posts que vêm por baixo desse também não vão pertence

    }

    return postsIn;
}

