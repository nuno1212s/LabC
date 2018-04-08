//
// Created by nuno on 29-03-2018.
//

#include <memory>
#include "posts/PostManager.h"
#include "storage/StorageManager.h"
#include "users/UserManager.h"
#include "rest/RestHandler.h"
#include "Main.h"
#include "storage/MySQL.h"

int main() {

    Main::instantiateStorage<MySQL>();

    std::shared_ptr<RestHandler> pointer = std::make_shared<RestHandler>();

    std::thread restThread(&RestHandler::start, pointer);

    restThread.detach();

    std::cout << "Hello" << std::endl;

    std::cin.get();
}

PostManager *Main::postManager = nullptr;

StorageManager *Main::storageManager = nullptr;

UserManager *Main::userManager = nullptr;

PostManager *Main::getPostManager() {

    if (postManager == nullptr) {
        postManager = new PostManager();
    }

    return postManager;
}

UserManager *Main::getUserManager() {

    if (userManager == nullptr) {
        userManager = new UserManager();
    }

    return userManager;
}

StorageManager *Main::getStorageManager() {
    return storageManager;
}

Main::~Main() {
    delete postManager;

    delete userManager;

    delete storageManager;
}