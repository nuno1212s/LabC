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

    //std::cout << "Received request" << std::endl;
    //std::cout << request.method() << std::endl;
    //std::cout << request.resource() << std::endl;

    if (request.method() == Http::Method::Get) {

        const Http::Uri::Query &query = request.query();

        if (request.resource() == "/loadUser") {

            //std::cout << "Received a load request" << std::endl;

            if (query.has("username")) {
                User *user = Main::getUserManager()->getUser(query.get("username").getOrElse(""));

                if (user == nullptr) {
                    response.send(Http::Code::Not_Found);
                } else {
                    response.send(Http::Code::Ok, user->toJSON());
                }

            } else if (query.has("userID")) {

                const unsigned long userID = strtoul(query.get("userID").get().c_str(), nullptr, 10);

                User *user = Main::getUserManager()->getUser(userID);

                if (user == nullptr) {
                    response.send(Http::Code::Not_Found);
                } else {
                    response.send(Http::Code::Ok, user->toJSON());
                }

            } else {
                response.send(Http::Code::Bad_Request);
            }

        } else if (request.resource() == "/loadPosts") {

            unsigned long userID = 0;

            if (query.has("userID")) {

                userID = strtoul(query.get("userID").getOrElse("0").c_str(), nullptr, 10);

            }

            std::vector<Post *> *posts = Main::getPostManager()->loadFeedForUser(userID);

            json j = json::array();

            for (auto post : *posts) {
                j.push_back(post->toJSON());

                //delete post;
            }

            delete posts;

            response.send(Http::Code::Ok, j.dump());

        } else if (request.resource() == "/loadUPosts") {

            if (!query.has("userID")) {

                response.send(Http::Code::Bad_Request);

                return;
            }

            const unsigned long userID = strtoul(query.get("userID").getOrElse("0").c_str(), nullptr, 10);

            std::vector<Post *> *posts = Main::getPostManager()->loadUnsubscribedTopicsForUser(userID);

            json j = json::array();

            std::for_each(posts->begin(), posts->end(), [&j](Post *post) -> void {
                j.push_back(post->toJSON());
            });

            delete posts;

            response.send(Http::Code::Ok, j.dump());

        } else if (request.resource() == "/loadActivePosts") {

            if (!query.has("time") || !query.has("amount")) {

                response.send(Http::Code::Bad_Request);

                return;
            }

            const unsigned long time = strtoul(query.get("time").get().c_str(), nullptr, 10);

            const unsigned int amount = (unsigned int) strtoul(query.get("amount").get().c_str(), nullptr, 10);

            std::vector<Post *> *posts = Main::getPostManager()->getMostActiveTopics(amount, time);

            json j = json::array();

            std::for_each(posts->begin(), posts->end(), [&j](Post *p) -> void {
                j.push_back(p->toJSON());
            });

            delete posts;

            response.send(Http::Code::Ok, j.dump());

        } else {

            response.send(Http::Code::Bad_Request, "Please provide valid information");

        }

    } else if (request.method() == Http::Method::Post) {

        json j = json::parse(request.body());

        if (request.resource() == "/auth") {

            std::string password = j["Password"];
            unsigned long userID = j["UserID"];

            User *user = Main::getUserManager()->getUser(userID);

            if (user->authenticate(password)) {

                response.send(Http::Code::Ok, Main::getUserManager()->generateAccessKey(userID));

            } else {
                response.send(Http::Code::Bad_Request, "PASSWORD_FAILED");
            }

            //Cannot free user, stored in UserManager
            //delete user;

        } else if (request.resource() == "/create") {

            std::string userName = j["userName"], contact = j["Contact"], name = j["Name"];
            User *user = Main::getUserManager()->createUserWithUsername(userName);

            if (user == nullptr) {
                response.send(Http::Code::Bad_Request, "Already exists a user with that username");
                return;
            }

            user->setName(name);
            user->setContactInfo(contact);

            response.send(Http::Code::Ok, user->toJSON());

            //Cannot free user, stored in UserManager
            //delete user;

        } else if (request.resource() == "/updateUser") {

            //Atualizar o nome e o contacto de um utilizador

            unsigned long userID = j["UserID"];

            std::string authKey = j["AuthKey"];

            std::string name = j["Name"], contact = j["Contacto"];

            User *user = Main::getUserManager()->getUser(userID);

            if (!Main::getUserManager()->isAuthenticated(userID, authKey)) {

                response.send(Http::Code::Bad_Request, "User auth key not valid");

                return;
            }

            if (user == nullptr) {
                response.send(Http::Code::Bad_Request, "User with ID not found");
                return;
            }

            user->setName(name);
            user->setContactInfo(contact);

        } else if (request.resource() == "/updatePassword") {

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

        } else if (request.resource() == "/createPost") {

            std::string authKey = j["AuthKey"];

            const unsigned long userID = j["UserID"];

            if (Main::getUserManager()->isAuthenticated(userID, authKey)) {

                Post *post = Main::getPostManager()->createPost(j["PostTitle"], userID, j["ParentPost"]);

                post->setPostText(j["PostText"]);

                if (post == nullptr) {

                    response.send(Http::Code::Bad_Request, "A post with that title already exists");

                } else {

                    nlohmann::json j;

                    j["PostID"] = post->getPostID();

                    response.send(Http::Code::Ok, j.dump(4));

                }
            } else {
                response.send(Http::Code::Bad_Request, "Auth key not valid");
            }

        } else if (request.resource() == "/updatePost") {

            std::string authKey = j["AuthKey"];

            const unsigned long userID = j["UserID"];

            if (Main::getUserManager()->isAuthenticated(userID, authKey)) {

                Main::getStorageManager()->updatePostText(j["PostID"], j["PostText"]);

                response.send(Http::Code::Ok);
            } else {
                response.send(Http::Code::Forbidden);
            }

        } else if (request.resource() == "/deletePost") {

            std::string authKey = j["AuthKey"];

            const unsigned long userID = j["UserID"];

            if (Main::getUserManager()->isAuthenticated(userID, authKey)) {

                Main::getStorageManager()->deletePost(j["PostID"]);

                response.send(Http::Code::Ok);
            } else {
                response.send(Http::Code::Forbidden);
            }


        } else if (request.resource() == "/subscribe") {

            std::string authKey = j["AuthKey"];

            const unsigned long userID = j["UserID"], postID = j["PostID"];

            if (Main::getUserManager()->isAuthenticated(userID, authKey)) {

                Main::getPostManager()->subscribeToPost(postID, userID);

                response.send(Http::Code::Ok);
            } else {
                response.send(Http::Code::Forbidden);
            }

        } else if (request.resource() == "/unsubscribe") {

            std::string authKey = j["AuthKey"];

            const unsigned long userID = j["UserID"], postID = j["PostID"];

            if (Main::getUserManager()->isAuthenticated(userID, authKey)) {

                Post *p = Main::getStorageManager()->getPostWithID(postID);

                p->removeSubscriber(userID);

                response.send(Http::Code::Ok);
            } else {
                response.send(Http::Code::Forbidden);
            }

        } else if (request.resource() == "/favourite") {

            std::string authKey = j["AuthKey"];

            const unsigned long userID = j["UserID"], postID = j["PostID"];

            if (Main::getUserManager()->isAuthenticated(userID, authKey)) {

                User *user = Main::getUserManager()->getUser(userID);

                if (user == nullptr) {
                    response.send(Http::Code::Bad_Request);
                    return;
                }

                user->addFavouritePost(postID);

                response.send(Http::Code::Ok);
            } else {
                response.send(Http::Code::Forbidden);
            }

        } else if (request.resource() == "/unfavourite") {
            std::string authKey = j["AuthKey"];

            const unsigned long userID = j["UserID"], postID = j["PostID"];

            if (Main::getUserManager()->isAuthenticated(userID, authKey)) {

                User *user = Main::getUserManager()->getUser(userID);

                if (user == nullptr) {
                    response.send(Http::Code::Bad_Request);
                    return;
                }

                user->removeFavouritePost(postID);

                response.send(Http::Code::Ok);

            } else {
                response.send(Http::Code::Forbidden);
            }

        }
    }

}