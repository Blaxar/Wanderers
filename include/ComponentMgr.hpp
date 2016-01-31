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
	virtual void tearDown(void) = 0;
	
};

class ControlMgr: public ComponentMgr
{
	
    public:

    virtual void setUp(void) = 0;
    virtual void update(const uint32_t elapsed_time_ns, ControlComponent& cmp, size_t id) = 0;
	virtual void tearDown(void) = 0;
	
};

class PhysicsMgr: public ComponentMgr
{
	
    public:

    virtual void setUp(void) = 0;
    virtual void update(const uint32_t elapsed_time_ns, SpatialComponent& sCmp, PhysicsComponent& pCmp, size_t id) = 0;
	virtual void tearDown(void) = 0;
	
};

class GraphicsMgr: public ComponentMgr
{
	
    public:

    virtual void setUp(void) = 0;
    virtual void update(const uint32_t elapsed_time_ns, GraphicsComponent& cmp, size_t id) = 0;
	virtual void tearDown(void) = 0;
	
};

class SoundMgr: public ComponentMgr
{
	
    public:

    virtual void setUp(void) = 0;
    virtual void update(const uint32_t elapsed_time_ns, SoundComponent& cmp, size_t id) = 0;
	virtual void tearDown(void) = 0;
	
};

#endif //COMPONENTMGR_HPP
