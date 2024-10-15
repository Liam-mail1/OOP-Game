
#include "WallSet.h"
#include "raylib.h"

WallSet::WallSet(int type) {
  switch (type) {
  case 1:
    wallcount = sizeof(Wallset1[0]) / sizeof(Wallset1[0][0]);
    Wallnum = 1;
    break;
  }
};

void WallSet::draw(int type) {
  switch (type) {
  case 1:
    for (int i = 0; i < wallcount; i++) {
      DrawRectangle(Wallset1[0][i], Wallset1[1][i], Wallset1[2][i],
                    Wallset1[3][i], BLACK);
    }

    break;
  }
};

int WallSet::getX(int wallset, int num) {
  if (wallset == 1) {
    return Wallset1[0][num];
  }
  return -1;
};
int WallSet::getY(int wallset, int num) {
  if (wallset == 1) {
    return Wallset1[1][num];
  }
  return -1;
};
int WallSet::getWidth(int wallset, int num) {
  if (wallset == 1) {
    return Wallset1[2][num];
  }
  return -1;
};
int WallSet::getLength(int wallset, int num) {
  if (wallset == 1) {
    return Wallset1[3][num];
  }
  return -1;
};

int WallSet::getWallcount() { return wallcount; };
int WallSet::getNum() { return Wallnum; }

int WallSet::getWallDIr(int type, int num) {
  if (type == 1) {
    return Wallset1Dir[num];
  }
  return -1;
};