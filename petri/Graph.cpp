/*********************************************************************************
*     File Name           :     Graph.cpp
*     Created By          :     edwardzhe
*     Creation Date       :     [2016-04-30 21:02]
*     Last Modified       :     [2016-05-02 19:49]
*     Description         :      
**********************************************************************************/
#include "Graph.h"
Graph *Graph::get_instance()
{
    static Graph *c_singleton;
    if (c_singleton == NULL)
    {
        c_singleton = new Graph();
    }
    return c_singleton;
}
Graph::Graph()
{
    _amusement_park.insert({"in_out",std::make_shared<Amusement>("in_out", 1, time_unit(0))});
    _amusement_park.insert({"A",std::make_shared<Amusement>("A", 400, time_unit(33*60))});
    _amusement_park.insert({"B",std::make_shared<Amusement>("B" ,30, time_unit(1*60 + 15))});
    _amusement_park.insert({"C",std::make_shared<Amusement>("C", 50, time_unit(2*60 + 30))});
    _amusement_park.insert({"D",std::make_shared<Amusement>("D", 30, time_unit(2*60 + 30))});
    _amusement_park.insert({"E",std::make_shared<Amusement>("E", 100, time_unit(5*60))});
    _amusement_park.insert({"F",std::make_shared<Amusement>("F" ,50, time_unit(2*60 + 30))});
    _amusement_park.insert({"G",std::make_shared<Amusement>("G", 30, time_unit(2*60))});
    _amusement_park.insert({"H",std::make_shared<Amusement>("H", 30, time_unit(1*60 + 30))});
    _amusement_park.insert({"I",std::make_shared<Amusement>("I", 20, time_unit(1*60 + 30))});
    _amusement_park.insert({"J",std::make_shared<Amusement>("J", 50, time_unit(2*60))});

    _amusement_park["in_out"]->insert_neighbor({_amusement_park["A"], time_unit(273)});
    _amusement_park["in_out"]->insert_neighbor({_amusement_park["B"], time_unit(364)});

    _amusement_park["A"]->insert_neighbor({_amusement_park["B"], time_unit(273)});
    _amusement_park["A"]->insert_neighbor({_amusement_park["J"], time_unit(228)});
    _amusement_park["A"]->insert_neighbor({_amusement_park["in_out"], time_unit(273)});
    _amusement_park["A"]->insert_neighbor({_amusement_park["E"], time_unit(319)});

    _amusement_park["B"]->insert_neighbor({_amusement_park["in_out"], time_unit(364)});
    _amusement_park["B"]->insert_neighbor({_amusement_park["A"], time_unit(273)});
    _amusement_park["B"]->insert_neighbor({_amusement_park["C"], time_unit(273)});
    _amusement_park["B"]->insert_neighbor({_amusement_park["E"], time_unit(319)});

    _amusement_park["C"]->insert_neighbor({_amusement_park["B"], time_unit(273)});
    _amusement_park["C"]->insert_neighbor({_amusement_park["E"], time_unit(455)});
    _amusement_park["C"]->insert_neighbor({_amusement_park["D"], time_unit(410)});

    _amusement_park["D"]->insert_neighbor({_amusement_park["C"], time_unit(410)});
    _amusement_park["D"]->insert_neighbor({_amusement_park["F"], time_unit(455)});

    _amusement_park["E"]->insert_neighbor({_amusement_park["G"], time_unit(500)});
    _amusement_park["E"]->insert_neighbor({_amusement_park["I"], time_unit(410)});
    _amusement_park["E"]->insert_neighbor({_amusement_park["C"], time_unit(455)});
    _amusement_park["E"]->insert_neighbor({_amusement_park["B"], time_unit(319)});
    _amusement_park["E"]->insert_neighbor({_amusement_park["A"], time_unit(319)});
    
    _amusement_park["F"]->insert_neighbor({_amusement_park["D"], time_unit(455)});
    _amusement_park["F"]->insert_neighbor({_amusement_park["G"], time_unit(591)});
    
    _amusement_park["G"]->insert_neighbor({_amusement_park["F"], time_unit(591)});
    _amusement_park["G"]->insert_neighbor({_amusement_park["E"], time_unit(500)});
    _amusement_park["G"]->insert_neighbor({_amusement_park["H"], time_unit(364)});

    _amusement_park["H"]->insert_neighbor({_amusement_park["G"], time_unit(364)});
    _amusement_park["H"]->insert_neighbor({_amusement_park["I"], time_unit(410)});

    _amusement_park["I"]->insert_neighbor({_amusement_park["H"], time_unit(410)});
    _amusement_park["I"]->insert_neighbor({_amusement_park["J"], time_unit(319)});
    _amusement_park["I"]->insert_neighbor({_amusement_park["E"], time_unit(410)});

    _amusement_park["J"]->insert_neighbor({_amusement_park["I"], time_unit(319)});
    _amusement_park["J"]->insert_neighbor({_amusement_park["A"], time_unit(228)});
}
void Graph::run()
{
    std::map<std::string, std::shared_ptr<Amusement>>::iterator it;
    std::vector<std::thread> vec_thread;
    for (it = _amusement_park.begin(); it != _amusement_park.end(); ++it)
    {
        if(it->first == "in_out")
        {
            continue;
        }
        it->second->run();
    }
    _amusement_park["in_out"]->in_out_run();
        
}
