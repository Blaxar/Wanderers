#ifndef ENTITYFACTORY_HPP
#define ENTITYFACTORY_HPP

#include <vector>
#include <Entity.hpp>
#include <cstddef>

class EntityFactory
{

	EntityFactory();
	~EntityFactory();

	Entity createWanderer();

};

#endif //ENTITYFACTORY_HPP
