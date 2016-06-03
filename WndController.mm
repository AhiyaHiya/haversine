
#import "WndController.h"
#include "Harversine.h"
#include "ZipCodes.h"

#include <string>

using namespace std;


@implementation WndController

#pragma mark Initialization

/*
 This method is called once the nib has finish loadig. This message is sent out to any class that is derived from NSObject so that they have a chance to respond to this message.
 */
- (void)awakeFromNib
{	
	// Set the checkbox default to Miles
	[chkMiles setState:NSOnState];
	[chkKiloMeters setState:NSOffState];

	// Set the checkbox default to Option 1
	[chkUseLatLon setState:NSOnState];
	[chkUseZip setState:NSOffState];

	
	// Attempt to load our zip codes file
	string strFP = [[[NSBundle mainBundle] 
					 pathForResource:@"zips" ofType:@"csv" inDirectory:@""] 
					cStringUsingEncoding:NSUTF8StringEncoding];
	LoadZipCodes(strFP);
}

/*
 Make sure we clean up after ourselves and clean out our map!
 */
- (void)windowWillClose:(NSNotification *)notification
{
	ReleaseZipCodes();
}

#pragma mark Button Controllers

/*
 When the user clicks on the calculate button, the function has to evaluate
 whether or not we are using Latitude and Longitude or Zip codes.
 */
- (IBAction)calculate:(id)sender 
{
	double nLat1 = 0.0;
	double nLon1 = 0.0;
	double nLat2 = 0.0;
	double nLon2 = 0.0;
	
	double nDist = 0.0;
	
	if ( [chkUseLatLon state] )
	{
		// We are using Latitude and Longitude
		nLat1 = [txtLat1 doubleValue];
		nLon1 = [txtLon1 doubleValue];
		nLat2 = [txtLat2 doubleValue];
		nLon2 = [txtLon2 doubleValue];
		
		nDist = CalculateDistance(nLat1, nLon1, nLat2, nLon2);
	}
	else
	{
		// We are using zip codes instead
		int nZip1 = [txtZip1 integerValue];
		int nZip2 = [txtZip2 integerValue];
		
		// Get our Latitude and Longitude for each zip code
		LatLon sLL1 = GetLatAndLon(nZip1);
		LatLon sLL2 = GetLatAndLon(nZip2);
		
		nLat1 = sLL1.GetLat();
		nLon1 = sLL1.GetLon();
		nLat2 = sLL2.GetLat();
		nLon2 = sLL2.GetLon();
		
		nDist = CalculateDistance(nLat1, nLon1, nLat2, nLon2);
	}
	
	if ( nDist > 0.0 )
	{
		// Our value is returned to us in Kilometers, so it has to be converted to Miles if needed
		if ( [chkMiles state] )
			nDist = nDist/1.609344;
		
		[txtRDist setDoubleValue:nDist];// Set our control value
	}
}

- (IBAction)clear:(id)sender 
{
    [txtLat1 setStringValue:@""];
    [txtLat2 setStringValue:@""];
    [txtLon1 setStringValue:@""];
    [txtLon2 setStringValue:@""];
    [txtRDist setStringValue:@""];
    [txtZip1 setStringValue:@""];
    [txtZip2 setStringValue:@""];
}


#pragma mark UI Responders
/*
 This section is pretty cool. Here, we implement code that handles how the UI should behave when the user clicks in one field or sets the option checkboxes, etc.
 */

- (IBAction)checkKilometers:(id)sender 
{
    // Get the state of the button and toggle the otherbutton	
	if ( [chkKiloMeters state] )
		[chkMiles setState:NSOffState];
	else
		[chkMiles setState:NSOnState];
}

- (IBAction)checkMiles:(id)sender 
{
	if ( [chkMiles state] )
		[chkKiloMeters setState:NSOffState];    
	else
		[chkKiloMeters setState:NSOnState];
}

- (IBAction)checkUseLatLon:(id)sender;
{
	if ( [chkUseLatLon state] )
		[chkUseZip setState:NSOffState];    
	else
		[chkUseZip setState:NSOnState];
}

- (IBAction)checkUseZip:(id)sender;
{
	if ( [chkUseZip state] )
		[chkUseLatLon setState:NSOffState];    
	else
		[chkUseLatLon setState:NSOnState];
}


@end
