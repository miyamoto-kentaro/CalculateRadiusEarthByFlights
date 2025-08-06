// straight_segments.c
#include "straight_route_finder.h"
#include <stdlib.h>
#include <math.h>

static double bearing_diff(double a, double b) {
    double d = fabs(a - b);
    return (d > 180.0) ? 360.0 - d : d;
}

Segment* findStraightSegments(
    const RecordList* list,
    double threshold_deg,
    size_t min_records,
    size_t* out_count)
{
    *out_count = 0;
    size_t n = list->size;
    if (n < min_records) {
        return NULL;
    }

    size_t cap = 16;
    Segment* segments = malloc(sizeof * segments * cap);
    if (!segments) return NULL;

    long seg_start = -1;
    size_t seg_len = 1;

    for (size_t i = 0; i + 1 < n; ++i) {
        double d1 = list->items[i].direction;
        double d2 = list->items[i + 1].direction;
        double diff = bearing_diff(d1, d2);

        if (diff <= threshold_deg) {
            if (seg_start < 0) {
                seg_start = (long)i;
                seg_len = 2;
            }
            else {
                seg_len++;
            }
        }
        else {
            if (seg_start >= 0 && seg_len >= min_records) {
                if (*out_count >= cap) {
                    cap *= 2;
                    segments = realloc(segments, sizeof * segments * cap);
                    if (!segments) return NULL;
                }
                segments[*out_count].start = (size_t)seg_start;
                segments[*out_count].end = (size_t)(seg_start + seg_len - 1);
                (*out_count)++;
            }
            seg_start = -1;
            seg_len = 1;
        }
    }

    if (seg_start >= 0 && seg_len >= min_records) {
        if (*out_count >= cap) {
            cap += 1;
            segments = realloc(segments, sizeof(Segment) * cap);
            if (!segments) return NULL;
        }
        segments[*out_count].start = (size_t)seg_start;
        segments[*out_count].end = (size_t)(seg_start + seg_len - 1);
        (*out_count)++;
    }

    return segments;
}