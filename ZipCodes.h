/*
 *  ZipCodes.h
 *  Haversine
 *
 *  Created by Jaime Rios on 2/17/08.
 *
 */

#include <map>
#include <string>
#include <tuple>

using UTF8Path   = std::string;
using ErrNum     = int32_t;
using ErrMessage = std::string;
using Success    = bool;

// Structure for containing our Latitude and Longitude pair
struct LatLon
{
  private:
    double latitude;
    double longtitude;

  public:
    LatLon()
        : latitude(0)
        , longtitude(0){};
    LatLon(const double lat, const double lon)
        : latitude(lat)
        , longtitude(lon){};

    double GetLat() const { return latitude; };
    double GetLon() const { return longtitude; };

    void SetLat(const double newVal) { latitude = newVal; };
    void SetLon(const double newVal) { longtitude = newVal; };
};

using ZipCode    = int32_t;
using ZipCodeMap = std::map< ZipCode, LatLon >;

auto LoadZipCodes(const UTF8Path filePath) -> std::tuple< Success, ErrMessage, ZipCodeMap >;
