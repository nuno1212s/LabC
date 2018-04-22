//
// Created by nuno on 30-03-2018.
//

#ifndef LABC_MYSQL_H
#define LABC_MYSQL_H

#include <mysql_driver.h>
#include <resultset.h>
#include "StorageManager.h"
#include "../posts/Post.h"

class MySQL : public StorageManager {

private:
    std::string host, userName, password, database;

    int port;

    sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();

    sql::Connection *con;

    void checkCon();

    PostBuilder* instantiateFromResultSet(sql::ResultSet*);

    User *instantiateUserFromResultSet(sql::ResultSet *set);

public:
    MySQL() : host("localhost"), userName("teste"), password("teste"), database("posts"), port(3306) {

        std::cout << "instantiated" << std::endl;

        startConnection();

        createTables();

    }

    ~MySQL() {
        con->close();

        delete con;
    }

    void startConnection() {

        con = driver->connect("tcp://" + host + ":" + std::to_string(port) + "/" + database, userName, password);

    }

    std::vector<Post *> *getAllPosts() override;

    std::vector<Post *> *getAllPostsFor(const unsigned long &userID) override;

    std::vector<Post *> *getAllPostsWithParent(const unsigned long &parentID) override;

    Post *getPostWithID(const unsigned long &postID) override;

    Post *createPostWithTitle(const std::string &postTitle, const unsigned long&, const unsigned long&) override;

    void updatePostText(const unsigned long &postID, const std::string &postText) override;

    void deletePost(const unsigned long &postID) override;

    Post *getPostWithTitle(const std::string &postTitle) override;

    void saveUser(User *user) override;

    void deleteUser(const unsigned long &userID) override;

    User *getUser(const unsigned long &userID) override;

    User *getUserByUsername(const std::string &string) override;

    User *createUserWithUserName(const std::string &userName, const std::string &salt) override;

    void updateUserPassword(const unsigned long &i, const std::string &string) override;

    void createTables();
};

#endif //LABC_MYSQL_H
