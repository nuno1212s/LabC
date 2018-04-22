//
// Created by nuno on 30-03-2018.
//

#include <cppconn/prepared_statement.h>
#include "nlohmann/json.hpp"
#include "../users/User.h"
#include <list>
#include <set>
#include "MySQL.h"
#include "../Main.h"

using namespace sql;
using namespace nlohmann;

static unsigned long getLastID(Connection *);

void MySQL::checkCon() {
    if (con->isValid()) {
        con->reconnect();
    }
}

void MySQL::createTables() {

    Statement *s = con->createStatement();

    std::string table1 = "CREATE TABLE IF NOT EXISTS users(USERID BIGINT UNSIGNED PRIMARY KEY AUTO_INCREMENT"
            ", USERNAME varchar(25) NOT NULL DEFAULT ''"
            ", PASSWORD char(64) NOT NULL, SALT char(16) NOT NULL"
            ", SUBSCRIBEDTO TEXT, CREATEDPOSTS TEXT"
            ", RANK TINYINT UNSIGNED DEFAULT 1, UNIQUE(USERNAME))";

    s->execute(table1);

    std::string table2 = "CREATE TABLE IF NOT EXISTS posts(POSTID BIGINT UNSIGNED PRIMARY KEY AUTO_INCREMENT"
            ", PARENT BIGINT UNSIGNED DEFAULT 0, POSTINGUSER BIGINT UNSIGNED"
            ", POSTTITLE varchar(500) NOT NULL DEFAULT '', POSTTEXT TEXT NOT NULL DEFAULT ''"
            ", SUBSCRIBEDUSERS TEXT NOT NULL DEFAULT '', SUBPOSTS TEXT NOT NULL DEFAULT '')";

    s->execute(table2);

    delete s;
}

std::vector<Post *> *MySQL::getAllPosts() {

    checkCon();

    PreparedStatement *s = con->prepareStatement("SELECT * FROM posts");

    ResultSet *result = s->executeQuery();

    std::list<PostBuilder *> posts;

    while (result->next()) {
        posts.push_back(instantiateFromResultSet(result));
    }

    posts.sort([](const PostBuilder *p1, const PostBuilder *p2) -> bool {

        return p1->getPostID() > p2->getPostID();

    });

//    posts->reverse();

    auto finalPosts = new std::vector<Post *>(posts.size());

    for (std::list<PostBuilder *>::iterator it = posts.begin(); it != posts.end(); ++it) {

        finalPosts->push_back((*it)->build(&posts));

        delete (*it);

    }

    delete result;
    delete s;

    return finalPosts;
}

std::vector<Post *> *MySQL::getAllPostsFor(const unsigned long &userID) {
    checkCon();

}

std::vector<Post *> *MySQL::getAllPostsWithParent(const unsigned long &parentID) {

    checkCon();

    PreparedStatement *s = con->prepareStatement("SELECT * FROM posts WHERE PARENT=?");

    s->setUInt64(1, parentID);

    ResultSet *set = s->executeQuery();

    std::vector<Post*>* posts = new std::vector<Post*>();

    std::list<PostBuilder*> disposable(0);

    while (set->next()) {

    }

    //TODO: load the posts

    delete set;
    delete s;
}

Post *MySQL::getPostWithID(const unsigned long &postID) {

    checkCon();

    PreparedStatement *s = con->prepareStatement("SELECT * FROM posts WHERE POSTID=?");

    ResultSet *result = s->executeQuery();

    std::list<PostBuilder *> builder;

    Post *post = nullptr;

    if (result->next()) {

        PostBuilder *build = instantiateFromResultSet(result);

        post = build->build(&builder);

        delete build;

    }

    return post;
}

Post *MySQL::createPostWithTitle(const std::string &postTitle, const unsigned long &parentPost,
                                 const unsigned long &postingUser) {

    checkCon();

    PreparedStatement *s = con->prepareStatement(
            "INSERT INTO posts(PARENT, POSTINGUSER, POSTTITLE, POSTTEXT, SUBSCRIBEDUSERS, SUBPOSTS) values(?, ?, ?, ?, ?, ?)");

    s->setUInt64(1, parentPost);
    s->setUInt64(2, postingUser);
    s->setString(3, postTitle);
    s->setString(4, "");
    s->setString(5, json::array().dump());
    s->setString(6, json::array().dump());

    s->executeUpdate();

    delete s;

    return new Post(parentPost, postingUser, getLastID(con), postTitle, "", new std::set<unsigned long>(),
                    new std::vector<Post *>());
}

void MySQL::deletePost(const unsigned long &postID) {

    checkCon();

    PreparedStatement *s = con->prepareStatement("DELETE FROM posts WHERE POSTID=?");

    s->setUInt64(1, postID);

    s->executeUpdate();

    delete s;
}

void MySQL::saveUser(User *user) {

    checkCon();

    PreparedStatement *s = con->prepareStatement(
            "INSERT INTO users(USERNAME, PASSWORD, SALT, SUBSCRIBEDTO, CREATEDPOSTS, RANK) values(?, ?, ?, ?, ?, ?) ON DUPLICATE KEY UPDATE "
            "SUBSCRIBEDTO=?, CREATEDPOSTS=?, RANK=?");

    s->setString(1, user->getUserName());

    //password is already hashed, so it can be stored
    //the server never gets access to the unhashed un-salted password
    s->setString(2, user->getPassword());

    s->setString(3, user->getSalt());

    auto createdPosts = user->getCreatedPosts(), subscribedPosts = user->getSubscribedTo();

    json subscribedJSON = json::array(), createdJSON = json::array();

    for (unsigned long subscribedPost : *subscribedPosts) {
        subscribedJSON.push_back(subscribedPost);
    }

    for (unsigned long createdPost : *createdPosts) {
        createdJSON.push_back(createdPost);
    }

    auto subscribed = subscribedJSON.dump(), created = createdJSON.dump();

    s->setString(4, subscribed);

    s->setString(5, created);

    s->setUInt(6, user->getRank());

    s->setString(7, subscribed);

    s->setString(8, subscribed);

    s->setUInt(9, user->getRank());

    s->executeUpdate();

    delete s;

}

