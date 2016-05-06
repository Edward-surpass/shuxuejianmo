/*********************************************************************************
*     File Name           :     main.cpp
*     Created By          :     edwardzhe
*     Creation Date       :     [2016-04-30 20:29]
*     Last Modified       :     [2016-05-02 15:52]
*     Description         :      
**********************************************************************************/
#include "Graph.h"
#include "Amusement.h"
#include "BeginClock.h"

int main(int argc, char *argv[])
{
     //std::cout << "Printing begin " << std::endl;
     //std::this_thread::sleep_for(time_unit(33 * 60));
     //std::cout << "Printing end " << std::endl;
    //          << "us.\n";
    BeginClock::get_instance();
    Graph::get_instance()->run();
    return 0;
}

