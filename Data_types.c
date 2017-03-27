#include "Data_Types.h"

Entity Entity_Make(const Point_2D _p, Icon *_i)
{
	Entity entity;
	
	entity.position = _p;
	entity.image = _i;
	
	return entity;
}

Point_2D Point_2D_Make(const int _x, const int _y)
{
	Point_2D point;
	
	point.x = _x;
	point.y = _y;
	
	return point;
}

Icon Icon_Make(const unsigned int _width, const unsigned int _height, const unsigned int _bytes_per_pixel, unsigned char *_pixel_data)
{
	Icon icon;
	
	icon.width = _width;
	icon.height = _height;
	icon.bytes_per_pixel = _bytes_per_pixel;
	icon.pixel_data = _pixel_data;
	
	return icon;
}
