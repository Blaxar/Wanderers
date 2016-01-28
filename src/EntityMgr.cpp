#include <iostream>
#include <EntityMgr.hpp>

#ifndef _CACHE_FRIENDLY

std::vector<EntityPtr> EntityMgr::create(Entity proto, size_t number)
{

	std::vector<EntityPtr> entities;
   	size_t added_entities;

	//First, we search for available slots among already allocated ones
	for(added_entities = 0; added_entities < number && added_entities < _freeSlots.size(); added_entities++)
	{
		entities.push_back(EntityPtr(*this, _entities.size()));
		_entities[_freeSlots[added_entities]] = proto;
	}

	//Then, if we still have entities left to create, we allocate space for them
	for(size_t i=added_entities; i<number; i++)
	{
		entities.push_back(EntityPtr(*this, _entities.size()));
		_entities.push_back(proto);
	}
		
	return entities;
	
}
	
void EntityMgr::destroy(EntityPtr& entity)
{

	_entities[entity._id]._type = None;
	_freeSlots.push_back(entity._id);
	
}
	
void EntityMgr::update(uint32_t elapsed_time_ns)
{

	_controlMgr->setUp();
    for(Entity& ent: _entities) _controlMgr->update(elapsed_time_ns, ent);
	_controlMgr->tearDown();

	_physicsMgr->setUp();
    for(Entity& ent: _entities) _physicsMgr->update(elapsed_time_ns, ent);
	_physicsMgr->tearDown();

	_graphicsMgr->setUp();
    for(Entity& ent: _entities) _graphicsMgr->update(elapsed_time_ns, ent);
	_graphicsMgr->tearDown();

	_soundMgr->setUp();
    for(Entity& ent: _entities) _soundMgr->update(elapsed_time_ns, ent);
    _soundMgr->tearDown();
	
}

#endif
