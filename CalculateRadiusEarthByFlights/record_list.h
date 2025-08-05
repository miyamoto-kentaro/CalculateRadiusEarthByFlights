// record_list.h
// cにlistがないため自前で実装
#ifndef RECORD_LIST_H
#define RECORD_LIST_H

#include "record.h"

// Record の動的配列
typedef struct {
    Record* items;     // 要素配列
    size_t  size;      // 現在の要素数
    size_t  capacity;  // 確保済み容量
} RecordList;

// 初期化（空のリストにする）
void RecordList_init(RecordList* list);

// 解放（使い終わったら呼ぶ）
void RecordList_free(RecordList* list);

// 要素追加（内部で容量が足りなければ自動拡張）
void RecordList_append(RecordList* list, const Record* r);

// CSV ファイルからロードしてリストに詰める
//   filename: CSV ファイル名
//   list: 初期化済みの RecordList
//   戻り値: 0=成功, -1=エラー
int RecordList_loadFromCSV(RecordList* list, const char* filename);

#endif // RECORD_LIST_H