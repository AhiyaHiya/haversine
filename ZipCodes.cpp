/*
 *  ZipCodes.c
 *  Haversine
 *
 *  Created by Jaime Rios on 2/17/08.
 *
 */

#include "ZipCodes.h"
#include <cstdlib> // for atod function
#include <errno.h> // for errno
#include <sstream> // for converting strings to double
#include <cstring>
#include <vector>

/* In order for us to use our Zip codes, Latitudes and Longitudes, we have to store 
	those values in a container variable. Since out interface uses Zip code for 
	calculating our distances, we are going to use a stl map to hold our values and 
	give use the ability to search by zip code. */
static std::map<int, LatLon> static_ZipCodesMap;

// Function for returning our Latitude and Longitude
auto GetLatAndLon(const int32_t zipCode) -> LatLon
{
	// Find the zipcode
	auto zipFound = static_ZipCodesMap.find(zipCode);
	
	if(zipFound != static_ZipCodesMap.end())
		return (*zipFound).second;
	else
		return LatLon(0,0); // return zero if not found 
}

class FileHandler
{
public:
    FileHandler(UTF8Path filePath)
    : _file{nullptr}
    {
        if (filePath.length() > 0)
        {
            _file = fopen(filePath.c_str(),"r");
        }
    };
    
    ~FileHandler()
    {
        if (_file != nullptr)
        {
            fclose(_file);
            _file = nullptr;
        }
    }
    
    auto FileDescriptor() -> FILE* { return _file; }
    
private:
    FILE* _file;
};
/*
 Function for reading in our zip code table file.
 Returns 0 when no errors were encounted or a positive number when an error was found.
 */
auto LoadZipCodes(const UTF8Path filePath) -> std::tuple<Success, ErrMessage>
{
	// Make sure we have a path to work with
	if (filePath.length() > 0)
	{
        auto line = std::vector<char>(1024, 0);
		char fields[ 6 ][ 32 ] = {0x0};	// Multidimensional character array to hold each field found in a line
		
        auto file = FileHandler(filePath);
        
		// Check to see if there were any errors
		if (file.FileDescriptor() == nullptr)
		{
            auto errorString = std::vector<char>(1024, 0);
			sprintf (errorString.data(), "An error occurred while attempting to open our file: %s", strerror (errno) );
            return std::make_tuple(false, ErrMessage{ errorString.data() });
		}
		
		// If we got to this point, let's iterate over every line in our file and extract each field
        auto filePtr = file.FileDescriptor();
		while( fgets ( line.data(), line.size(), filePtr) !=0 )
		{
			/* 
			 Here strtok is used to first extract the field, then it is called 
			 recursively, with a NULL pointer, to get the remaining fields. */
			auto field = strtok(line.data(), ",");
			auto index = 0;
			
			while( field != 0)
			{
				strcpy(fields[index], field);
				++index;
                auto token = '\0';
                field = std::strtok(&token, ",");
			}
			
			// Now that we got our fields, let's get our latitude, longitude and zipcode
			// First, convert our C strings to doubles
			LatLon sLL( ToDouble(fields[2]), ToDouble(fields[3]) );
			static_ZipCodesMap[ atoi(fields[0]) ] = sLL;
		}
    
		return std::make_tuple(true, ErrMessage{ "Success" });
	}
	else
		return std::make_tuple(false, ErrMessage{ "Fail" });
}

// Function to clean up after ourselves
void ReleaseZipCodes()
{
	if ( !static_ZipCodesMap.empty() )
		static_ZipCodesMap.clear();
}

// Function to convert string to double
double ToDouble ( std::string strVal )
{
	std::stringstream ss;
	double nVal;
	
	ss << strVal;
	ss >> nVal;
		
	return nVal;
}