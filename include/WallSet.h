#ifndef WALLSET_H
#define WALLSET_H

#include "raylib.h"

class WallSet {

private:
int Wallset1[4][20] = {
    // X-coordinates
    {640, 896, 256, 128, 512, 768, 1152, 1408, 1280, 512, 1024, 1600, 256, 640, 1024, 1280, 512, 768, 384, 1792},
    // Y-coordinates
    {512, 640, 128, 256, 200, 512, 384, 640, 128, 256, 640, 128, 768, 640, 512, 896, 300, 200, 400, 700},
    // Widths (horizontal: 265, vertical: 10)
    {265, 10, 265, 10, 265, 10, 265, 10, 265, 10, 265, 10, 265, 10, 10, 265, 10, 10, 265, 10},
    // Lengths (horizontal: 10, vertical: 265)
    {10, 265, 10, 265, 10, 265, 10, 265, 10, 265, 10, 265, 10, 265, 256, 10, 265, 265, 10, 265}
};
// 128      1 horizontal 2 vertical 3 horizontal

  /*
  the matrix wallset is a predetermined matrix that contains arguments used
  to spwan a set of walls, each row contains information requred to spwan
  one rectangle using the raylib function drawRectangle() and each collumns
  stores four different intgers, which are

  x-coord of the top right corner of the wall,
  y-coord of tbe top right corner of the wall
  wdith of the wall
  length of the wall
  and colour of the wall( we will just stick to black)

  to add a new wall into the set simply increase the number of rows and
  mannuly fill in the coordinates that you desire
  */

  int Wallset1Dir[3] = {1, 2, 3};
  // this line tells the orientation of the wall, 1
  // for vertical and 2 for horizontal, this is
  // particular improtant for calculating the reflection of projectile when
  // hitting the wall

  int wallcount;
  int Wallnum;

public:
  WallSet(int type); // tells what set of wall you are using
  int getWallcount();

  int getX(int wallset, int num);
  int getY(int wallset, int num);
  int getWidth(int wallset, int num);
  int getLength(int wallset, int num);
  void draw(int type);
  int getNum();
  int getWallDIr(int type, int num);
  // the draw() will takes an argument asking whcih type of wall you want
  // to use, then use the corresponding
  // wallSet matrix to spwan walls in the map (we only have one wall set in the
  // moment)
};

#endif