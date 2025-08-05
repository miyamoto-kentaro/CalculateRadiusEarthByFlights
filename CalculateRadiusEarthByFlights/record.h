#ifndef RECORD_H
#define RECORD_H

#include <time.h>

// 生データを格納する構造体
typedef struct {
    time_t   unixTime;   // Unix time（秒）
    double   longitude;  // 経度（度）
    double   latitude;   // 緯度（度）
    double   altitude;   // 高度（ft）
    double   speed;      // 速度（kts）
    double   direction;  // 方位（度、北=0→時計回り）
} Record;

// ── コンストラクタ ──
void Record_init(
    Record* r,
    time_t unixTime,
    double longitude,
    double latitude,
    double altitude,
    double speed,
    double direction);

#endif // RECORD_H
