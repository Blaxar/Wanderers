#ifndef ENTITYMGR_HPP
#define ENTITYMGR_HPP

#include <vector>
#include <Entity.hpp>
#include <ComponentMgr.hpp>
#include <cstddef>

class VoidMgr
{
	
    public:

    void update(uint16_t elapsed_time, std::vector<Entity>& entities){}
	
};

template <class ControlMgrT, class PhysicsMgrT, class GraphicsMgrT, class SoundMgrT>
class EntityPtr;

template<class ControlMgrT, class PhysicsMgrT, class GraphicsMgrT, class SoundMgrT>
class EntityMgr
{

using TypedEntityPtr = EntityPtr<ControlMgrT, PhysicsMgrT, GraphicsMgrT, SoundMgrT>;
	
public:

	static EntityMgr<ControlMgrT, PhysicsMgrT, GraphicsMgrT, SoundMgrT>&
	getInstance(ControlMgrT& aiMgr, PhysicsMgrT& physicsMgr, GraphicsMgrT& graphicsMgr, SoundMgrT& soundMgr)
	{

		static EntityMgr<ControlMgrT, PhysicsMgrT, GraphicsMgrT, SoundMgrT> instance
			   (aiMgr, physicsMgr, graphicsMgr, soundMgr);
		return instance;
		
	}

	std::vector<TypedEntityPtr> create(Entity proto, size_t number=1)
    {

		std::vector<TypedEntityPtr> entities;
		size_t added_entities;

		//First, we search for available slots among already allocated ones
		for(added_entities = 0; added_entities < number && added_entities < _freeSlots.size(); added_entities++)
		{
			entities.push_back(TypedEntityPtr(*this, _entities.size()));
			_entities[_freeSlots[added_entities]] = proto;
		}

		//Then, if we still have entities left to create, we allocate space for them
		for(size_t i=added_entities; i<number; i++)
		{
			entities.push_back(TypedEntityPtr(*this, _entities.size()));
			_entities.push_back(proto);
		}
		
		return entities;
	
	}
	
	void destroy(TypedEntityPtr& entity)
	{

		_entities[entity._id]._type = None;
		_freeSlots.push_back(entity._id);
	
    }
	
	void update(uint32_t elapsed)
	{

	    _controlMgr.update(elapsed, _entities);
	    _physicsMgr.update(elapsed, _entities);
	    _graphicsMgr.update(elapsed, _entities);
	    _soundMgr.update(elapsed, _entities);
	
	}

    Entity* operator [] (size_t i) {return &_entities[i];}

private:

	std::vector<size_t> _freeSlots;
	std::vector<Entity> _entities;

    ControlMgrT& _controlMgr;
	PhysicsMgrT& _physicsMgr;
    GraphicsMgrT& _graphicsMgr;
    SoundMgrT& _soundMgr;

	EntityMgr(ControlMgrT& aiMgr, PhysicsMgrT& physicsMgr, GraphicsMgrT& graphicsMgr, SoundMgrT& soundMgr):
		      _controlMgr(aiMgr), _physicsMgr(physicsMgr), _graphicsMgr(graphicsMgr), _soundMgr(soundMgr){}
	
	EntityMgr(EntityMgr const&) = delete;
	void operator = (EntityMgr const&) = delete;

	friend TypedEntityPtr;
	
};

template<class ControlMgrT, class PhysicsMgrT, class GraphicsMgrT, class SoundMgrT>
class EntityPtr
{

	using TypedEntityMgr = EntityMgr<ControlMgrT, PhysicsMgrT, GraphicsMgrT, SoundMgrT>;
	
    private:

    TypedEntityMgr& _entityMgr;
	size_t _id;
	
	EntityPtr(TypedEntityMgr& entityMgr, size_t id):_entityMgr(entityMgr), _id(id){}

    public:

	~EntityPtr(){}

	EntityType getType(){ return _entityMgr[_id]->_type; }

	friend TypedEntityMgr;
	
};

#endif //ENTITYMGR_HPP
