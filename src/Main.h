//
// Created by nuno on 29-03-2018.
//

#ifndef LABC_MAIN_H
#define LABC_MAIN_H

class PostManager;

class StorageManager;

class UserManager;

class Main {

private:
    static PostManager *postManager;

    static StorageManager *storageManager;

    static UserManager *userManager;

public:

    static PostManager *getPostManager();

    static StorageManager *getStorageManager();

    static UserManager *getUserManager();

    /**
     * Allow only for subclasses of StorageManager to be passed
     * @tparam T
     */
    template <typename T, typename std::enable_if<std::is_base_of<StorageManager, T>::value>::type* = nullptr>
    static void instantiateStorage() {

        storageManager = new T();

    };

    ~Main();

};

#endif //LABC_MAIN_H
