//
// Created by nuno on 30-03-2018.
//

#include "RestHandler.h"
#include "../storage/StorageManager.h"
#include "../posts/PostManager.h"
#include "../posts/Post.h"
#include "../users/UserManager.h"
#include "../users/User.h"
#include "../Main.h"
#include "nlohmann/json.hpp"

using namespace Pistache;
using namespace nlohmann;

void RestHandler::onRequest(const Pistache::Http::Request &request, Pistache::Http::ResponseWriter response) {

    if (request.method() == Http::Method::Get) {

        const Http::Uri::Query &query = request.query();

        if (query.has("userName")) {

            User *user = Main::getUserManager()->getUser(query.get("UserName").getOrElse(""));

            if (user == nullptr) {
                response.send(Http::Code::Not_Found);
            } else {
                response.send(Http::Code::Ok, user->toJSON());
            }

        } else if (query.has("posts")) {

            unsigned long userID = 0;

            if (!query.has("userID")) {

                userID = strtoul(query.get("userID").getOrElse("0").c_str(), 0, 10);
            }

            std::vector<Post *> *posts = Main::getPostManager()->loadFeedForUser(userID);

            json j = json::array();

            for (auto post : *posts) {
                j.push_back(post->toJSON());

                delete post;
            }

            delete posts;

            response.send(Http::Code::Ok, j.dump(4));

        } else {

            response.send(Http::Code::Bad_Request, "Please provide valid information");

        }

    } else if (request.method() == Http::Method::Post) {

        json j = json::parse(request.body());

        if (request.query().has("auth")) {

            std::string password = j["Password"];
            unsigned long userID = j["UserID"];

            User *user = Main::getUserManager()->getUser(userID);

            if (user->authenticate(password)) {

                response.send(Http::Code::Ok, Main::getUserManager()->generateAccessKey(userID));

            } else {
                response.send(Http::Code::Ok, "PASSWORD_FAILED");
            }

            //Cannot free user, stored in UserManager
            //delete user;

        } else if (request.query().has("create")) {

            std::string userName = j["userName"];

            User *user = Main::getUserManager()->createUserWithUsername(userName);

            response.send(Http::Code::Ok, user->toJSON());

            //Cannot free user, stored in UserManager
            //delete user;

        } else if (request.query().has("updatePassword")) {

            std::string oldPassword = j["OldPassword"];
            std::string hashedPassword = j["Password"];
            unsigned long userID = j["UserID"];

            User *user = Main::getUserManager()->getUser(userID);

            if (user == nullptr) {
                response.send(Http::Code::Bad_Request, "User does not exist");
                return;
            }

            if (user->authenticate(oldPassword)) {

                Main::getStorageManager()->updateUserPassword(userID, hashedPassword);
                response.send(Http::Code::Ok, "Password updated");

            } else {

                response.send(Http::Code::Bad_Request, "Old password is wrong");

            }

            //delete user;

        } else if (request.query().has("createPost")) {

            Post *post = Main::getPostManager()->createPost(j["PostTitle"], j["UserID"], j["ParentPost"]);

            if (post == nullptr) {

                response.send(Http::Code::Bad_Request, "A post with that title already exists");

            } else {

                response.send(Http::Code::Ok, "Post created");

            }

        } else if (request.query().has("updatePost")) {

            std::string authKey = j["AuthKey"];

            const unsigned long userID = j["UserID"];

            if (Main::getUserManager()->isAuthenticated(userID, authKey)) {

                Main::getStorageManager()->updatePostText(j["PostID"], j["PostText"]);

            }

        } else if (request.query().has("deletePost")) {

            std::string authKey = j["AuthKey"];

            const unsigned long userID = j["UserID"];

            if (Main::getUserManager()->isAuthenticated(userID, authKey)) {

                Main::getStorageManager()->deletePost(j["PostID"]);

            }

        }
    }

}