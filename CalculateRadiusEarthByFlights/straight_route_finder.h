#ifndef STRAIGHT_ROUTE_FINDER_H
#define STRAIGHT_ROUTE_FINDER_H
// recordListから直線航路を走っているレコードを探す
#include "record_list.h"

#include <stddef.h>

// 直線区間を表すインデックスペア
typedef struct {
    size_t start;  // 直線区間の最初のレコード index
    size_t end;    // 直線区間の最後のレコード index
} Segment;


Segment* findStraightSegments(
    const RecordList* list,
    double threshold_deg,
    size_t min_records,
    size_t* out_count);


#endif // STRAIGHT_ROUTE_FINDER_H
