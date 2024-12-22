//
// Created by Titieni Paul on 24.07.2024.
//

#ifndef PRODUSE_SERVICEEXCEPTION_H
#define PRODUSE_SERVICEEXCEPTION_H
#include <string>
#include <utility>

using std::string;

class ServiceException {
private:
    string mesaj;
public:
    explicit ServiceException(string msg) : mesaj{std::move(msg)} {};

    string get_mesaj() const{
        return mesaj;
    }
};


#endif //PRODUSE_SERVICEEXCEPTION_H
