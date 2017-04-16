
#ifndef _TOUCH_HANDLER_H
#define _TOUCH_HANDLER_H

#include "Data_Types.h"
#include "Board_Touch.h"


void Touch_Handler_Update(void);

int Screen_Touched(Point_2D *position);

Entity* Point_Entity_Collision(Point_2D *point, Entity *entities, const unsigned int num_entities);

int Point_Entity_Test(Point_2D *point, Entity *entity);

#endif /* _TOUCH_HANDLER_H */
