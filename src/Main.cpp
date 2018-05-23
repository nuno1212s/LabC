//
// Created by nuno on 29-03-2018.
//

#include <memory>
#include <csignal>
#include "posts/PostManager.h"
#include "storage/StorageManager.h"
#include "users/UserManager.h"
#include "rest/RestHandler.h"
#include "Main.h"
#include "storage/JSON.h"
#include "commandhandler/CommandHandler.h"

std::shared_ptr<RestHandler> restHandler;

void handleSignal(int sig) {

    std::cout << "Forcing save" << std::endl;

    Main::getStorageManager()->forceSave();

    delete restHandler.get();

    exit(EXIT_SUCCESS);

}

int main() {

    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);

#ifdef SIGBREAK
    signal(SIGBREAK, handleSignal);
#endif

    Main::instantiateStorage<JSON>();

    std::shared_ptr<RestHandler> pointer = std::make_shared<RestHandler>();

    restHandler = pointer;

    std::thread restThread(&RestHandler::start, pointer);

    restThread.detach();

    initialMenu();
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