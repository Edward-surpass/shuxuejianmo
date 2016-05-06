/*********************************************************************************
*     File Name           :     Person.cpp
*     Created By          :     edwardzhe
*     Creation Date       :     [2016-04-30 20:50]
*     Last Modified       :     [2016-05-02 22:24]
*     Description         :      
**********************************************************************************/
#include "Person.h"
Person::Person(int logid):_logid(logid),_play_count(0) {
        begin_time = std::chrono::steady_clock::now();
        _played_amusement.insert("in_out");
}

Person::~Person()
{
}

void Person::add_play_count()
{
    ++_play_count;
}


std::chrono::steady_clock::time_point Person::get_begin_time()
{
    return begin_time;
}

int Person::get_play_count()
{
    return _play_count;
}

bool Person::is_played(const std::string &amu)
{
    return _played_amusement.count(amu);
}

void Person::insert_played(const std::string &amu)
{
    _played_amusement.insert(amu);
}

void Person::delete_played(const std::string &amu)
{
    _played_amusement.erase(amu);
}
