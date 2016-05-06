/*********************************************************************************
*     File Name           :     Person.cpp
*     Created By          :     edwardzhe
*     Creation Date       :     [2016-04-30 20:50]
*     Last Modified       :     [2016-05-03 16:37]
*     Description         :      
**********************************************************************************/
#include "Person.h"
Person::Person(int logid):_logid(logid),_play_count(0) {
        begin_time = std::chrono::steady_clock::now();
        _play_path.push("in_out");
        _play_path.push("B");
        _play_path.push("E");
        _play_path.push("C");
        _play_path.push("D");
        _play_path.push("F");
        _play_path.push("G");
        _play_path.push("H");
        _play_path.push("I");
        _play_path.push("J");
        _play_path.push("A");
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

std::string Person::get_next_play()
{
    std::string temp = _play_path.top();
    _play_path.pop();
    return temp;
}
