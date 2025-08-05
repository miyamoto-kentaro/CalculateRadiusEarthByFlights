#include <stdio.h>
#include <math.h>
#include "record.h"
#include "record_list.h"
#include "straight_route_finder.h"
#include "earth_radius_calculator.h"

int main(void) {
	// レコードリストの初期化
    RecordList recodeList;
    RecordList_init(&recodeList);

    if (RecordList_loadFromCSV(&recodeList, "C:\\Users\\宮本健太郎\\Downloads\\20230727_HD43_HND_CTS.csv") != 0) {
        fprintf(stderr, "Failed to load flight data from CSV.\n");
        RecordList_free(&recodeList);
		return 1;
	}

	// 直線航路を探す
	size_t segmentCount = 0;
	// 角度の閾値を10度、最小レコード数を5に設定
	// 直線区間のリストを取得
	// segmentsは動的に確保されるので、後で解放する必要がある
	Segment* segments = findStraightSegments(&recodeList, 10.0, 5, &segmentCount);

	for (size_t i = 0; i < segmentCount; i++) {
		Segment seg = segments[i];
		printf("Segment %zu: start=%zu, end=%zu\n", i, seg.start, seg.end);
		// 直線区間のレコードを取得
		const Record* startRecord = &recodeList.items[seg.start];

		double calculatedRadius = calculateEarthRadius(
			&recodeList.items[seg.start],
			seg.end - seg.start + 1
		);
		printf("このセグメントの地球半径 %zu: %.2f m\n", i, calculatedRadius);
	}

    // 開放
	RecordList_free(&recodeList);
    return 0;
}
