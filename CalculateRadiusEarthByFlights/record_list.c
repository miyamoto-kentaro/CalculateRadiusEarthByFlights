#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record_list.h"
#include "constants.h"

void RecordList_init(RecordList* list) {
    list->items = NULL;
    list->size = 0;
    list->capacity = 0;
}

void RecordList_free(RecordList* list) {
    free(list->items);
    list->items = NULL;
    list->size = 0;
    list->capacity = 0;
}

void RecordList_append(RecordList* list, const Record* r) {
	// サイズが現在の容量以上なら拡張
    if (list->size >= list->capacity) {
        size_t newCap = (list->capacity == 0) ? 8 : list->capacity * 2;
        Record* tmp = (Record*)realloc(list->items, newCap * sizeof(Record));
        if (!tmp) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        list->items = tmp;
        list->capacity = newCap;
    }
	// 新しいレコードを追加
    list->items[list->size++] = *r;
}

// CSV ファイルからレコードリストにデータを読み込む関数
int RecordList_loadFromCSV(RecordList* list, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return -1;
    }

    char line[512];
    int lineNo = 0;
    bool foundHeader = false;

    // ヘッダー行を探す
    while (fgets(line, sizeof(line), fp)) {
        lineNo++;
        if (strncmp(line, "Unix Time", strlen("Unix Time")) == 0) {
            foundHeader = true;
            break;
        }
    }
    if (!foundHeader) {
        fprintf(stderr, "Error: 'Unix Time' header not found (lines read: %d)\n", lineNo);
        fclose(fp);
        return -1;
    }

    // データ部をパース
    while (fgets(line, sizeof(line), fp)) {
        // 空行スキップ
        if (line[0] == '\n' || line[0] == '\r') continue;

        Record r;
        long long unixTime_ll;
        int year_dummy;
        int month, day, hour, minute, second;
        double lon_deg, lat_deg, alt_ft, speed_kts, dir_deg;

        int n = sscanf(line,
            "%lld,%d,%d,%d,%d,%d,%d,%lf,%lf,%lf,%lf,%lf",
            &unixTime_ll,
            &year_dummy,
            &month,
            &day,
            &hour,
            &minute,
            &second,
            &lon_deg,
            &lat_deg,
            &alt_ft,
            &speed_kts,
            &dir_deg
        );
        // 12項目取得できなかったらスキップ
        if (n != 12) {
            fprintf(stderr, "Warning: malformed CSV line %d (got %d fields)\n", lineNo + 1, n);
            continue;
        }

        // 構造体にセット
        r.unixTime = (time_t)unixTime_ll;
        // 座標・速度・高度の変換
		r.longitude = lon_deg;
		r.latitude = lat_deg;
        r.altitude = alt_ft;
		r.speed = speed_kts;
		r.direction = dir_deg;



        RecordList_append(list, &r);
        lineNo++;
    }

    fclose(fp);
    return 0;
}