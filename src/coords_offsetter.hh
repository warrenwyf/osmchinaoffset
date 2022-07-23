#pragma once

#include <cmath>

struct Coords {
  double x;
  double y;
};

const double a = 6378245.0;
const double ee = 0.00669342162296594323;
const double rad = M_PI / 180.0;
const double xpi = 3000.0 * rad;

struct CoordsOffsetter {
public:
  static void wgs2gcj(Coords* coords) {
    double lon = coords->x;
    double lat = coords->y;
    if (out_of_china(lon, lat)) {
      return;
    }

    double d_lat = transform_lat(lon - 105.0, lat - 35.0);
    double d_lon = transform_lon(lon - 105.0, lat - 35.0);
    double rad_lat = lat * rad;
    double magic = sin(rad_lat);
    magic = 1 - ee * magic * magic;
    double sqrt_magic = sqrt(magic);
    d_lat = d_lat / ((a * (1 - ee)) / (magic * sqrt_magic) * rad);
    d_lon = d_lon / (a / sqrt_magic * cos(rad_lat) * rad);
    coords->x = lon + d_lon;
    coords->y = lat + d_lat;
  }

private:
  static bool out_of_china(double lon, double lat) {
    if (lon > 73.66 && lon < 135.05 && lat > 3.86 && lat < 53.55) {
      return false;
    }

    return true;
  }

  static double transform_lon(double x, double y) {
    double ret = 300.0 + x + 2.0 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * sqrt(x > 0 ? x : -x);
    ret += (20.0 * sin(6.0 * x * M_PI) + 20.0 * sin(2.0 * x * M_PI)) * 2.0 / 3.0;
    ret += (20.0 * sin(x * M_PI) + 40.0 * sin(x / 3.0 * M_PI)) * 2.0 / 3.0;
    ret += (150.0 * sin(x / 12.0 * M_PI) + 300.0 * sin(x / 30.0 * M_PI)) * 2.0 / 3.0;
    return ret;
  }

  static double transform_lat(double x, double y) {
    double ret =
        -100.0 + 2.0 * x + 3.0 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * sqrt(x > 0 ? x : -x);
    ret += (20.0 * sin(6.0 * x * M_PI) + 20.0 * sin(2.0 * x * M_PI)) * 2.0 / 3.0;
    ret += (20.0 * sin(y * M_PI) + 40.0 * sin(y / 3.0 * M_PI)) * 2.0 / 3.0;
    ret += (160.0 * sin(y / 12.0 * M_PI) + 320 * sin(y * M_PI / 30.0)) * 2.0 / 3.0;
    return ret;
  }
};