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
    // Unix time ��ێ�
    r->unixTime = unixTime;
    // ����ȊO�̏����Z�b�g
    r->longitude = longitude;
    r->latitude = latitude;
    r->altitude = altitude;
    r->speed = speed;
    r->direction = direction;
}
