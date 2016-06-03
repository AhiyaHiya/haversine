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

/* In order for us to use our Zip codes, Latitudes and Longitudes, we have to store 
	those values in a container variable. Since out interface uses Zip code for 
	calculating our distances, we are going to use a stl map to hold our values and 
	give use the ability to search by zip code. */
static map<int, LatLon> g_ZipCodes;

// Function for returning our Latitude and Longitude
LatLon GetLatAndLon(int nZipCode)
{
	// Find the zipcode
	map<int, LatLon>::iterator zipFound = g_ZipCodes.find(nZipCode);
	
	if(zipFound != g_ZipCodes.end())
		return (*zipFound).second;
	else
		return LatLon(0,0); // return zero if not found 
}

/* 
 Function for reading in our zip code table file.
 Returns 0 when no errors were encounted or a positive number when an error was found.
 */
int LoadZipCodes(string strPathToFile)
{
	// Make sure we have a path to work with
	if (strPathToFile.length() > 0)
	{
		char	cLine[1024] = {0x0};		// Character array to hold the contents of each line
		char	cFields[ 6 ][ 32 ] = {0x0};	// Multidimensional character array to hold each field found in a line
		FILE*	pF = NULL;					// File pointer
		
		// Attempt to open our file in read only mode
		pF = fopen(strPathToFile.c_str(),"r");
		
		// Check to see if there were any errors
		if (pF == NULL) 
		{
			/* When an error occurs while opening a file, you can get the description by 
				using the strerror function on the global errno number */
			printf ( "An error occurred while attempting to open our file: %s", strerror (errno) );
			return 1;
		}
		
		// If we got to this point, let's iterate over every line in our file and extract each field
		while( fgets ( cLine, sizeof(cLine), pF) !=0 )
		{
			/* 
			 Here strtok is used to first extract the field, then it is called 
			 recursively, with a NULL pointer, to get the remaining fields. */
			char*	pField = strtok(cLine, ",");
			int		nFld = 0;
			
			while( pField != 0)
			{
				strcpy(cFields[nFld], pField);
				++nFld;
                auto token = '\0';
                pField = std::strtok(&token, ",");
			}
			
			// Now that we got our fields, let's get our latitude, longitude and zipcode
			// First, convert our C strings to doubles
			LatLon sLL( ToDouble(cFields[2]), ToDouble(cFields[3]) );
			g_ZipCodes[ atoi(cFields[0]) ] = sLL;
		}
		
		// Close our file
		fclose (pF);
		
		// If we got to this point, we are error free!
		return 0;
	}
	else
		return 1;
}

// Function to clean up after ourselves
void ReleaseZipCodes()
{
	if ( !g_ZipCodes.empty() )
		g_ZipCodes.clear();
}

// Function to convert string to double
double ToDouble ( string strVal )
{
	std::stringstream ss;
	double nVal;
	
	ss << strVal;
	ss >> nVal;
		
	return nVal;
}