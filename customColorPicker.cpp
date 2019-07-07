#include "customColorPicker.h"
#include "math.h"

customColorPicker::customColorPicker(HSLAPixel fillColor, int x, int y, double scale)
{
/* your code here! */
	color = fillColor;
	x_pos = x;
	y_pos = y;
	sle = scale;
}

HSLAPixel customColorPicker::operator()(int x, int y)
{
/* your code here! */
	HSLAPixel color1 = color;
	double tgt = (color1.h + ((x - x_pos)*(x - x_pos) + (y - y_pos)*(y - y_pos))*sle);
	color1.h = (tgt >360) ? (360. * (exp(-(tgt-360)/3600))) : tgt;
	return color1;
}
