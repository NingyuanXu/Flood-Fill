/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace.
 *
 */


animation filler::fillStripeDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
  stripeColorPicker stripePicker(fillColor,stripeSpacing);
  return fill<Stack> (img, x, y, stripePicker, tolerance,frameFreq);
}

animation filler::fillBorderDFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
  borderColorPicker borderPicker(borderColor,img,tolerance,*(img.getPixel(x,y)));
  return fill<Stack> (img, x, y, borderPicker, tolerance,  frameFreq);
}

/* Given implementation of a DFS rainbow fill. */
animation filler::fillRainDFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
  rainbowColorPicker a(freq);
  return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillStripeBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
  stripeColorPicker stripePicker(fillColor,stripeSpacing);
  return fill<Queue> (img, x,  y, stripePicker,tolerance,frameFreq);
}

animation filler::fillBorderBFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
  borderColorPicker borderPicker(borderColor,img,tolerance,*(img.getPixel(x,y)));
  return fill<Queue> (img, x, y, borderPicker, tolerance, frameFreq);

}

/* Given implementation of a BFS rainbow fill. */
animation filler::fillRainBFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    rainbowColorPicker a(freq);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure.
     *
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are
     *              within (or equal to) tolerance distance from the center,
     *              to the ordering structure.
     *        2.    use the colorPicker to set the new color of the point.
     *        3.    mark the point as processed.
     *        4.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        For this assignment, each pixel p has 8 neighbors, consisting of
     *        the 8 pixels who share an edge or corner with p. (We leave it to
     *        you to describe those 8 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours!
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the ordering structure (queue or stack)
     *        is as follows: **UPRIGHT(+x,-y), UP(-y), UPLEFT(-x,-y), LEFT(-x),
     *        DOWNLEFT(-x,+y), DOWN(+y), DOWNRIGHT(+x,+y), RIGHT(+x)**
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and
     *        it will be the one we test against.
     */
 animation ani;
 int i = 0;
 HSLAPixel center = *(img.getPixel(x,y));
 int ** s = new int* [img.width()];
 for (unsigned p = 0; p < img.width(); p++ ) {
     s[p] = new int[img.height()];
 }

 for (unsigned p = 0; p < img.width(); p++) {
     for (unsigned j = 0 ; j < img.height(); j++) {
       s[p][j] = 0;
    }
}


 OrderingStructure<int> o;

 *(img.getPixel(x,y)) = fillColor(x,y);
 o.add(x*img.height() + y);
 s[x][y] = 1;
 i ++;
 while (!o.isEmpty()) {
     int loc = o.remove();
     int loc_y = loc % img.height();
     int loc_x = (loc - loc_y) / img.height();
     int Loc_x[] = {1,0,-1,-1,-1,0,1,1};
     int Loc_y[] = {-1,-1,-1,0,1,1,1,0};

     for (int k= 0; k < 8; k++) {
       int new_x = loc_x + Loc_x[k];
       int new_y = loc_y + Loc_y[k];
       if (new_x >= 0 && new_x < (int)img.width() && new_y >= 0 && new_y < (int)img.height() && s[new_x][new_y] == 0 &&
        center.dist(*(img.getPixel(new_x,new_y))) <= tolerance)  {
          o.add(new_x*img.height()+ new_y);
          s[new_x][new_y] = 1;
          *(img.getPixel(new_x,new_y)) = fillColor(new_x,new_y);
          i ++;
          if (i % frameFreq == 0) {
            ani.addFrame(img);
          }
        }
     }
   }
    ani.addFrame(img);
    for (unsigned p = 0; p < img.width() ; p ++) {
      delete[] s[p];
    }
    delete[] s;
    return ani;
}
