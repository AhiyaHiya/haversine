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


auto CalculateDistance( Angle latitude1, Angle longtitude1, Angle latitude2, Angle longtitude2 ) -> Angle;

auto Convert( const Angle angle ) -> Radians;