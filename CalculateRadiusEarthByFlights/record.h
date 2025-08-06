#ifndef RECORD_H
#define RECORD_H

#include <time.h>

typedef struct {
    time_t   unixTime;
    double   longitude;
    double   latitude;
    double   altitude;
    double   speed;
    double   direction;
} Record;


void Record_init(
    Record* r,
    time_t unixTime,
    double longitude,
    double latitude,
    double altitude,
    double speed,
    double direction);

#endif // RECORD_H
