/*
 *  zipcodes.h
 *  Haversine
 *
 *  Created by Jaime Rios on 2/17/08.
 *
 */

#include <map>
#include <string>
#include <tuple>

using utf8path_t   = std::string;
using errnum_t     = int32_t;
using errmessage_t = std::string;
using success_t    = bool;

// Structure for containing our Latitude and Longitude pair
struct lat_lon
{
private:
  double latitude;
  double longtitude;

public:
  lat_lon()
    : latitude(0)
    , longtitude(0){};
  lat_lon(const double lat, const double lon)
    : latitude(lat)
    , longtitude(lon){};

  double get_latitude() const { return latitude; };
  double get_longtitude() const { return longtitude; };

  void set_latitude(const double newVal) { latitude = newVal; };
  void set_longtitude(const double newVal) { longtitude = newVal; };
};

using zipcode_t  = int32_t;
using zipcodes_t = std::map<zipcode_t, lat_lon>;

auto load_zip_codes(const utf8path_t filePath) -> std::tuple<success_t, errmessage_t, zipcodes_t>;
