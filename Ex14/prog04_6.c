#include <stdio.h>
#include "prog04_1.h"

Point CalcTriangleCentroid(Triangle *tri){
  Point Centroid = {0.0 ,0.0};
  int i;

  for(i = 0; i < 3; i++){
    Centroid.x += tri->vertex[i].x;
    Centroid.y += tri->vertex[i].y;
  }

  Centroid.x /= 3.0;
  Centroid.y /= 3.0;

  return Centroid;
}
