#ifndef COMPONENTREADER_HPP
#define COMPONENTREADER_HPP

#include <EntityMgr.hpp>

class ComponentReader
{

    private:

    EntityMgr& _entMgr;
	
    public:

	ComponentReader(EntityMgr& entMgr): _entMgr(entMgr){}

	inline const ControlComponent getControlComponent(size_t id){return _entMgr._entities[id]._control;}
	inline const SpatialComponent getSpatialComponent(size_t id){return _entMgr._entities[id]._spatial;}
	inline const PhysicsComponent getPhysicsComponent(size_t id){return _entMgr._entities[id]._physics;}
    inline const GraphicsComponent getGraphicsComponent(size_t id){return _entMgr._entities[id]._graphics;}
	inline const SoundComponent getSoundComponent(size_t id){return _entMgr._entities[id]._sound;}
	
};

#endif //COMPONENTREADER_HPP
