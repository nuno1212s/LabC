//
// Created by nuno on 19-04-2018.
//

#ifndef LABC_COMMANDHANDLER_H
#define LABC_COMMANDHANDLER_H

void initialMenu();

bool readAuth();

void authenticatedMenu();

void management();

void manageTopics();

void manageUsers();

std::string getHashedPassword(const std::string &, const std::string &);

#endif //LABC_COMMANDHANDLER_H
