
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
    (void)notification;
	ReleaseZipCodes();
}

#pragma mark Button Controllers

/*
 When the user clicks on the calculate button, the function has to evaluate
 whether or not we are using Latitude and Longitude or Zip codes.
 */
- (IBAction)calculate:(id)sender 
{
    (void)sender;
	Angle lat1 = 0.0;
	Angle lon1 = 0.0;
	Angle lat2 = 0.0;
	Angle lon2 = 0.0;
	
	Angle distance = 0.0;
	
	if ( [chkUseLatLon state] )
	{
		// We are using Latitude and Longitude
		lat1 = [txtLat1 doubleValue];
		lon1 = [txtLon1 doubleValue];
		lat2 = [txtLat2 doubleValue];
		lon2 = [txtLon2 doubleValue];
		
		distance = CalculateDistance(lat1, lon1, lat2, lon2);
	}
	else
	{
		// We are using zip codes instead
		int zip1 = [txtZip1 integerValue];
		int zip2 = [txtZip2 integerValue];
		
		// Get our Latitude and Longitude for each zip code
		LatLon ll1 = GetLatAndLon(zip1);
		LatLon ll2 = GetLatAndLon(zip2);
		
		lat1 = ll1.GetLat();
		lon1 = ll1.GetLon();
		lat2 = ll2.GetLat();
		lon2 = ll2.GetLon();
		
		distance = CalculateDistance(lat1, lon1, lat2, lon2);
	}
	
	if ( distance > 0.0 )
	{
		// Our value is returned to us in Kilometers, so it has to be converted to Miles if needed
		if ( [chkMiles state] )
			distance = distance/1.609344;
		
		[txtRDist setDoubleValue:distance];// Set our control value
	}
}

- (IBAction)clear:(id)sender 
{
    (void)sender;
    
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
    (void)sender;
    
    // Get the state of the button and toggle the otherbutton	
	if ( [chkKiloMeters state] )
		[chkMiles setState:NSOffState];
	else
		[chkMiles setState:NSOnState];
}

- (IBAction)checkMiles:(id)sender 
{
    (void)sender;
    
	if ( [chkMiles state] )
		[chkKiloMeters setState:NSOffState];    
	else
		[chkKiloMeters setState:NSOnState];
}

- (IBAction)checkUseLatLon:(id)sender;
{
    (void)sender;
    
	if ( [chkUseLatLon state] )
		[chkUseZip setState:NSOffState];    
	else
		[chkUseZip setState:NSOnState];
}

- (IBAction)checkUseZip:(id)sender;
{
    (void)sender;
    
	if ( [chkUseZip state] )
		[chkUseLatLon setState:NSOffState];    
	else
		[chkUseLatLon setState:NSOnState];
}


@end
