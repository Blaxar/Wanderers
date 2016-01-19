#include <iostream>
#include <EntityMgr.hpp>


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

void EntityMgr::update(uint32_t elapsed)
{

    if(_aiMgr != NULL) _aiMgr->update(elapsed, _entities);
	if(_physicsMgr != NULL) _physicsMgr->update(elapsed, _entities);
	if(_graphicsMgr != NULL) _graphicsMgr->update(elapsed, _entities);
    if(_soundMgr != NULL) _soundMgr->update(elapsed, _entities);
	
}
