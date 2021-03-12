/*
 *  Harversine.c
 *  Haversine
 *
 *  Created by Jaime Rios on 2/16/08.
 *
 */

#include "Harversine.h"

#include <math.h> // For PI

/*
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
auto CalculateDistance(const Angle latitude1,
                       const Angle longtitude1,
                       const Angle latitude2,
                       const Angle longtitude2) -> Angle
{
    const auto radius = Kilometers{6371}; // Earth's radius

    // Get the difference between our two points then convert the difference into radians
    const auto latDelta = Convert(latitude2 - latitude1);
    const auto lonDelta = Convert(longtitude2 - longtitude1);

    const auto convertedLat1 = Convert(latitude1);
    const auto convertedLat2 = Convert(latitude2);

    const auto a =
        pow(sin(latDelta / 2), 2) + cos(convertedLat1) * cos(convertedLat2) * pow(sin(lonDelta / 2), 2);

    const auto c = 2 * atan2(sqrt(a), sqrt(1 - a));
    const auto d = radius * c;

    return d;
}

// Convert our passed value to Radians
auto Convert(const Angle angle) -> Radians { return angle * (M_PI / 180); }
