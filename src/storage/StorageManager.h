//
// Created by nuno on 27-03-2018.
//

#ifndef LABC_MYSQLHANDLER_H
#define LABC_MYSQLHANDLER_H

#include <vector>
#include <iostream>

class User;
class Post;

class StorageManager {

public:

    StorageManager() = default;

    /**
     * Obtem todos os posts
     * @return
     */
    virtual std::vector<Post *> *getAllPosts() = 0;

    /**
     * Obtem todos os posts para um utilizador
     * @param userID
     * @return
     */
    virtual std::vector<Post *> *getAllPostsFor(const unsigned long &userID) = 0;

    /**
     * Obtem todos os posts cujo pai é o dado
     * @param postID
     * @return
     */
    virtual std::vector<Post *> *getAllPostsWithParent(const unsigned long &postID) = 0;

    /**
     * Obtem o post com o ID
     * @param postID
     * @return
     */
    virtual Post *getPostWithID(const unsigned long &postID) = 0;

    /**
     * Cria um post e guarda-o com todos os dados dados
     * @param postTitle
     * @param parentPost
     * @param postingUser
     * @return
     */
    virtual Post *createPostWithTitle(const std::string &postTitle, const unsigned long &parentPost, const unsigned long &postingUser) = 0;

    /**
     * Faz update ao texto de um post
     * @param postID
     * @param postText
     */
    virtual void updatePostText(const unsigned long &postID, const std::string &postText) = 0;

    /**
     * Apaga um post com o ID dado
     * @param postID
     */
    virtual void deletePost(const unsigned long &postID) = 0;

    /**
     * Obtem o post com o titulo dado
     * @param postTitle
     * @return
     */
    virtual Post *getPostWithTitle(const std::string &postTitle) = 0;

    /**
     * Salva um utilizador
     */
    virtual void saveUser(User *) = 0;

    /**
     * Apaga um utilizador com o ID dado
     * @param userID
     */
    virtual void deleteUser(const unsigned long &userID) = 0;

    /**
     * Obtem um utilizador com o ID dado
     * @return
     */
    virtual User *getUser(const unsigned long &) = 0;

    /**
     * Obtem um utilizador com o username dado
     * @return
     */
    virtual User *getUserByUsername(const std::string &) = 0;

    /**
     * Cria um utilizador com os dados dados
     * @return
     */
    virtual User *createUserWithUserName(const std::string &, const std::string &) = 0;

    /**
     * Obtem todos os utilizadores com um dado rank
     * @param rank
     * @return
     */
    virtual std::vector<User *>* getUsersWithRank(int rank) = 0;

    /**
     * Obtem todos os utilizadores
     * @return
     */
    virtual std::vector<User *>* getAllUsers() = 0;

    /**
     * Modifica a password de um utilizador
     */
    virtual void updateUserPassword(const unsigned long &, const std::string&) = 0;

    /**
     * Força salvar todos os utilizadores e posts
     */
    virtual void forceSave() = 0;

};


#endif //LABC_MYSQLHANDLER_H
