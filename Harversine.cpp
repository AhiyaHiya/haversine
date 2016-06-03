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
double CalculateDistance( double nLat1, double nLon1, double nLat2, double nLon2 )
{
	double nRadius = 6371; // Earth's radius in Kilometers

	// Get the difference between our two points then convert the difference into radians
	double nDLat = ToRad(nLat2 - nLat1);  
	double nDLon = ToRad(nLon2 - nLon1); 

	nLat1 =  ToRad(nLat1);
	nLat2 =  ToRad(nLat2);
	
	double nA =	pow ( sin(nDLat/2), 2 ) +
				cos(nLat1) * cos(nLat2) * 
				pow ( sin(nDLon/2), 2 );
	
	double nC = 2 * atan2( sqrt(nA), sqrt( 1 - nA ));
	double nD = nRadius * nC;
	
	return nD; // Return our calculated distance
}

// Convert our passed value to Radians
double ToRad( double nVal )
{
	return nVal * (M_PI/180);
}