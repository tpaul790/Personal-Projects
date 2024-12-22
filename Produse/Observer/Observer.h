//
// Created by Titieni Paul on 09.08.2024.
//

#ifndef PRODUSE_OBSERVER_H
#define PRODUSE_OBSERVER_H


class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};


#endif //PRODUSE_OBSERVER_H
