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

class FileHandler
{
public:
  FileHandler(UTF8Path filePath)
    : m_file{nullptr}
  {
    if (filePath.length() > 0)
    {
      m_file = fopen(filePath.c_str(), "r");
    }
  };

  ~FileHandler()
  {
    if (m_file != nullptr)
    {
      fclose(m_file);
      m_file = nullptr;
    }
  }

  auto FileDescriptor() -> FILE* { return m_file; }

private:
  FILE* m_file;
};

auto IsNumber(const std::string& maybeNumber) -> bool
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

/*
 Function for reading in our zip code table file.
 Returns 0 when no errors were encounted or a positive number when an error was
 found.
 */
auto LoadZipCodes(const UTF8Path filePath) -> std::tuple<Success, ErrMessage, ZipCodeMap>
{
  auto file = FileHandler(filePath);

  // Check to see if there were any errors
  if (file.FileDescriptor() == nullptr)
  {
    const auto error = "An error occurred while attempting to open our file: " + std::string{strerror(errno)};
    return std::make_tuple(false, error, ZipCodeMap{});
  }

  auto zipCodeMap = ZipCodeMap{};
  auto line       = std::vector<char>(1024, 'z');
  auto fields     = std::vector<std::string>(6, ""s);

  // extract each field
  auto filePtr = file.FileDescriptor();
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

    if (IsNumber(fields[2]))
    {
      const auto lat    = std::stod(fields[2]);
      const auto lon    = std::stod(fields[3]);
      const auto latLon = LatLon{lat, lon};
      const auto zip    = std::stoi(fields[0]);
      zipCodeMap[zip]   = latLon;
    }
  }

  return std::make_tuple(true, ErrMessage{"Success"}, zipCodeMap);
}
