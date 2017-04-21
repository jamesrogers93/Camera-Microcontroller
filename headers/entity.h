#ifndef _ENTITY_H
#define _ENTITY_H

#include <stdint.h>

typedef struct
{
	unsigned int  	 width;
  unsigned int  	 height;
  unsigned int  	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char 	 *pixel_data;
} Icon;

typedef struct
{
	int x, y;
} Point_2D;

typedef struct
{
	Point_2D position;
	Icon *image;
} Entity;

Entity Entity_Make(const Point_2D _p, Icon *_i);

Point_2D Point_2D_Make(const int _x, const int _y);

Icon Icon_Make(const unsigned int _width, const unsigned int _height, const unsigned int _bytes_per_pixel, unsigned char *_pixel_data);

uint8_t Entity_Point_Collision(const Entity *entity, const Point_2D *point);

#endif /* _ENTITY_H */
