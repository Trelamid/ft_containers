//
// Created by Prime_Games_2 on 22.05.2022.
//

#ifndef FT_CONTAINERS_MAP_H
#define FT_CONTAINERS_MAP_H

namespace ft {
    template<typename T, typename R>
    class map {
    public:
        map();
        map(map &map1);
        ~map();
        class iterator{

        };
        iterator begin();

    protected:
    private:
        T *first;
        R *second;
    };

    template<typename T, typename R>
    map<T, R>::map() {

    }

    template<typename T, typename R>
    map<T, R>::~map() {

    }

    template<typename T, typename R>
    map<T, R>::map(map &map1) {
        *this = map1;
    }
}


#endif //FT_CONTAINERS_MAP_H
