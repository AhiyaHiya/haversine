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
  double longitude;

public:
  lat_lon()
    : latitude(0)
    , longitude(0){};
  lat_lon(const double lat, const double lon)
    : latitude(lat)
    , longitude(lon){};

  double get_latitude() const { return latitude; };
  double get_longitude() const { return longitude; };

  void set_latitude(const double new_val) { latitude = new_val; };
  void set_longitude(const double new_val) { longitude = new_val; };
};

using zipcode_t  = int32_t;
using zipcodes_t = std::map<zipcode_t, lat_lon>;

auto load_zip_codes(const utf8path_t file_path) -> std::tuple<success_t, errmessage_t, zipcodes_t>;
