
#include "earth_radius_calculator.h"
#include <math.h>
#include <stdio.h>
#include <time.h>
#include "constants.h"
#include "record.h"

double calculateEarthRadius(
	const Record* records,
	size_t count
) {

	// まずspeedとdirectionを使って、最初のレコードと最後のレコードの位置を計算します。
	if (count < 2) {
		fprintf(stderr, "Error: Not enough records to calculate radius.\n");
		return 0.0; // レコードが2つ未満の場合は計算できない
	}

	// レコードの最初と最後の位置を取得
	const Record* firstRecord = &records[0];
	const Record* lastRecord = &records[count - 1];

	// 最初のレコードと最後のレコードの位置を計算
	double totalDistance = 0.0;
	for (size_t i = 0; i < count - 1; i++) {
		const Record* r1 = &records[i];
		const Record* r2 = &records[i + 1];

		double derectionRad1 = DEG_TO_RAD(r1->direction);
		double derectionRad2 = DEG_TO_RAD(r2->direction);
		double speed1 = KTS_TO_MPS(r1->speed);
		double speed2 = KTS_TO_MPS(r2->speed);
		double timeDiff = difftime(r2->unixTime, r1->unixTime);

		// 速度と時間差から移動距離を計算
		double distance = (speed1 + speed2) / 2.0 * timeDiff; // 平均速度での距離
		totalDistance += distance;
	}

	// 方程式を解くための係数を計算
	// 球座標系の距離を計算する式
	
	// 球座標の座標
	// A = (r1, θ1, φ1), B = (r2, θ2, φ2) 
	double theta1 = Latitude_TO_THETA(firstRecord->latitude);
	double phi1 = Longitude_TO_PHI(firstRecord->longitude);
	double theta2 = Latitude_TO_THETA(lastRecord->latitude);
	double phi2 = Longitude_TO_PHI(lastRecord->longitude);

	// ここでレコードは高度hを持っていて、緯度と経度を持っている。
	// r1 = h1 + R, r2 = h2 + R
	// このRは地球の半径で、h1, h2はそれぞれのレコードの高度。
	double h1 = FT_TO_M(firstRecord->altitude); // 高度をメートルに変換
	double h2 = FT_TO_M(lastRecord->altitude); // 高度をメートルに変換
	
	// 球座標におけるベクトルの長さは
	// d^2 = |A-B|^2
	// = r1^2 + r2^2 - 2 * r1 * r2 * γ
	// γ = sin(θ1) * sin(θ2) * cos(φ1 - φ2) + cos(θ1) * cos(θ2)
	double γ = sin(theta1) * sin(theta2) * cos(phi1 - phi2) + cos(theta1) * cos(theta2);

	// そのため、Rを求めるための方程式は次のようになる。
	// d^2 = (h1 + R)^2 + (h2 + R)^2 - 2 * (h1 + R) * (h2 + R) * γ
	// これをまとめて、
	// a * R^2 + b * R + c = 0
	// という形にする。
	// a = 2 * ( 1 - γ)
	double coff_a = 2.0 * (1.0 - γ);
	// b = 2* (h1 + h2) * (1 - γ)
	double coff_b = 2.0 * (h1 + h2) * (1.0 - γ);
	// c = h1^2 + h2^2 - 2 * h1 * h2 * γ - d^2
	double d2 = totalDistance * totalDistance; // 距離の二乗
	double coff_c = h1 * h1 + h2 * h2 - 2.0 * h1 * h2 * γ - d2;

	// これを解くために、判別式を計算する。
	double discriminant = coff_b * coff_b - 4.0 * coff_a * coff_c;
	if (discriminant < 0) {
		fprintf(stderr, "Error: Negative discriminant, no real solution.\n");
		return 0.0; // 判別式が負の場合は実数解がない
	}
	// 判別式が0以上の場合、解は2つある。
	double sqrt_discriminant = sqrt(discriminant);
	// 解の公式を使って、Rを求める。
	double R1 = (-coff_b + sqrt_discriminant) / (2.0 * coff_a);
	double R2 = (-coff_b - sqrt_discriminant) / (2.0 * coff_a);
	// R1とR2のうち、正の値を返す。
	if (R1 > 0.0 && R2 > 0.0) {
		return (R1 < R2) ? R1 : R2; // 小さい方を返す
	} else if (R1 > 0.0) {
		return R1; // R1が正ならそれを返す
	} else if (R2 > 0.0) {
		return R2; // R2が正ならそれを返す
	}

	return 0.0;
}
