//
// Created by nuno on 19-04-2018.
//

#ifndef LABC_COMMANDHANDLER_H
#define LABC_COMMANDHANDLER_H

#include <vector>
#include "../users/User.h"

class Post;

/**
 * Menu inicial
 */
void initialMenu();

/**
 * Ler autenticação
 * @return
 */
bool readAuth();

/**
 * Menu de autenticação
 */
void authenticatedMenu();

/**
 * Gerir topicos e utilizadores
 */
void management();

/**
 * Gerir topicos
 */
void manageTopics();

/**
 * Gerir utilizadores
 */
void manageUsers();

/**
 * Ver estatisticas
 */
void viewStats();

/**
 * Ver estatisticas dos posts
 */
void viewPostStats();

/**
 * Ver posts ativos
 */
void activePosts();

/**
 * Ver estatisticas dos posts
 */
void postStats();

/**
 * Lista os posts mais usados
 */
void mostUsedPosts();

/**
 * Lista todos os utilizadores que interagiram com o post
 */
void usersInteractingWithPost();

/**
 * Ver estatisticas dos utilizador
 */
void viewUserStats();

/**
 * Ver os ultimos posts de um utilizador
 */
void viewUserLastPosts();

/**
 * Ver estatisticas de todos os tempos dos utilizadores
 */
void viewUserAllTimeStats();

/**
 * Pede o utilizador ao utilizador
 * @return
 */
User *requestUser(std::vector<User *>*, bool (*)(User *));

Post *getPostChoice(std::vector<Post *>*, bool (*)(Post *));

std::string getHashedPassword(const std::string &, const std::string &);

#endif //LABC_COMMANDHANDLER_H
