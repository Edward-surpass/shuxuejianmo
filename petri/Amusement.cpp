/*********************************************************************************
*     File Name           :     Amusement.cpp
*     Created By          :     edwardzhe
*     Creation Date       :     [2016-04-30 18:07]
*     Last Modified       :     [2016-05-02 23:18]
*     Description         :      
**********************************************************************************/

#include "Amusement.h"
#include "BeginClock.h"
Amusement::Amusement(const std::string &name, const int &capacity, const time_unit &playtime):_name(name), _capacity(capacity), _playtime(playtime){
    _item_is_running = false;
}
void Amusement::work(){
    _log_mutex.lock();
    std::cout << _name << " Amusement is running" << std::endl;
    _log_mutex.unlock();
    while (true)
    {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        _log_mutex.lock();
        std::cout << "[" << std::chrono::duration_cast<time_unit>(end - BeginClock::get_instance()->get_begin_time()).count() << "]:" << _name << " Amusement now has Person size " << _ranks.size() << std::endl;
        _log_mutex.unlock();
        if (_ranks.size() > _capacity && !_item_is_running)
        {
            for (size_t i = 0; i < _capacity; ++i)
            {
                _log_mutex.lock();
                std::cout << std::setw(8) << std::setfill('0') << _ranks.front()->get_logid();
                std::cout << " is playing Amusement " << _name << "." << std::this_thread::get_id() << std::endl;
                _log_mutex.unlock();
                _ranks_mutex.lock();
                _has_play.push(_ranks.front());
                _ranks.pop_front();
                _ranks_mutex.unlock();
            }
            _item_is_running = true;
            std::thread t1(&Amusement::evacuate, this);
            std::this_thread::sleep_for(time_unit(_playtime));
            _item_is_running = false;
            t1.join();
            std::random_device rd;
            while(!_has_play.empty())
            {
                std::shared_ptr<Person> per = _has_play.front();
                size_t i = 0;
                while (i < _neighbor.size())
                {
                    if (!per->is_played(_neighbor[i].first->get_name()))
                    {
                        break;
                    }
                    ++i;
                }
                if (i == _neighbor.size())
                {
                    i = rd() % _neighbor.size();
                }
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                _log_mutex.lock();
                std::cout << "[" << std::chrono::duration_cast<time_unit>(end - BeginClock::get_instance()->get_begin_time()).count() << "]:";
                std::cout << std::setw(8) << std::setfill('0') <<  _has_play.front()->get_logid();
                std::cout << " has played Amusement " << _name << ", and is going to "<< _neighbor[i].first->get_name() << " Amusement. _has_play size" << _has_play.size() << " " << std::this_thread::get_id()<< std::endl;

                _log_mutex.unlock();
                std::thread t2(&Amusement::push, _neighbor[i].first, _has_play.front(), _neighbor[i].second, _neighbor[i].first);
                t2.detach();
                _has_play.front()->add_play_count();
                _has_play.pop();
            }
        }
    }
}
void Amusement::in_out_run()
{
    std::thread t1(&Amusement::in_out_work, this);
    t1.join();
}
void Amusement::in_out_work()
{
    _log_mutex.lock();
    std::cout << _name << " is running" << std::endl;
    _log_mutex.unlock();
    int logid = 1;
    std::random_device rd;
    std::default_random_engine generator;
    std::poisson_distribution<int> distribution(4.0);
    while(true)
    {
        //_log_mutex.lock();
        //std::cout << 123 << std::endl;
        //_log_mutex.unlock();
        while(!_ranks.empty())
        {
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            _log_mutex.lock();
            std::cout << std::setw(8) << std::setfill('0') << _ranks.front()->get_logid();
            std::cout << " will out of Amusement and he stay in Amusement time:";
            std::cout << std::chrono::duration_cast<time_unit>(end - _ranks.front()->get_begin_time()).count() << ". " ;
            std::cout << "play count :"<< _ranks.front()->get_play_count() << std::endl;;
            _log_mutex.unlock();

            _ranks_mutex.lock();
            _ranks.pop_front();
            _ranks_mutex.unlock();
        }
        std::shared_ptr<Person> per = std::make_shared<Person>(logid++);
        size_t i = rd() % 2;
        std::thread t2(&Amusement::push, _neighbor[i].first, per,  _neighbor[i].second, _neighbor[i].first);
        t2.detach();
        _log_mutex.lock();
        std::cout << std::setw(8) << std::setfill('0') << per->get_logid();
        std::cout << " " << "has get in Amusement" << std::endl;
        _log_mutex.unlock();
        std::this_thread::sleep_for(time_unit(distribution(generator)));
    }
}
void Amusement::run()
{
    std::thread t1(&Amusement::work, this);
    t1.detach();
}
int Amusement::get_capacity()
{
    return _capacity;
}
std::string Amusement::get_name()
{
    return _name;
}
int Amusement::get_ranks_size()
{
    return _ranks.size();
}
void Amusement::evacuate()
{
    while (_item_is_running)
    {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        _log_mutex.lock();
        std::cout << "[" << std::chrono::duration_cast<time_unit>(end - BeginClock::get_instance()->get_begin_time()).count() << "]:" << _name << " Amusement now has Person size " << _ranks.size() << " running evacuate" << std::endl;
        _log_mutex.unlock();
        if (_ranks.size() > _capacity)
        {
            std::random_device rd;
            size_t i = rd() % _neighbor.size();
            if (_neighbor[i].first->get_ranks_size() > _neighbor[i].first->get_capacity())
            {
                for (i = 0; i < _neighbor.size(); ++i) {
                    if (!(_neighbor[i].first->get_ranks_size() > _neighbor[i].first->get_capacity()))
                    {
                        break;
                    }
                }
                if (i == _neighbor.size())
                {

                    continue;
                }
                _ranks_mutex.lock();
                std::shared_ptr<Person> per = _ranks.back();
                std::thread t2(&Amusement::push, _neighbor[i].first, per, _neighbor[i].second, _neighbor[i].first);
                t2.detach();
                _ranks.pop_back();
                _ranks_mutex.unlock();
                _log_mutex.lock();
                std::cout << _name << " Amusement is crowd.";
                std::cout << std::setw(8) << std::setfill('0') << per->get_logid() ;
                std::cout << " is going to " << _neighbor[i].first->get_name()<< " Amusement ." << std::endl;
                _log_mutex.unlock();
            }

        }
        std::this_thread::sleep_for(time_unit(time_unit(1)));
    }
}

