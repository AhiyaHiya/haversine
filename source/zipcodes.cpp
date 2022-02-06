/*
 *  ZipCodes.c
 *  Haversine
 *
 *  Created by Jaime Rios on 2/17/08.
 *
 */

#include "zipcodes.h"

#include <cstdlib> // for atod function
#include <errno.h> // for errno
#include <sstream> // for converting strings to double
#include <string>
#include <vector>

using namespace std::string_literals;

/**********************************************************************/
class file_handler
{
public:
  file_handler(utf8path_t filePath)
    : m_file{nullptr}
  {
    if (filePath.length() > 0)
    {
      m_file = fopen(filePath.c_str(), "r");
    }
  };

  ~file_handler()
  {
    if (m_file != nullptr)
    {
      fclose(m_file);
      m_file = nullptr;
    }
  }

  auto file_descriptor() -> FILE* { return m_file; }

private:
  FILE* m_file;
};

/**********************************************************************/
auto is_number(const std::string& maybeNumber) -> bool
{
  auto decimal = false;
  for (char c : maybeNumber)
  {
    if (c == '.' && !decimal)
      decimal = true;
    else if (c == '-')
      continue;
    else if (!std::isdigit(c))
      return false;
  }
  return true;
};

/***********************************************************************
 Function for reading in our zip code table file.
 Returns 0 when no errors were encounted or a positive number when an error was
 found.
 */
auto load_zip_codes(const utf8path_t filePath) -> std::tuple<success_t, errmessage_t, zipcodes_t>
{
  auto file = file_handler(filePath);

  // Check to see if there were any errors
  if (file.file_descriptor() == nullptr)
  {
    const auto error = "An error occurred while attempting to open our file: " + std::string{strerror(errno)};
    return std::make_tuple(false, error, zipcodes_t{});
  }

  auto zip_codes = zipcodes_t{};
  auto line      = std::vector<char>(1024, 'z');
  auto fields    = std::vector<std::string>(6, ""s);

  // extract each field
  auto filePtr = file.file_descriptor();
  while (fgets(line.data(), static_cast<int32_t>(line.size()), filePtr) != 0)
  {
    auto field = strtok(line.data(), ",");
    auto index = 0;

    while (field != 0)
    {
      fields[index] = field;
      ++index;
      field = std::strtok(nullptr, ",");
    }

    if (is_number(fields[2]))
    {
      const auto lat    = std::stod(fields[2]);
      const auto lon    = std::stod(fields[3]);
      const auto latlon = lat_lon{lat, lon};
      const auto zip    = std::stoi(fields[0]);
      zip_codes[zip]    = latlon;
    }
  }

  return std::make_tuple(true, errmessage_t{"success_t"}, zip_codes);
}
