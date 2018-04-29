//
// Created by nuno on 19-04-2018.
//

#include <iostream>
#include <string>
#include "CommandHandler.h"
#include "../users/UserManager.h"
#include "../users/User.h"
#include "../Main.h"
#include "sha.h"
#include "filters.h"
#include "base64.h"
#include "../posts/Post.h"
#include "../posts/PostManager.h"
#include "../storage/StorageManager.h"

#define EXIT_CODE (-1)

void initialMenu() {

    const short int LOGIN = 1;

    short int opt = 0;

    std::cout << "Welcome. " << std::endl;

    while (opt != EXIT_CODE) {
        std::cout << LOGIN << ") Login / autenticação" << std::endl;

        std::cin >> opt;

        if (opt == LOGIN) {

            //Verificar se a autenticação foi bem sucedida
            if (readAuth()) {

                //Mostrar o menu autenticado
                authenticatedMenu();

                break;
            }

        }

    }

}


bool readAuth() {
    std::string userName, password;

    //Ler o username e a password
    std::cout << "Username: ";
    std::cin >> userName;

    std::cout << "Password: ";
    std::cin >> password;

    User *user;

    if ((user = Main::getUserManager()->getUser(userName)) != nullptr) {


        if (user->authenticate(getHashedPassword(password, user->getSalt()))) {

            if (user->getRank() != UserRank::ADMIN) {

                std::cout << "This user does not have the permissions required to use the server" << std::endl;

                return false;
            }

            return true;
        } else {
            std::cout << "Wrong password" << std::endl;
        }


        //delete user;
    }

    return false;
}

std::string getHashedPassword(const std::string &password, const std::string &salt) {
    std::string digest;

    CryptoPP::SHA256 hash;

    //Fazer hash da  password juntamente com o salt para armazenamento seguro
    CryptoPP::StringSource foo(password + salt, true,
                               new CryptoPP::HashFilter(hash,
                                                        new CryptoPP::Base64Encoder(
                                                                new CryptoPP::StringSink(digest))));

    std::cout << digest;

    return digest;
}

void authenticatedMenu() {

    const short int CREATE_TOPIC = 1, MANAGE_TOPICS = 2, STATISTICS = 3;

    short int opt = 0;

    while (opt != EXIT_CODE) {

        std::cout << CREATE_TOPIC << ") - Criar novo topico" << std::endl;

        std::cout << MANAGE_TOPICS << ") - Gerir topicos / utilizadores" << std::endl;

        std::cout << STATISTICS << ") - Estatisticas " << std::endl;

        std::cout << EXIT_CODE << ") - Sair" << std::endl;

        std::cin >> opt;

        if (opt == CREATE_TOPIC) {

            std::string topicTitle, description;

            std::cout << "Insert topic title" << std::endl;

            std::getline(std::cin, topicTitle);

            std::getline(std::cin, topicTitle);

            std::cout << "Insert topic description" << std::endl;

            std::getline(std::cin, description);

            Post *p = Main::getPostManager()->createPost(topicTitle, 0, 0);

            if (p == nullptr) {
                std::cout << "A topic with that name already exists!" << std::endl;
                continue;
            }

            p->setPostText(description);

            //Does not need to deallocate memory
            //delete p;

            std::cout << "Topic has been created" << std::endl;

        } else if (opt == MANAGE_TOPICS) {

            management();

        }

    }

}

void management() {

    const short int MANAGE_TOPICS = 1, MANAGE_USERS = 2;

    short int opt = 0;

    while (opt != EXIT_CODE) {

        std::cout << MANAGE_TOPICS << ") - Gerir topicos" << std::endl;

        std::cout << MANAGE_USERS << ") - Gerir utilizadores" << std::endl;

        std::cout << EXIT_CODE << ") - Sair" << std::endl;

        std::cin >> opt;

        if (opt == MANAGE_TOPICS) {
            manageTopics();
        } else if (opt == MANAGE_USERS) {
            manageUsers();
        }
    }

}

