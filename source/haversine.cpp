/*
 *  Harversine.c
 *  Haversine
 *
 *  Created by Jaime Rios on 2/16/08.
 *
 */

#include "haversine.h"

#include <numbers>

/**********************************************************************
 Haversine Formula
 R = earth’s radius (mean radius = 6,371km)
 Δlat = lat2− lat1
 Δlong = long2− long1
 a = sin²(Δlat/2) + cos(lat1).cos(lat2).sin²(Δlong/2)
 c = 2.atan2(√a, √(1−a))
 d = R.c

 JavaScript Example from http://www.movable-type.co.uk/scripts/latlong.html
 var R = 6371; // km
 var dLat = (lat2-lat1).toRad();
 var dLon = (lon2-lon1).toRad();
 lat1 = lat1.toRad(), lat2 = lat2.toRad();

 var a = Math.sin(dLat/2) * Math.sin(dLat/2) +
                 Math.cos(lat1.toRad()) * Math.cos(lat2.toRad()) *
                 Math.sin(dLon/2) * Math.sin(dLon/2);
 var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
 var d = R * c;
 */
auto calculate_distance(const angle_t latitude1,
                        const angle_t longitude1,
                        const angle_t latitude2,
                        const angle_t longitude2) -> kilometers_t
{
  const auto radius = kilometers_t{6371}; // Earth's radius

  // Get the difference between our two points then convert the difference into radians
  const auto lat_delta = convert(latitude2 - latitude1);
  const auto lon_delta = convert(longitude2 - longitude1);

  const auto converted_lat1 = convert(latitude1);
  const auto converted_lat2 = convert(latitude2);

  const auto a =
      pow(sin(lat_delta / 2), 2) + cos(converted_lat1) * cos(converted_lat2) * pow(sin(lon_delta / 2), 2);

  const auto c = 2 * atan2(sqrt(a), sqrt(1 - a));
  const auto d = radius * c;

  return d;
}

// convert our passed value to radians_t
auto convert(const angle_t angle) -> radians_t
{
  return angle * (std::numbers::pi / 180);
}
