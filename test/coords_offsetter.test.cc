#include "coords_offsetter.hh"

#include <math.h>

#include <gtest/gtest.h>

TEST(CoordsOffsetter, wgs2gcj) {
  Coords coords;

  coords.x = 0;
  coords.y = 0;
  CoordsOffsetter::wgs2gcj(&coords);
  ASSERT_EQ(coords.x, 0);
  ASSERT_EQ(coords.x, 0);

  coords.x = 116.39;
  coords.y = 39.9;
  CoordsOffsetter::wgs2gcj(&coords);
  ASSERT_TRUE(abs(coords.x - 116.396240) < 1e-6);
  ASSERT_TRUE(abs(coords.y - 39.901400) < 1e-6);

  coords.x = 121.48;
  coords.y = 31.22;
  CoordsOffsetter::wgs2gcj(&coords);
  ASSERT_TRUE(abs(coords.x - 121.484501) < 1e-6);
  ASSERT_TRUE(abs(coords.y - 31.218035) < 1e-6);
}