/*********************************************************************************
*     File Name           :     Clock.cpp
*     Created By          :     edwardzhe
*     Creation Date       :     [2016-05-02 12:36]
*     Last Modified       :     [2016-05-02 13:22]
*     Description         :      
**********************************************************************************/
#include "BeginClock.h"

BeginClock* BeginClock::get_instance(){
    static BeginClock * instance;
    if (instance == NULL)
    {
        std::chrono::steady_clock::time_point begin_time = std::chrono::steady_clock::now();
        instance = new BeginClock(begin_time);
    }
    return instance;
}
BeginClock::BeginClock(const std::chrono::steady_clock::time_point &bt):begin_time(bt)
{}

std::chrono::steady_clock::time_point BeginClock::get_begin_time(){
    return begin_time;
}
