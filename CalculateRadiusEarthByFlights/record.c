#include "record.h"
#include <stdlib.h>
#include <string.h>

void Record_init(Record* r,
    time_t unixTime,
    double longitude,
    double latitude,
    double altitude,
    double speed,
    double direction)
{
    // Unix time を保持
    r->unixTime = unixTime;
    // それ以外の情報をセット
    r->longitude = longitude;
    r->latitude = latitude;
    r->altitude = altitude;
    r->speed = speed;
    r->direction = direction;
}
