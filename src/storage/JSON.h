//
// Created by nuno on 06-04-2018.
//

#ifndef LABC_JSON_H
#define LABC_JSON_H


#include "StorageManager.h"
#include "../users/User.h"

#include <unordered_map>
#include <json.hpp>

class JSON : public StorageManager {

private:

    std::string userFilePath, postsStoragePath, auxStoragePath;

    std::unordered_map<unsigned long, Post *> posts;

    std::unordered_map<unsigned long, User *> users;

    unsigned long currentPostID, currentUserID;

    bool execute = true;

    std::mutex postLock, userLock;

    void loadPosts();

    void savePosts();

    void loadUsers();

    void saveUsers();

    void loadAux();

    void saveAux();

    Post *loadPost(nlohmann::json j);

    unsigned long nextPostID() {

        return this->currentPostID++;

    };

    unsigned long nextUserID() {

        return this->currentUserID++;
    };

public:
    JSON() : userFilePath("users.json"), postsStoragePath("posts.json"),
             auxStoragePath("aux.json") {

        loadAux();

        loadPosts();
        loadUsers();

        std::thread([this]() -> void {

            while (execute) {
                std::this_thread::sleep_for(std::chrono::seconds(20));

                //std::cout << "Saving all data..." << std::endl;

                this->savePosts();
                this->saveUsers();
                this->saveAux();
            }

        }).detach();

    }

    std::vector<Post *> *getAllPosts() override;

    std::vector<Post *> *getAllPostsFor(const unsigned long &userID) override;

    std::vector<Post *> *getAllPostsWithParent(const unsigned long &parentID) override;

    Post *getPostWithID(const unsigned long &postID) override;

    Post *createPostWithTitle(const std::string &postTitle, const unsigned long &parentPost,
                              const unsigned long &postingUser) override;

    void updatePostText(const unsigned long &postID, const std::string &postText) override;

    void deletePost(const unsigned long &postID) override;

    Post *getPostWithTitle(const std::string &postTitle) override;

    void saveUser(User *user) override;

    void deleteUser(const unsigned long &userID) override;

    User *getUser(const unsigned long &i) override;

    User *getUserByUsername(const std::string &userName) override;

    /**
     * Cria um utilizador com o username e com  o salt dados
     * @param string
     * @param string1
     * @return
     */
    User *createUserWithUserName(const std::string &username, const std::string &salt) override;

    std::vector<User *>* getUsersWithRank(int rank) override;

    std::vector<User *>* getAllUsers() override;

    void updateUserPassword(const unsigned long &i, const std::string &string) override;

    void forceSave() override {

        this->execute = false;

        this->saveAux();
        this->savePosts();
        this->saveUsers();

        std::cout << "Saved" << std::endl;
    }

};


#endif //LABC_JSON_H