void MySQL::deleteUser(const unsigned long &userID) {

    checkCon();

    PreparedStatement *s = con->prepareStatement("DELETE FROM users WHERE USERID=?");

    s->setUInt64(1, userID);

    s->execute();

    delete s;

}

User *MySQL::getUser(const unsigned long &userID) {

    checkCon();

    PreparedStatement *s = con->prepareStatement("SELECT * FROM users WHERE USERID=?");

    s->setUInt64(1, userID);

    ResultSet *set = s->executeQuery();

    User *user = nullptr;

    if (set->next()) {
        user = instantiateUserFromResultSet(set);
    }

    delete set;

    delete s;

    return user;
}

User *MySQL::getUserByUsername(const std::string &string) {

    checkCon();

    PreparedStatement *s = con->prepareStatement("SELECT * FROM users WHERE USERNAME=?");

    s->setString(1, string);

    ResultSet *set = s->executeQuery();

    User *user = nullptr;

    if (set->next()) {
        user = instantiateUserFromResultSet(set);
    }

    delete set;

    delete s;

    return user;
}

Post *MySQL::getPostWithTitle(const std::string &postTitle) {

    checkCon();

    PreparedStatement *s = con->prepareStatement("SELECT * FROM posts WHERE LOWER(POSTTITLE)=LOWER(?)");

    s->setString(1, postTitle);

    ResultSet *set = s->executeQuery();

    Post* post = nullptr;

    if (set->next()) {

        std::list<PostBuilder*> posts;

        PostBuilder *postBuilder = instantiateFromResultSet(set);

        post = postBuilder->build(&posts);

        delete postBuilder;
    }

    delete set;

    delete s;

    return post;
}

User *MySQL::createUserWithUserName(const std::string &userName, const std::string &salt) {

    checkCon();

    PreparedStatement *s = con->prepareStatement("INSERT INTO users(USERNAME, PASSWORD, SALT, SUBSCRIBEDTO, CREATEDPOSTS) values(?, '', ?, '[]', '[]')");

    s->setString(1, userName);

    s->setString(2, salt);

    s->executeUpdate();

    delete s;

    return new User(getLastID(con), userName, "", salt, UserRank::USER);
}

User* MySQL::instantiateUserFromResultSet(ResultSet *set) {


    unsigned long userID = set->getUInt64("USERID");

    std::string userName = set->getString("USERNAME"),
            password = set->getString("PASSWORD"),
            salt = set->getString("SALT");

    json subscribed = json::parse(std::string(set->getString("SUBSCRIBEDTO"))),
            created = json::parse(std::string(set->getString("CREATEDPOSTS")));

    unsigned long rank = set->getUInt("RANK");

    auto subscribedPosts = new std::set<unsigned long>(), createdPosts = new std::set<unsigned long>();

    for (unsigned long subscribedPost : subscribed) {
        subscribedPosts->insert(subscribedPost);
    }

    for (unsigned long createdPost : created) {
        createdPosts->insert(createdPost);
    }

    return new User(userID, userName, password, salt, static_cast<UserRank>(rank), subscribedPosts, createdPosts);

}

PostBuilder *MySQL::instantiateFromResultSet(ResultSet *set) {

    unsigned long parentPost = set->getUInt64("PARENT"),
            postID = set->getUInt64("POSTID"),
            postingUser = set->getUInt64("POSTINGUSER");

    std::string postTitle = set->getString("POSTTITLE"), postText = set->getString("POSTTEXT");

    auto subscribedUsers = new std::set<unsigned long>(), subPosts = new std::set<unsigned long>();

    auto subscribedUserList = json::parse(std::string(set->getString("SUBSCRIBEDUSERS"))),
            subPostList = json::parse(std::string(set->getString("SUBPOSTS")));

    if (subscribedUserList.is_array()) {

        for (auto it = subscribedUserList.begin(); it != subscribedUserList.end(); it++) {

            subscribedUsers->insert((unsigned long) *it);

        }

    }

    if (subPostList.is_array()) {

        for (auto it = subPostList.begin(); it != subPostList.end(); it++) {

            subPosts->insert((unsigned long) *it);

        }

    }

    PostBuilder *post = new PostBuilder(parentPost, postingUser, postID, postTitle, postText, subscribedUsers,
                                        subPosts);

    return post;
}

void MySQL::updateUserPassword(const unsigned long &userID, const std::string &password) {

    PreparedStatement *s = con->prepareStatement("UPDATE users SET PASSWORD=? WHERE USERID=?");

    s->setString(1, password);

    s->setUInt64(2, userID);

    s->executeUpdate();

    delete s;
}

void MySQL::updatePostText(const unsigned long &postID, const std::string &postText) {

    PreparedStatement *s = con->prepareStatement("UPDATE posts SET POSTTEXT=? WHERE POSTID=?");

    s->setString(1, postText);

    s->setUInt64(2, postID);

    s->executeUpdate();

    delete s;

}

static unsigned long getLastID(Connection *con) {

    sql::PreparedStatement *lastID = con->prepareStatement("SELECT LAST_INSERT_ID()");

    sql::ResultSet *resultSet = lastID->executeQuery();

    unsigned long requestID = 0;

    if (resultSet->next()) {
        requestID = resultSet->getUInt64(1);
    }

    delete resultSet;

    delete lastID;

    return requestID;
}
