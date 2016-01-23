#ifndef COMPONENTMGR_HPP
#define COMPONENTMGR_HPP

#include <vector>
#include <cstddef>
#include <Entity.hpp>

struct Entity;

class ComponentMgr
{
	
    public:

    virtual void update(uint16_t elapsed_time, std::vector<Entity>& entities) = 0;
	
};

#endif //COMPONENTMGR_HPP
