/*
 *  ZipCodes.h
 *  Haversine
 *
 *  Created by Jaime Rios on 2/17/08.
 *
 */

#include <string>
#include <map>
#include <tuple>

using UTF8Path   = std::string;
using ErrNum     = int32_t;
using ErrMessage = std::string;
using Success    = bool;

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
auto GetLatAndLon(const int32_t zipCode) -> LatLon;

auto LoadZipCodes(const UTF8Path filePath) -> std::tuple<Success, ErrMessage>;


// Function to clean up our global map
void ReleaseZipCodes();

// Function for converting strings to double
auto ConvertStringToDouble ( const std::string stringVal ) -> double;
