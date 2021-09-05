#include "pch.h"
#include "../Simplify/DouglasPeucker.h"

TEST(simplify, PerpendicularDistance_001)
{
  Point A(30, 20);
  Point B(200,80);
  Point C(160,00);
  double dist = simplify::PerpendicularDistance(C, A, B);

  EXPECT_EQ((int)dist, 62);
  EXPECT_TRUE(true);
  
}