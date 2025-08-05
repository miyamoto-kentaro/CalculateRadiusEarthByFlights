#ifndef CONSTANTS_H
#define CONSTANTS_H

// ── マクロ定義 ──
#define PI 3.14159265358979323846  // 円周率
#define DEG_TO_RAD(deg) ((deg) * PI / 180.0)     // 度→ラジアン
#define FT_TO_M(ft) ((ft) * 0.3048)           // フィート→メートル
#define KTS_TO_MPS(kts) ((kts) * 0.514444)   // ノット→メートル毎秒

// 経度→phi(0<phi<2PI) グリニッジ天文台で 0PI
#define Longitude_TO_PHI(longitude) ((longitude) * PI / 180.0)

// 緯度→phi(0<phi<PI) 赤道で PI/2
#define Latitude_TO_THETA(latitude) (PI/2 - (latitude) * PI / 180.0)

#define EARTH_RADIUS_M 6371000.0  // 正解の地球の半径（メートル）


#endif // CONSTANTS_H
