//
// Created by nuno on 19-04-2018.
//

#include <iostream>
#include "CommandHandler.h"
#include "../users/UserManager.h"
#include "../users/User.h"
#include "../Main.h"
#include "../posts/Post.h"
#include "../posts/PostManager.h"
#include "../storage/StorageManager.h"
#include "sha.h"
#include "filters.h"
#include "base64.h"

#define EXIT_CODE (-1)

User *activeUser = nullptr;

void initialMenu() {

    const short int LOGIN = 1;

    short int opt = 0;

    std::cout << "Welcome. " << std::endl;

    while (opt != EXIT_CODE) {
        std::cout << LOGIN << ") Login / autenticação" << std::endl;
        std::cout << EXIT_CODE << ") Sair " << std::endl;

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

    std::cout << "Tem a certeza que quer sair? Sem o servidor o cliente não irá funcionar" << std::endl;
    std::cout << EXIT_CODE << ") Sair " << std::endl;
    std::cin >> opt;

    if (opt != EXIT_CODE) {

        initialMenu();

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

            activeUser = user;
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

//    std::cout << digest;

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

            Post *p = Main::getPostManager()->createPost(topicTitle, activeUser->getUserID(), 0);

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

        } else if (opt == STATISTICS) {
            viewStats();
        }

    }

    activeUser = nullptr;

    initialMenu();

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

            std::cout << "You have deleted the user!" << std::endl;

        } else if (opt == CREATE_USER) {

            std::cout << "Insira o username do utilizador" << std::endl;

            std::string userName, password;

            std::cin >> userName;

            std::cout << "Insira a password" << std::endl;

            std::cin >> password;

            User *user = Main::getUserManager()->createUserWithUsername(userName);

            if (user == nullptr) {

                std::cout << "Já existe um utilizador com esse username" << std::endl;

                continue;
            }

            Main::getStorageManager()->updateUserPassword(user->getUserID(),
                                                          getHashedPassword(password, user->getSalt()));

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

void viewStats() {

    const short VIEW_POST = 1;
    const short VIEW_USER = 2;

    std::cout << VIEW_POST << ") Ver estatisticas de posts" << std::endl;
    std::cout << VIEW_USER << ") Ver estatisticas de utilizadores" << std::endl;
    std::cout << "3) Voltar atrás" << std::endl;

    int escolha = 0;

    std::cout << "Faça a sua escolha" << std::endl;
    std::cin >> escolha;

    if (escolha == VIEW_POST) {

        viewPostStats();

    } else if (escolha == VIEW_USER) {

        viewUserStats();

    } else if (escolha == 3) {

        authenticatedMenu();

    }

}

void viewUserStats() {

    const short POSTS_IN_THE_LAST = 1, ALL_TIME = 2;

    std::cout << POSTS_IN_THE_LAST << ") Posts in the last time" << std::endl;
    std::cout << ALL_TIME << ") All time user stats" << std::endl;
    std::cout << EXIT_CODE << ") Sair " << std::endl;

    int escolha = 0;

    std::cin >> escolha;

    if (escolha == POSTS_IN_THE_LAST) {
        viewUserLastPosts();
    } else if (escolha == ALL_TIME) {

        viewUserAllTimeStats();
    } else if (escolha == EXIT_CODE) {
        viewStats();
    }

}

void viewUserAllTimeStats() {

    std::vector<User *> *users = Main::getUserManager()->getAllUsers();

    User *user = requestUser(users, [](User *) -> bool {
        return true;
    });

    if (user == nullptr) {
        viewUserStats();

        delete users;
        return;
    }

    delete users;

    std::cout << user->getUserName() << std::endl;
    std::cout << "Nome:" << user->getName() << std::endl;
    std::cout << "Contact: " << user->getContactInfo() << std::endl;
    std::cout << "Posts criados:" << user->getCreatedPosts()->size() << std::endl;
    std::cout << "Posts subscritos + likes: " << user->getSubscribedTo()->size() << std::endl;

    std::cout << "1) Voltar atrás" << std::endl;
    std::cin.get();

    viewStats();
}

void viewUserLastPosts() {

    std::vector<User *> *users = Main::getUserManager()->getAllUsers();

    User *user = requestUser(users, [](User *) -> bool {
        return true;
    });


    if (user == nullptr) {
        viewUserStats();

        delete users;
        return;
    }

    delete users;

    readTime:

    system("clear");

    std::cout << "1) 30 minutos" << std::endl;

    std::cout << "2) 2 horas" << std::endl;

    std::cout << "3) 12 horas" << std::endl;

    std::cout << "4) 24 horas" << std::endl;

    std::cout << "5) 7 dias" << std::endl;

    std::cout << EXIT_CODE << ") Voltar atras" << std::endl;

    unsigned long time;

    int escolha = 0;

    std::cin >> escolha;

    switch (escolha) {

        case 1:
            time = 1800;
            break;
        case 2:
            time = 7200;
            break;
        case 3:
            time = 43200;
            break;
        case 4:
            time = 86400;
            break;
        case 5:
            time = 604800;
            break;
        default:
            viewStats();
            return;
    }

    std::vector<Post *> *posts = Main::getUserManager()->postsInTheLastTime(user, time);

    if (posts->empty()) {

        std::cout << "Este utilizador não tem posts" << std::endl;

        delete posts;

        goto readTime;

    }

    for (Post *post : *posts) {

        time_t time = post->getPostDate();

        std::cout << post->getPostTitle() << std::endl;
        std::cout << "Data de criação: " << std::asctime(std::localtime(&time)) << std::endl << std::endl;

    }

    std::cout << "1) Voltar atrás" << std::endl;

    std::cin.get();

    delete posts;

    goto readTime;
}

User *requestUser(std::vector<User *> *users, bool(*acceptFunc)(User *)) {

    std::unordered_map<int, User *> usersNumber;

    for (User *user : *users) {

        if (acceptFunc(user)) {

            std::cout << usersNumber.size() << ") " << user->getUserName() << std::endl;

            usersNumber[usersNumber.size()] = user;

        }

    }

    escolhaUser:

    int escolha = 0;

    std::cout << "-1) Voltar atrás" << std::endl;

    std::cin >> escolha;

    if (escolha == -1) {

        return nullptr;

    }

    if (usersNumber.find(escolha) == usersNumber.end()) {
        std::cout << "Esse utilizador não existe" << std::endl;

        goto escolhaUser;
    }

    return usersNumber[escolha];
}

void viewPostStats() {

    const short VIEW_ACTIVE = 1, MOST_USED = 2, POST_STATS = 3, USERS_INTERACTING_WITH = 4;

    std::cout << VIEW_ACTIVE << ") Posts ativos" << std::endl;
    std::cout << MOST_USED << ") Posts mais usados" << std::endl;
    std::cout << POST_STATS << ") Estatitisticas de posts" << std::endl;
    std::cout << USERS_INTERACTING_WITH << ") Utilizadores que interagiram com post" << std::endl;
    std::cout << EXIT_CODE << ") Sair" << std::endl;

    int escolha = 0;

    std::cout << "Escolha uma das opções:" << std::endl;

    std::cin >> escolha;

    if (escolha == VIEW_ACTIVE) {

        activePosts();

    } else if (escolha == MOST_USED) {

        mostUsedPosts();

    } else if (escolha == POST_STATS) {

        postStats();

    } else if (escolha == USERS_INTERACTING_WITH) {
        usersInteractingWithPost();
    } else if (escolha == EXIT_CODE) {

        authenticatedMenu();

    }
}

void usersInteractingWithPost() {

    readTime:

    system("clear");

    std::cout << "1) 30 minutos" << std::endl;

    std::cout << "2) 2 horas" << std::endl;

    std::cout << "3) 12 horas" << std::endl;

    std::cout << "4) 24 horas" << std::endl;

    std::cout << "5) 7 dias" << std::endl;

    std::cout << EXIT_CODE << ") Voltar atras" << std::endl;

    unsigned long time;

    int escolha = 0;

    std::cin >> escolha;

    switch (escolha) {

        case 1:
            time = 1800;
            break;
        case 2:
            time = 7200;
            break;
        case 3:
            time = 43200;
            break;
        case 4:
            time = 86400;
            break;
        case 5:
            time = 604800;
            break;
        default:
            viewStats();
            return;
    }

    std::vector<Post *> *posts = Main::getStorageManager()->getAllPosts();

    Post *p = getPostChoice(posts, [](Post *p) -> bool {
        return true;
    });

    if (p == nullptr) {

        delete posts;

        goto readTime;
    }

    for (Post *post : *(p->getSubPosts())) {

        if (time_t(nullptr) - post->getPostDate() < time) {
            std::cout << post->getPostTitle() << std::endl;

            //Não há necessidade de libertar a memória pois o utilizador está guardado no storage manager
            std::cout << "Criador: " << Main::getUserManager()->getUser(post->getPostingUser())->getName() << std::endl;
        }

    }

    delete posts;

    std::cout << "1) Voltar atrás" << std::endl;
    std::cin.get();

    goto readTime;

}

void activePosts() {

    readTime:

    system("clear");

    std::cout << "1) 30 minutos" << std::endl;

    std::cout << "2) 2 horas" << std::endl;

    std::cout << "3) 12 horas" << std::endl;

    std::cout << "4) 24 horas" << std::endl;

    std::cout << "5) 7 dias" << std::endl;

    std::cout << EXIT_CODE << ") Voltar atras" << std::endl;

    unsigned long time;

    int escolha = 0;

    std::cin >> escolha;

    switch (escolha) {

        case 1:
            time = 1800;
            break;
        case 2:
            time = 7200;
            break;
        case 3:
            time = 43200;
            break;
        case 4:
            time = 86400;
            break;
        case 5:
            time = 604800;
            break;
        default:
            viewStats();
            return;
    }

    std::vector<Post *> *posts = Main::getStorageManager()->getAllPosts();

    Post *p = getPostChoice(posts, [](Post *p) -> bool {
        return true;
    });

    if (p == nullptr) {

        delete posts;

        goto readTime;
    }

    std::unordered_map<Post *, int> postsAtivos;

    for (Post *post : *p->getSubPosts()) {

        unsigned int postsInTheLastTime = post->postsInTheLastAmountOfTime(time);

        if (postsInTheLastTime > 0) {

            postsAtivos.emplace(post, postsInTheLastTime);

        }

    }

    std::for_each(postsAtivos.begin(), postsAtivos.end(), [](std::pair<Post *, int> pair) -> void {

        std::cout << pair.first->getPostTitle() << std::endl;
        std::cout << "Posts in the last specified time: " << pair.second << std::endl;
        std::cout << std::endl;
    });

    std::cout << "1) Voltar atrás" << std::endl;

    delete posts;

    goto readTime;

}

void postStats() {

    system("clear");

    std::vector<Post *> *posts = Main::getStorageManager()->getAllPosts();

    Post *p = getPostChoice(posts, [](Post *p) -> bool {
        return true;
    });

    std::cout << "Post:" << std::endl << p->getPostTitle() << std::endl << p->getPostText() << std::endl;

    time_t time = p->getPostDate();

    std::cout << "Data de criação:" << std::asctime(std::localtime(&time)) << std::endl;
    std::cout << "Sub-comentários: " << p->getSubPosts()->size() << std::endl;
    std::cout << "Likes: " << p->getSubscribers()->size() << std::endl;

    std::cout << "1) Voltar atrás" << std::endl;
    std::cin.get();

    delete posts;

    viewStats();
}

void mostUsedPosts() {

    readTime:

    system("clear");

    std::cout << "1) 30 minutos" << std::endl;

    std::cout << "2) 2 horas" << std::endl;

    std::cout << "3) 12 horas" << std::endl;

    std::cout << "4) 24 horas" << std::endl;

    std::cout << "5) 7 dias" << std::endl;

    std::cout << EXIT_CODE << ") Voltar atras" << std::endl;

    unsigned long time;

    int escolha = 0;

    std::cin >> escolha;

    switch (escolha) {

        case 1:
            time = 1800;
            break;
        case 2:
            time = 7200;
            break;
        case 3:
            time = 43200;
            break;
        case 4:
            time = 86400;
            break;
        case 5:
            time = 604800;
            break;
        default:
            viewStats();
            return;
    }

    std::vector<Post *> *posts = Main::getPostManager()->getMostActiveTopics(10, time);

    for (Post *post : *posts) {

        std::cout << post->getPostTitle() << std::endl;
        std::cout << "Posts recentes: " << post->postsInTheLastAmountOfTime(time) << std::endl;

    }

    delete posts;

    std::cout << "1) Voltar atrás" << std::endl;
    std::cin.get();

    goto readTime;
}


Post *getPostChoice(std::vector<Post *> *postData, bool (*acceptMethod)(Post *p)) {

    std::cout << "Posts: " << std::endl;

    std::unordered_map<int, Post *> topicos;

    int current = 0;

    for (Post *post : *postData) {
        if (acceptMethod(post)) {

            std::cout << current << ") " << post->getPostTitle() << std::endl;

            topicos[current++] = post;

        }
    }

    explorarTopico:

    std::cout << "-1) Explorar topico" << std::endl;
    std::cout << "-2) Voltar atrás" << std::endl;

    std::cin >> current;

    if (current == -1) {

        escolherTopicoExplorar:

        std::cout << "Escolha o topico" << std::endl;
        std::cin >> current;

        if (topicos.find(current) == topicos.end()) {

            std::cout << "Esse topico não existe" << std::endl;

            goto escolherTopicoExplorar;
        }

        Post *toReturn = getPostChoice(topicos[current]->getSubPosts(), acceptMethod);

        //Voltar a esta pagina caso a escolha da ultima tenha sido voltar atrás
        if (toReturn == nullptr) {
            toReturn = getPostChoice(postData, acceptMethod);
        }

        return toReturn;
    } else if (current == -2) {

        return nullptr;

    }

    if (topicos.find(current) == topicos.end()) {

        std::cout << "Esse topico não existe" << std::endl;

        goto explorarTopico;
    }

    return topicos[current];
}