/*
 *  ZipCodes.h
 *  Haversine
 *
 *  Created by Jaime Rios on 2/17/08.
 *
 */

#include <string>
#include <map>

using namespace std;


// Structure for containing our Latitude and Longitude pair
struct LatLon
{
private:
	double nLat;
	double nLon;
public:
	LatLon() : nLat (0), nLon(0){};
	LatLon(double lat, double lon) : nLat (lat), nLon(lon){};
	
	double GetLat(){return nLat;};
	double GetLon(){return nLon;};
	
	void SetLat(double nVal){nLat=nVal;};
	void SetLon(double nVal){nLon=nVal;};
};

// Function for returning our Latitude and Longitude
LatLon GetLatAndLon(int nZipCode);

// Function for reading in our zip code table
int LoadZipCodes(std::string strPathToFile);

// Function to clean up our global map
void ReleaseZipCodes();

// Function for converting strings to double
double ToDouble ( string strVal );
