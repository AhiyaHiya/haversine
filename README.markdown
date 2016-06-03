# C implementation of Haversine Formula

Jaime O. Rios

www.jaimerios.com

# Intro
This implementation of the Haversine formula is a port of the Javascript implementation listed at http://www.movable-type.co.uk/scripts/latlong.html

In the included Xcode project, there is a mechanism to use zip codes to calculate the distance between two points.

Here are some notes from the source code:

### Haversine Formula
R = earth’s radius (mean radius = 6,371km)

Δlat = lat2− lat1

Δlong = long2− long1

a = sin²(Δlat/2) + cos(lat1).cos(lat2).sin²(Δlong/2)

c = 2.atan2(√a, √(1−a))

d = R.c

### JavaScript Example from http://www.movable-type.co.uk/scripts/latlong.html
var R = 6371; // km

var dLat = (lat2-lat1).toRad();

var dLon = (lon2-lon1).toRad();

lat1 = lat1.toRad(), lat2 = lat2.toRad();


var a = Math.sin(dLat/2) * Math.sin(dLat/2) +
Math.cos(lat1.toRad()) * Math.cos(lat2.toRad()) * 
Math.sin(dLon/2) * Math.sin(dLon/2); 

var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));

var d = R * c;