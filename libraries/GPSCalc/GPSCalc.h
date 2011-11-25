#ifndef GPSCalc_H
#define GPSCalc_H
   
#include <WProgram.h> //It is very important to remember this!
       
class GPSCalc {
private:
	int32_t getCos65536(int degrees);
	// Fast arctan2
	// http://www.dspguru.com/dsp/tricks/function-approximation
	double arctan2(double y, double x);
	double d_abs(double x);
	double degreesToRadians(double x);
public:
	GPSCalc();
	~GPSCalc();
	// from http://www.informit.com/guides/content.aspx?g=dotnet&seqNum=513
	// flat earth approximation
	int getCourse(long pt1lat, long pt1long, long pt2lat, long pt2long);
	int getDirectionDiff(long fromlat, long fromlong, long tolat, long tolong, int currentcourse);
	int getDistance(long pt1lat, long pt1long, long pt2lat, long pt2long);
	boolean isWithin(long fromlat, long fromlong, long tolat, long tolong, int toradius);
};
#endif

