#include <GPSCalc.h>

GPSCalc gpsCalc;

void setup() {
  // Karlsruhe middle - 49.008085,8.403756
  // Karlsruhe park - 48.99779,8.400464
  // Distance should be 1168 meters, course 195 degrees.
  // Coords are multiplied with 100000 like in TinyGPS lib.
  long pt1_lat = 4900808;
  long pt1_lon = 840375;
  long pt2_lat = 4899779;
  long pt2_lon = 840046;
  
  Serial.begin(115200);
  
  Serial.print("Distance: ");
  Serial.println(gpsCalc.getDistance(pt1_lat, pt1_lon, pt2_lat, pt2_lon));

  Serial.print("Target within 50m?: ");
  Serial.println(gpsCalc.isWithin(pt1_lat, pt1_lon, pt2_lat, pt2_lon, 50) ? "true" : "false");

  Serial.print("Target within 2km?: ");
  Serial.println(gpsCalc.isWithin(pt1_lat, pt1_lon, pt2_lat, pt2_lon, 2000) ? "true" : "false");

  Serial.print("Course: ");
  Serial.println(gpsCalc.getCourse(pt1_lat, pt1_lon, pt2_lat, pt2_lon));
  
  Serial.print("Course correction for course 150: ");
  Serial.println(gpsCalc.getDirectionDiff(pt1_lat, pt1_lon, pt2_lat, pt2_lon, 150));

  Serial.print("Course correction for course 2: ");
  Serial.println(gpsCalc.getDirectionDiff(pt1_lat, pt1_lon, pt2_lat, pt2_lon, 2));
}

void loop() {
}
