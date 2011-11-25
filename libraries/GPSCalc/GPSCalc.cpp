#include "GPSCalc.h" //include the declaration for this class
 
#define PI 3.141592653589793
      
GPSCalc::GPSCalc(){
}
       
//<<destructor>>
GPSCalc::~GPSCalc(){/*nothing to destruct*/}
       

// from http://www.informit.com/guides/content.aspx?g=dotnet&seqNum=513
// flat earth approximation
int GPSCalc::getCourse(long pt1lat, long pt1long, long pt2lat, long pt2long) {
  double course;
  int32_t dlat = pt2lat - pt1lat;
  int32_t dlon = pt2long - pt1long;
  int32_t distanceNorth = (dlat * 65536);
  int32_t distanceEast = (dlon * getCos65536(pt1lat / 100000));
  // compute the course
  course = arctan2(distanceEast / 100000.0, distanceNorth / 100000.0);
  course = course * 180.0 / PI;
  if (course < 0)
    course += 360;
  while (course > 360) {
    course -= 360;
  }
  return (int)course;
}

int GPSCalc::getDirectionDiff(long fromlat, long fromlong, long tolat, long tolong, int currentcourse) {
  int diffDirection;

  diffDirection  =  getCourse(fromlat, fromlong, tolat, tolong) - currentcourse;
  if (diffDirection > 180) {
    diffDirection = diffDirection - 360;
  } 
  else if (diffDirection < -180) {
    diffDirection = diffDirection + 360;
  }
  return diffDirection;
}

int GPSCalc::getDistance(long pt1lat, long pt1long, long pt2lat, long pt2long) {
  double dist_radians;
  long dist_meters; 
  double d1lat = degreesToRadians((double)pt1lat / 100000.0);
  double d1lon = degreesToRadians((double)pt1long / 100000.0);
  double d2lat = degreesToRadians((double)pt2lat / 100000.0);
  double d2lon = degreesToRadians((double)pt2long / 100000.0);

  // compute latitude and longitude differences
  double dlat = d2lat - d1lat;
  double dlon = d2lon - d1lon;

  double distanceNorth = dlat;
  double distanceEast = dlon * cos(d1lat);

  // compute the distance in radians
  dist_radians = sqrt(distanceNorth * distanceNorth + distanceEast * distanceEast);


  dist_meters = dist_radians * 180.0 * 60.0 * 1852.0 / PI;


  return (int) dist_meters;
}

boolean GPSCalc::isWithin(long fromlat, long fromlong, long tolat, long tolong, int toradius) {
  return (getDistance(fromlat, fromlong, tolat, tolong) - toradius) <= 0;
}

// ----------- private stuff --------------------------

double GPSCalc::degreesToRadians(double degrees) {
  return degrees * PI / 180.0;
}

int32_t GPSCalc::getCos65536(int degrees)
{
  uint16_t cosIntTab[] = { 
    65536, 65526, 65496, 65446, 65376, 65286, 65176, 65047,
    64898, 64729, 64540, 64331, 64103, 63856, 63589, 63302, 62997,
    62672, 62328, 61965, 61583, 61183, 60763, 60326, 59870, 59395,
    58903, 58393, 57864, 57319, 56755, 56175, 55577, 54963, 54331,
    53683, 53019, 52339, 51643, 50931, 50203, 49460, 48702, 47929,
    47142, 46340, 45525, 44695, 43852, 42995, 42125, 41243, 40347,
    39440, 38521, 37589, 36647, 35693, 34728, 33753, 32768, 31772,
    30767, 29752, 28729, 27696, 26655, 25606, 24550, 23486, 22414,
    21336, 20251, 19160, 18064, 16961, 15854, 14742, 13625, 12504,
    11380, 10252, 9120, 7986, 6850, 5711, 4571, 3429, 2287, 1143, 0     };

  int quadrant = ((int) degrees) / 90;
  int index = 0;

  switch (quadrant) {
  case 0:
    index = (int) degrees;
    break;
  case 1:
    index = 180 - (int) degrees;
    break;
  case 2:
    index = (int) degrees - 180;
    break;
  case 3:
    index = 360 - (int) degrees;
    break;
  }
  if (quadrant > 0 && quadrant < 3) {
    return -cosIntTab[index];
  } 
  else {
    return cosIntTab[index];
  }
}

// Fast arctan2
// http://www.dspguru.com/dsp/tricks/function-approximation
double GPSCalc::arctan2(double y, double x)
{
  double coeff_1 = 0.7853981633974483;
  double coeff_2 = 3*coeff_1;
  double abs_y = d_abs(y)+1e-10;      // kludge to prevent 0/0 condition
  double angle;
  if (x>=0)
  {
    double r = (x - abs_y) / (x + abs_y);
    angle = coeff_1 - coeff_1 * r;
  }
  else
  {
    double r = (x + abs_y) / (abs_y - x);
    angle = coeff_2 - coeff_1 * r;
  }
  if (y < 0)
    return(-angle);     // negate if in quad III or IV
  else
    return(angle);
}

double GPSCalc::d_abs(double x)
{
  if(x>0) return x; 
  else return (-x);
}

