#include <EntityMgr.hpp>

std::vector<EntityPtr> EntityMgr::create(Entity proto, size_t number) {

	  std::vector<EntityPtr> entities;
   	size_t added_entities;

	  //First, we search for available slots among already allocated ones
	  for (added_entities = 0; added_entities < number &&
         added_entities < _freeSlots.size(); added_entities++) {
		    entities.push_back(EntityPtr(*this, _entities.size()));
		    _entities[_freeSlots[added_entities]] = proto;
	  }

	  //Then, if we still have entities left to create, we allocate space for them
	  for (size_t i=added_entities; i<number; i++) {
		    entities.push_back(EntityPtr(*this, _entities.size()));
		    _entities.push_back(proto);
	  }
	
	  return entities;

}

void EntityMgr::destroy(EntityPtr& entity) {

	  _entities[entity._id]._type = None;
	  _freeSlots.push_back(entity._id);

}
	
void EntityMgr::update(uint32_t elapsed_time_ns) {

    size_t i=0;

	  if (_controlMgr != nullptr) {
		    _controlMgr->setUp();
		    for(i=0; i<_entities.size(); i++)
            _controlMgr->update(elapsed_time_ns,
                                (ControlComponent&) _entities[i]._control, i);
		    _controlMgr->tearDown();
	  }

    if (_physicsMgr != nullptr) {
		    _physicsMgr->setUp();
		    for(i=0; i<_entities.size(); i++)
            _physicsMgr->update(elapsed_time_ns,
                                (SpatialComponent&) _entities[i]._spatial,
                                (PhysicsComponent&) _entities[i]._physics, i);
		    _physicsMgr->tearDown();
    }

	  if (_graphicsMgr != nullptr) {
		    _graphicsMgr->setUp();
		    for(i=0; i<_entities.size(); i++)
            _graphicsMgr->update(elapsed_time_ns,
                                 (GraphicsComponent&) _entities[i]._graphics, i);
		    _graphicsMgr->tearDown();
	  }

	  if (_soundMgr != nullptr) {
	      _soundMgr->setUp();
        for(i=0; i<_entities.size(); i++)
            _soundMgr->update(elapsed_time_ns,
                              (SoundComponent&) _entities[i]._sound, i);
        _soundMgr->tearDown();
	  }
	
}
