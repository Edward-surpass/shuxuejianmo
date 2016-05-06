/*********************************************************************************
*     File Name           :     Amusement.h
*     Created By          :     edwardzhe
*     Creation Date       :     [2016-04-30 16:54]
*     Last Modified       :     [2016-05-02 20:34]
*     Description         :      
**********************************************************************************/
#ifndef AMUSEMENT_H
#define AMUSEMENT_H
#include <deque>
#include <queue>
#include <iostream>
#include <chrono>
#include <mutex>
#include <memory>
#include <map>
#include <thread>
#include <random>
#include "Person.h"
typedef std::chrono::milliseconds time_unit;
class Amusement{
    private:
        std::string _name;
        size_t _capacity;
        time_unit _playtime;
        bool _item_is_running;
        std::mutex _items_is_running_mutex;
        std::deque<std::shared_ptr<Person>> _ranks;
        std::queue<std::shared_ptr<Person>> _has_play;
        std::mutex _ranks_mutex;
        std::vector<std::pair<std::shared_ptr<Amusement>, time_unit>> _neighbor;
    public:
        Amusement(const std::string &, const int &, const time_unit &);
        Amusement(const Amusement &) = default;
        void in_out_run();
        void in_out_work();
        void run();
        void work();
        void evacuate();
        int get_capacity();
        int get_ranks_size();
        std::mutex &get_ranks_mutex();
        std::deque<std::shared_ptr<Person>> &get_ranks();
        std::string get_name();
        void push(std::shared_ptr<Person>, time_unit, std::shared_ptr<Amusement> amu);
        void insert_neighbor(const std::pair<std::shared_ptr<Amusement>, time_unit> &);
        ~Amusement();
};
#endif
