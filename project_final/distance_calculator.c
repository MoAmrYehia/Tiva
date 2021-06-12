/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::                                                                         :*/
/*::  This function calculates the distance between two points (given the    :*/
/*::  latitude/longitude). It is being used to calculate                     :*/
/*::  the distance between two locations using GPS Module                    :*/
/*::                                                                         :*/
/*::  Definitions:                                                           :*/
/*::    South latitudes are negative, east longitudes are positive           :*/
/*::                                                                         :*/
/*::  Passed to function:                                                    :*/
/*::    lat1, lon1 = Latitude and Longitude of point 1 (in decimal degrees)  :*/
/*::    lat2, lon2 = Latitude and Longitude of point 2 (in decimal degrees)  :*/
/*::                                                                         :*/ 
/*:: Aouther: Mohamed Amr                                                    :*/
/*::                                                                         :*/
/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/




/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  Function Structure                                            :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

#include "distance_calculator.h"
#include "test.h"
#include <math.h>


double distance(double lat1, double lon1, double lat2, double lon2) {
    double theta, dist;
	char *arr;
	lat1 = sub_double(lat1);
	lat2 = sub_double(lat2);
	lon1 = sub_double(lon1);
	lon2 = sub_double(lon2);
	/*sprintf(arr,"%f",lat1);
	Print_String(arr);
	sprintf(arr,"%f",lon1);
	Print_String(arr);
	sprintf(arr,"%f",lat2);
	Print_String(arr);
	sprintf(arr,"%f",lon2);
	Print_String(arr);*/
    if ((lat1 == lat2) && (lon1 == lon2)) {
        return 0;
    }
    else {
        theta = lon1 - lon2;
        dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
        dist = acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515 * 1.609344 * 1000; // This line converts distant from the degrees to metric unit
        return (dist);
    }
}


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts decimal degrees to radians             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

double deg2rad(double deg) {
    return (deg * pi / 180);
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts radians to decimal degrees             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

double rad2deg(double rad) {
    return (rad * 180 / pi);
}

double sub_double(double cordanate) {
    return (floorf(cordanate*10000)/10000);
}

double velocity(double min1,double min2,double sec1,double sec2,double distance)  //velocity in m/s
{
	return distance/((sec2-sec1)+(min2-min1)*60);
	
}


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This main function is just for testing                        :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/* int main() {

    double lat1 = 30.0444 ; // Cairo Location
    double lon1 = 31.2357;

    double lat2 = 31.2001; // Alex Location 
    double lon2 = 29.9187;

    double distance_meter = distance(lat1, lon1, lat2, lon2);

    printf("Total distance is: %lf \n", distance_meter);
    return 0;
} */

