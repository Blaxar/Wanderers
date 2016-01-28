#ifndef COMPONENTMGR_HPP
#define COMPONENTMGR_HPP

#include <vector>
#include <cstddef>
#include <Entity.hpp>

struct Entity;

class ComponentMgr
{
	
    public:

    virtual void setUp(void) = 0;
    virtual void update(const uint32_t elapsed_time_ns, Entity& ent) = 0;
	virtual void tearDown(void) = 0;
	
};

#endif //COMPONENTMGR_HPP
