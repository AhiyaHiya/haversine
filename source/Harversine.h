/*
 *  Harversine.h
 *  Haversine
 *
 *  Created by Jaime Rios on 2/16/08.
 *
 */

using Angle      = double;
using Radians    = double;
using Kilometers = double;

auto CalculateDistance(const Angle latitude1,
                       const Angle longtitude1,
                       const Angle latitude2,
                       const Angle longtitude2) -> Angle;

auto Convert(const Angle angle) -> Radians;
