#ifndef STRAIGHT_ROUTE_FINDER_H
#define STRAIGHT_ROUTE_FINDER_H
// recordList���璼���q�H�𑖂��Ă��郌�R�[�h��T��
#include "record_list.h"

#include <stddef.h>

// ������Ԃ�\���C���f�b�N�X�y�A
typedef struct {
    size_t start;  // ������Ԃ̍ŏ��̃��R�[�h index
    size_t end;    // ������Ԃ̍Ō�̃��R�[�h index
} Segment;


Segment* findStraightSegments(
    const RecordList* list,
    double threshold_deg,
    size_t min_records,
    size_t* out_count);


#endif // STRAIGHT_ROUTE_FINDER_H
