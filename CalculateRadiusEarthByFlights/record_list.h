// record_list.h
// c��list���Ȃ����ߎ��O�Ŏ���
#ifndef RECORD_LIST_H
#define RECORD_LIST_H

#include "record.h"

// Record �̓��I�z��
typedef struct {
    Record* items;     // �v�f�z��
    size_t  size;      // ���݂̗v�f��
    size_t  capacity;  // �m�ۍςݗe��
} RecordList;

// �������i��̃��X�g�ɂ���j
void RecordList_init(RecordList* list);

// ����i�g���I�������Ăԁj
void RecordList_free(RecordList* list);

// �v�f�ǉ��i�����ŗe�ʂ�����Ȃ���Ύ����g���j
void RecordList_append(RecordList* list, const Record* r);

// CSV �t�@�C�����烍�[�h���ă��X�g�ɋl�߂�
//   filename: CSV �t�@�C����
//   list: �������ς݂� RecordList
//   �߂�l: 0=����, -1=�G���[
int RecordList_loadFromCSV(RecordList* list, const char* filename);

#endif // RECORD_LIST_H