#include <stdio.h>
#include <math.h>
#include "record.h"
#include "record_list.h"
#include "straight_route_finder.h"
#include "earth_radius_calculator.h"

int main(void) {
	// ���R�[�h���X�g�̏�����
    RecordList recodeList;
    RecordList_init(&recodeList);

    if (RecordList_loadFromCSV(&recodeList, "C:\\Users\\�{�{�����Y\\Downloads\\20230727_HD43_HND_CTS.csv") != 0) {
        fprintf(stderr, "Failed to load flight data from CSV.\n");
        RecordList_free(&recodeList);
		return 1;
	}

	// �����q�H��T��
	size_t segmentCount = 0;
	// �p�x��臒l��10�x�A�ŏ����R�[�h����5�ɐݒ�
	// ������Ԃ̃��X�g���擾
	// segments�͓��I�Ɋm�ۂ����̂ŁA��ŉ������K�v������
	Segment* segments = findStraightSegments(&recodeList, 10.0, 5, &segmentCount);

	for (size_t i = 0; i < segmentCount; i++) {
		Segment seg = segments[i];
		printf("Segment %zu: start=%zu, end=%zu\n", i, seg.start, seg.end);
		// ������Ԃ̃��R�[�h���擾
		const Record* startRecord = &recodeList.items[seg.start];

		double calculatedRadius = calculateEarthRadius(
			&recodeList.items[seg.start],
			seg.end - seg.start + 1
		);
		printf("���̃Z�O�����g�̒n�����a %zu: %.2f m\n", i, calculatedRadius);
	}

    // �J��
	RecordList_free(&recodeList);
    return 0;
}
