//
// Created by nuno on 27-03-2018.
//

#ifndef LABC_POSTMANAGER_H
#define LABC_POSTMANAGER_H

#include <vector>
#include <iostream>

//Forward declaration of Post
class Post;

class PostManager {

public:

    Post* getPost(const unsigned long &postID);

    /**
     * Loads all the posts and the corresponding subposts
     * @param postID
     * @return
     */
    Post* loadPost(const unsigned long &postID);

    Post* createPost(const std::string& postTitle, const unsigned long& userID, const unsigned long& parentPost);

    std::vector<Post*>* loadFeedForUser(const unsigned long &userID);

    std::vector<Post*>* loadPostsOfUser(const unsigned long &userID);

};

#endif //LABC_POSTMANAGER_H
