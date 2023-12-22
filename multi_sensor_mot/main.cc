#include <iostream>

#include "fusion_system/motion_fusion/motion_fusion.h"

void testKF();
void testEKF();

int main(){

  // testKF();

  // testEKF();
  fusion::MotionFusion mf;
  mf.motionFusion();

  return 0;
}