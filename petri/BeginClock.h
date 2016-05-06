/*********************************************************************************
*     File Name           :     Clock.h
*     Created By          :     edwardzhe
*     Creation Date       :     [2016-05-02 12:33]
*     Last Modified       :     [2016-05-02 13:22]
*     Description         :      
**********************************************************************************/
#ifndef BeginCLOCK_H_H
#define BeginCLOCK_H_H
#include <chrono>
#include <mutex>
#include <thread>
class BeginClock{
    private:
        std::chrono::steady_clock::time_point begin_time;
        BeginClock(const std::chrono::steady_clock::time_point &);
    public:
        std::chrono::steady_clock::time_point get_begin_time();
        static BeginClock *get_instance();

};
#endif
