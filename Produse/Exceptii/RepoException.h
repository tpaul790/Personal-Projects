//
// Created by Titieni Paul on 24.07.2024.
//

#ifndef PRODUSE_REPOEXCEPTION_H
#define PRODUSE_REPOEXCEPTION_H
#include <string>
#include <utility>

using std::string;

class RepoException {
private:
    string mesaj;
public:
    explicit RepoException(string msg) : mesaj{std::move(msg)} {};

    string get_mesaj() const{
        return mesaj;
    }
};


#endif //PRODUSE_REPOEXCEPTION_H
