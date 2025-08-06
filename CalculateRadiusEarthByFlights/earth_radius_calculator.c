#include "earth_radius_calculator.h"
#include <math.h>
#include <stdio.h>
#include <time.h>
#include "constants.h"
#include "record.h"

double calculateEarthRadius(
	const Record* records,
	size_t count
) {

	if (count < 2) {
		fprintf(stderr, "Error: Not enough records to calculate radius.\n");
		return 0.0; 
	}

	const Record* firstRecord = &records[0];
	const Record* lastRecord = &records[count - 1];

	double totalDistance = 0.0;
	for (size_t i = 0; i < count - 1; i++) {
		const Record* r1 = &records[i];
		const Record* r2 = &records[i + 1];

		double derectionRad1 = DEG_TO_RAD(r1->direction);
		double derectionRad2 = DEG_TO_RAD(r2->direction);
		double speed1 = KTS_TO_MPS(r1->speed);
		double speed2 = KTS_TO_MPS(r2->speed);
		double timeDiff = difftime(r2->unixTime, r1->unixTime);

		double distance = (speed1 + speed2) / 2.0 * timeDiff; 
		totalDistance += distance;
	}

	double theta1 = Latitude_TO_THETA(firstRecord->latitude);
	double phi1 = Longitude_TO_PHI(firstRecord->longitude);
	double theta2 = Latitude_TO_THETA(lastRecord->latitude);
	double phi2 = Longitude_TO_PHI(lastRecord->longitude);

	double h1 = FT_TO_M(firstRecord->altitude); 
	double h2 = FT_TO_M(lastRecord->altitude); 
	
	double γ = sin(theta1) * sin(theta2) * cos(phi1 - phi2) + cos(theta1) * cos(theta2);

	double coff_a = 2.0 * (1.0 - γ);
	double coff_b = 2.0 * (h1 + h2) * (1.0 - γ);
	double d2 = totalDistance * totalDistance;
	double coff_c = h1 * h1 + h2 * h2 - 2.0 * h1 * h2 * γ - d2;

	
	double discriminant = coff_b * coff_b - 4.0 * coff_a * coff_c;
	if (discriminant < 0) {
		fprintf(stderr, "Error: Negative discriminant, no real solution.\n");
		return 0.0; 
	}
	
	double sqrt_discriminant = sqrt(discriminant);
	
	double R1 = (-coff_b + sqrt_discriminant) / (2.0 * coff_a);
	double R2 = (-coff_b - sqrt_discriminant) / (2.0 * coff_a);
	
	if (R1 > 0.0 && R2 > 0.0) {
		return (R1 < R2) ? R1 : R2; 
	} else if (R1 > 0.0) {
		return R1; 
	} else if (R2 > 0.0) {
		return R2; 
	}

	return 0.0;
}