void manageTopics() {

    const short int SHOW_TOPICS = 1, DELETE_TOPIC = 2, ALTER_TOPIC = 3;

    short int opt = 0;

    while (opt != EXIT_CODE) {

        std::cout << SHOW_TOPICS << ") - Mostrar os topicos existentes" << std::endl;

        std::cout << DELETE_TOPIC << ") - Apagar um topico existente" << std::endl;

        std::cout << ALTER_TOPIC << ") - Alterar a descrição de um topico" << std::endl;

        std::cout << EXIT_CODE << ") - Sair" << std::endl;

        std::cin >> opt;

        if (opt == SHOW_TOPICS) {

            auto topics = Main::getPostManager()->getTopics();

            std::cout << "------------------------------------------------" << std::endl;

            for (auto post : *topics) {

                std::cout << post->getPostTitle() << std::endl;

                std::cout << post->getPostText() << std::endl;

                std::cout << "------------------------------------------------" << std::endl;

            }

            delete topics;

        } else if (opt == DELETE_TOPIC) {

            std::string topicTitle;

            std::cout << "Insert the topic title" << std::endl;

            std::getline(std::cin, topicTitle);

            std::getline(std::cin, topicTitle);

            Post *post = Main::getPostManager()->getPostWithTitle(topicTitle);

            if (post == nullptr) {

                std::cout << "Nao existe nenhum topico com esse titulo" << std::endl;

            } else if (post->getParentPost() != 0) {

                std::cout << "That post is not a topic!";

            } else {

                Main::getPostManager()->deletePost(post->getPostID());

                delete post;

            }

        } else if (opt == ALTER_TOPIC) {

            std::string topicTitle;

            std::cout << "Insert the topic title" << std::endl;

            std::getline(std::cin, topicTitle);

            std::getline(std::cin, topicTitle);

            Post *post = Main::getPostManager()->getPostWithTitle(topicTitle);

            if (post == nullptr) {

                std::cout << "Nao existe nenhum topico com esse titulo" << std::endl;

            } else if (post->getParentPost() != 0) {

                std::cout << "Esse post não é um topico" << std::endl;

            } else {

                std::string newDesc;

                std::cout << "Insira a nova descrição" << std::endl;

                std::getline(std::cin, newDesc);

                post->setPostText(newDesc);

                std::cout << "O topico foi atualizado" << std::endl;
            }

        }

    }

}

void manageUsers() {

    const short int ACCEPT_USERS = 1, DELETE_USERS = 2, CREATE_USER = 3, MODIFY_USER = 4;

    short int opt = 0;

    while (opt != EXIT_CODE) {

        std::cout << ACCEPT_USERS << ") - Aceita utilizadores" << std::endl;
        std::cout << DELETE_USERS << ") - Apagar utilizadores" << std::endl;
        std::cout << CREATE_USER << ") - Criar utilizador" << std::endl;
        std::cout << MODIFY_USER << ") - Modificar as permissões de um utilizador" << std::endl;
        std::cout << EXIT_CODE << ") Sair " << std::endl;

        std::cin >> opt;

        if (opt == ACCEPT_USERS) {

            std::cout << "Os utilizadores pendentes são:" << std::endl;

            auto users = Main::getUserManager()->getPendingUsers();

            if (users->empty()) {

                std::cout << "Não há utilizadores pendentes." << std::endl;

                continue;

            } else {
                for (User *user : *users) {

                    std::cout << user->getUserName() << " . UserID: " << user->getUserID() << std::endl;

                    //Can't delete users as the user is stored in the JSON storage method
                    //TODO: Make JSON return copies of the object instead of the object itself so it can be safely freed
                    //delete user;
                }
            }

            delete users;

            std::cout << "Insira o utilizador" << std::endl;

            std::string userName;

            std::cin >> userName;

            User *user = Main::getUserManager()->getUser(userName);

            if (user == nullptr) {

                std::cout << "Não existe nenhum utilizador com esse nome" << std::endl;

                continue;
            }

            user->setRank(UserRank::USER);

            std::cout << "User has been accepted" << std::endl;

        } else if (opt == DELETE_USERS) {

            std::cout << "Insira o username do utilizador que deseja apagar " << std::endl;

            std::string userName;

            std::cin >> userName;

            User *user = Main::getUserManager()->getUser(userName);

            if (user == nullptr) {
                std::cout << "There is no user with that name" << std::endl;

                continue;
            }

            Main::getUserManager()->deleteUser(user->getUserID());

            delete user;

            std::cout << "You have deleted the user!" << std::endl;

        } else if (opt == CREATE_USER) {

            std::cout << "Insira o username do utilizador" << std::endl;

            std::string userName, password;

            std::cin >> userName;

            std::cout << "Insira a password" << std::endl;

            std::cin >> password;

            User *user = Main::getUserManager()->createUserWithUsername(userName);

            if (user == nullptr) {

                std::cout << "Já existe um utilizador com esse username"<<std::endl;

                continue;
            }

            Main::getStorageManager()->updateUserPassword(user->getUserID(), getHashedPassword(password, user->getSalt()));

            user->setRank(UserRank::PENDING);

            std::cout << "Utilizador criado" << std::endl;

            //delete user
        } else if (opt == MODIFY_USER) {

            std::cout << "Insira o username do utilizador!" << std::endl;

            std::string userName;

            std::cin >> userName;

            //Procurar pelo utilizador com o username dado
            User *user = Main::getUserManager()->getUser(userName);

            std::cout << "Insira o novo grupo" << std::endl;

            //Inserir o grupo para que deseja mudar o utilizador
            std::cout << "0 - Admin" << std::endl << "1 - Moderador" << std::endl << "2 - Utilizador" << std::endl
                      << "3 - Pendente" << std::endl;

            unsigned short int rank;

            std::cin >> rank;

            //Verificar se o rank está dentro dos limites aceitaveis
            if (rank < 0 || rank > 3) {

                std::cout << "O grupo não foi reconhecido!";

                continue;
            }

            user->setRank(static_cast<UserRank> (rank));

            std::cout << "O utilizador foi modificado com sucesso!" << std::endl;

            //delete user

        }

    }

}

void viewStatistics() {

    const short int VIEW_POST = 1;


}