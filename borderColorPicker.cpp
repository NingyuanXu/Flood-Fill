#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance,HSLAPixel center)
{
color = fillColor;
im = img;
tol = tolerance;
ctr = center;
}

HSLAPixel borderColorPicker::operator()(int x, int y)
{
  for (int i = x - 3 ; i <= x + 3; i ++) {
    for (int j = y - 3 ; j <= y + 3; j ++) {
      if (i < 0 || i >= (int)im.width() || j < 0 || j >= (int)im.height() && ((x - i)*(x -i) + (y - j) * (y - j)) <= 9) {
        return color;
      }
      else if (((x - i)*(x -i) + (y - j) * (y - j)) <= 9 && ctr.dist(*(im.getPixel(i,j)))>tol && *(im.getPixel(i,j)) != color ) {
        return color;
      }
    }
  }
return *(im.getPixel(x,y));


}
