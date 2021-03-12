#import <Cocoa/Cocoa.h>
#import "zipcodes.h"

@interface WndController : NSObject
{
    zipcodes_t _zipCodeMap;
    
    IBOutlet id chkKiloMeters;
    IBOutlet id chkMiles;
    IBOutlet id chkUseLatLon;
    IBOutlet id chkUseZip;
    IBOutlet id txtLat1;
    IBOutlet id txtLat2;
    IBOutlet id txtLon1;
    IBOutlet id txtLon2;
    IBOutlet id txtRDist;
    IBOutlet id txtZip1;
    IBOutlet id txtZip2;
}
- (IBAction)calculate:(id)sender;
- (IBAction)clear:(id)sender;

- (IBAction)checkKilometers:(id)sender;
- (IBAction)checkMiles:(id)sender;

- (IBAction)checkUseLatLon:(id)sender;
- (IBAction)checkUseZip:(id)sender;

@end
