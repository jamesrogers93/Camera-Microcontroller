/**
  ******************************************************************************
  * @file    entity.c
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    25-March-2017
  * @brief   Contains data structures related to Entity.
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "entity.h"

/** @addtogroup DATA_STRUCTURES
  * @{
	*
	* Data structures used for graphical representations of objects.
  */
	
/**
  * @brief  Initalises an Entity structure.
	* @param	_p: A coodinate
	* @param	_i: An icon
	* @retval Entity: The Entity created from the parameters
  */
Entity Entity_Make(const Point_2D _p, Icon *_i)
{
	Entity entity;
	
	entity.position = _p;
	entity.image = _i;
	
	return entity;
}

/**
  * @brief  Initalises an Point_2D structure.
	* @param	_x: A x coodinate
	* @param	_y: A y coordinate
	* @retval Point_2D: The Point_2D created from the parameters
  */
Point_2D Point_2D_Make(const int _x, const int _y)
{
	Point_2D point;
	
	point.x = _x;
	point.y = _y;
	
	return point;
}

/**
  * @brief  Initalises an Icon structure.
	* @param	_width: 	The width of the image.
	* @param	_height: 	The height of the image.
	* @param	_bytes_per_pixel: The number of pixels in the image.
	* @param	_pixel_data:	The pixel data of the image.
	* @retval Icon: The Icon created from the parameters
  */
Icon Icon_Make(const unsigned int _width, const unsigned int _height, const unsigned int _bytes_per_pixel, unsigned char *_pixel_data)
{
	Icon icon;
	
	icon.width = _width;
	icon.height = _height;
	icon.bytes_per_pixel = _bytes_per_pixel;
	icon.pixel_data = _pixel_data;
	
	return icon;
}

/**
  * @brief  Tests for a collision between an Entity and a Point_2D.
	* @param	entity: 	The Entity structure.
	* @param	point: 	The Point_2D structure.
	* @retval status: 1 if collision, 0 if not.
  */
uint8_t Entity_Point_Collision(const Entity *entity, const Point_2D *point)
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

/**
  * @}
  */
