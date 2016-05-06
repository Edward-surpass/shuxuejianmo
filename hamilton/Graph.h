/*********************************************************************************
*     File Name           :     graph.h
*     Created By          :     edwardzhe
*     Creation Date       :     [2016-04-30 20:57]
*     Last Modified       :     [2016-05-02 13:14]
*     Description         :      
**********************************************************************************/
#ifndef GRAPH_H_
#define GRAPH_H_
#include "Amusement.h"
#include <map>
class Graph{
    private:
        Graph();
        std::map<std::string, std::shared_ptr<Amusement>> _amusement_park;

    public:
        static Graph *get_instance();
        void run();
};
#endif