void Amusement::push(std::shared_ptr<Person> per, time_unit distance_time, std::shared_ptr<Amusement> amu){

    //_log_mutex.lock();
    //std::time_t beg = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    //std::cout << std::this_thread::get_id() << " Amusement " << amu->get_name() << " begin push ";
    //std::cout << std::setw(8) << std::setfill('0') << per->get_logid();
    //std::cout << " time:" << std::put_time(std::localtime(&beg), "%F %T") << '\n';
    //_log_mutex.unlock();

    std::this_thread::sleep_for(distance_time);

    //_log_mutex.lock();
    //std::time_t end = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    //std::cout << std::this_thread::get_id() << " Amusement " << amu->get_name() << " end push ";
    //std::cout << std::setw(8) << std::setfill('0') << per->get_logid();
    //std::cout << " time:" << std::put_time(std::localtime(&end), "%F %T") << '\n';
    //_log_mutex.unlock();

    per->insert_played(amu->get_name());
    //_log_mutex.lock();
    //per->print_played_amu();
    //_log_mutex.unlock();

    if(per->get_play_count() > 6)
    {
        per->delete_played("in_out");
    }


    amu->get_ranks_mutex().lock();
    amu->get_ranks().push_back(std::shared_ptr<Person>(per));
    amu->get_ranks_mutex().unlock();
    _log_mutex.lock();
    std::cout << std::setw(8) << std::setfill('0') <<  per->get_logid();
    std::cout << " has arraive " << amu->get_name() << " Amusement ." << std::endl;
    _log_mutex.unlock();

}

std::mutex &Amusement::get_ranks_mutex()
{
    return _ranks_mutex;
}
std::deque<std::shared_ptr<Person>> &Amusement::get_ranks()
{
    return _ranks;
}

Amusement::~Amusement(){
    
}

void Amusement::insert_neighbor(const std::pair<std::shared_ptr<Amusement>, time_unit> &negihbor){
    _neighbor.push_back(negihbor);
}
