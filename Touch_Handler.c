#include "Touch_Handler.h"


Entity* Point_Entity_Collision(Point_2D *point, Entity *entities, const unsigned int num_entities)
{
	
	int i = 0;
	for(i = 0; i < num_entities; i++)
	{
		if(Point_Entity_Test(point, &entities[i]))
		{
			return &entities[i];
		}
	}
	
	return 0;
}

int Point_Entity_Test(Point_2D *point, Entity *entity)
{
	if(point->x > entity->position.x 
		&& point->x < entity->position.x + entity->image->width 
	  && point->y > entity->position.y
		&& point->y < entity->position.y + entity->image->height )
	{
		return 1;
	}
	return 0;
}
