#include "Touch_Handler.h"

#define TOUCH_DELAY 1000
static unsigned int Touch_Delay = TOUCH_DELAY;

void Touch_Handler_Update(void)
{
	Touch_Delay++;
}

int Screen_Touched(Point_2D *position)
{
	// Check if the touch delay is 0, meaning we are allowed to touch the display
	if(Touch_Delay >= TOUCH_DELAY)
	{
		// Check if the display was touched
		TOUCH_STATE  tsc_state;
		Touch_GetState (&tsc_state); /* Get touch state */   
		if (tsc_state.pressed) 
		{
			// Get the position of the touch and store it in the parameter, position
			position->x = tsc_state.x;
			position->y = tsc_state.y;
			
			return 1;
		}
	}
	
	return 0;
}

Entity* Point_Entity_Collision(Point_2D *point, Entity *entities, const unsigned int num_entities)
{
	
	// Check which entities were touched
	int i = 0;
	for(i = 0; i < num_entities; i++)
	{
		if(Point_Entity_Test(point, &entities[i]))
		{
			// Now that an entity has been touched, we want to reset the touch delay tick counter
			Touch_Delay = 0;
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
