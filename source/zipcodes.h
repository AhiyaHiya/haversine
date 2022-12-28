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
  double m_latitude  = 0.0;
  double m_longitude = 0.0;

public:
  lat_lon()
    : m_latitude(0)
    , m_longitude(0){};
  lat_lon(const double lat, const double lon)
    : m_latitude(lat)
    , m_longitude(lon){};

  double get_latitude() const { return m_latitude; };
  double get_longitude() const { return m_longitude; };

  void set_latitude(const double new_val) { m_latitude = new_val; };
  void set_longitude(const double new_val) { m_longitude = new_val; };
};

using zipcode_t  = int32_t;
using zipcodes_t = std::map<zipcode_t, lat_lon>;

auto load_zip_codes(const utf8path_t file_path) -> std::tuple<success_t, errmessage_t, zipcodes_t>;
