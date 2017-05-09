/**
  ******************************************************************************
  * @file    entity.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    25-March-2017
  * @brief   Contains data structures related to Entity.
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ENTITY_H
#define _ENTITY_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup DATA_STRUCTURES
  * @{
	*
	* Data structures used for graphical representations of objects.
  */
	
/**
  * @brief Specifies a graphical image.
  */
typedef struct
{
	unsigned int  	 width;
  unsigned int  	 height;
  unsigned int  	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char 	 *pixel_data;
} Icon;

/**
  * @brief Specifies a 2D point.
  */
typedef struct
{
	int x, y;
} Point_2D;

/**
  * @brief A graphical entity with a position and an image.
  */
typedef struct
{
	Point_2D position;
	Icon *image;
} Entity;

/**
  * @brief  Initalises an Entity structure.
	* @param	_p: A coodinate
	* @param	_i: An icon
	* @retval Entity: The Entity created from the parameters
  */
Entity Entity_Make(const Point_2D _p, Icon *_i);

/**
  * @brief  Initalises an Point_2D structure.
	* @param	_x: A x coodinate
	* @param	_y: A y coordinate
	* @retval Point_2D: The Point_2D created from the parameters
  */
Point_2D Point_2D_Make(const int _x, const int _y);

/**
  * @brief  Initalises an Icon structure.
	* @param	_width: 	The width of the image.
	* @param	_height: 	The height of the image.
	* @param	_bytes_per_pixel: The number of pixels in the image.
	* @param	_pixel_data:	The pixel data of the image.
	* @retval Icon: The Icon created from the parameters
  */
Icon Icon_Make(const unsigned int _width, const unsigned int _height, const unsigned int _bytes_per_pixel, unsigned char *_pixel_data);

/**
  * @brief  Tests for a collision between an Entity and a Point_2D.
	* @param	entity: 	The Entity structure.
	* @param	point: 	The Point_2D structure.
	* @retval status: 1 if collision, 0 if not.
  */
uint8_t Entity_Point_Collision(const Entity *entity, const Point_2D *point);

/**
  * @}
  */ 

#endif /* _ENTITY_H */
