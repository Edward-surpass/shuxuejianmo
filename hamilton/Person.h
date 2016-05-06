/*********************************************************************************
*     File Name           :     Person.h
*     Created By          :     edwardzhe
*     Creation Date       :     [2016-04-30 19:21]
*     Last Modified       :     [2016-05-03 16:11]
*     Description         :      
**********************************************************************************/
#ifndef PERSON_H_
#define PERSON_H_
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <set>
#include <stack>
typedef std::chrono::milliseconds time_unit;
static std::mutex _log_mutex;
class Person{
    private:
        int _logid;
        int _play_count;
        std::stack<std::string> _play_path;
        std::chrono::steady_clock::time_point begin_time;
        std::multiset<std::string> _played_amusement;
    public:
        Person(int);
        int get_logid()
        {
            return _logid;
        }
        void add_play_count();
        ~Person();
        std::chrono::steady_clock::time_point get_begin_time();
        int get_play_count();
        bool is_played(const std::string &);
        void insert_played(const std::string &);
        void delete_played(const std::string &);
        std::string get_next_play();
        void print_played_amu()
        {
            for (auto &e : _played_amusement)
            {
                std::cout << std::setw(8) << std::setfill('0') << _logid;
                std::cout << " " << e << std::endl;
            }
        }

};

#endif
