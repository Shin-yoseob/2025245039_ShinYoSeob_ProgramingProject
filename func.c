#include <stdio.h>
#include <math.h>
#include "header.h"

//입력받은 기기와 배터리 용량을 저장하는 함수 
void BetteryCapacity(name* arr, int mah, char machine_name) {
	strcpy(arr->name, machine_name);
	arr->mah = mah;
}

//배터리의 수명을 계산주는 함수
void BetteryLifeTime(name* arr,float 배터리용량, int 사용일수) {
	int first_fulltime = 0;		//초기 배터리 최대 사용가능 시간
	int pre_fulltime = 0;		//현재 배터리 최대 사용가능 시간

	first_fulltime = (배터리용량 / 1000) * 3.7 / 10;	//소비전력 W의 평균적인 값을 10으로 설정
	pre_fulltime = first_fulltime * (1 - 0.00275 * sqrt(사용일수));	//감쇠계수 K는 일반적으로 0.0005 ~ 0.005이므로 그 중간으로 설정
	

	arr->full_time = pre_fulltime;
}

//배터리 사용량 감쇠율을 계산하는 함수
void minus_bettery(name* arr, int cycle) {
	int bet_decline = 0;	//배터리 감쇠율 저장함수 
	bet_decline = 100 * (1 - 0.00275 * sqrt(cycle));

	arr->minus = bet_decline;
}

//배터리 1퍼센트가 소모되는 시간
float Spend_per_one(int mah) {
	float Wh = mah / 1000.0 * 3.7;		//배터리 단위를 미리암페어에서 와트로 전환

	float per_one = (Wh / 2.0) / 100.0;		//1퍼센트 감소하는데 걸리는 시간(대략적인 값들로 계산) 
											//2로 나눈 이유는 2W의 부하가 기기에 걸린다고 가정
	return per_one;
}

//현재 배터리 잔여량
float remain_Bettery(name* arr, float spend_one, float spend_today) {
	arr->remain = 100.0 - spend_today / spend_one;

	return 100.0 - spend_today / spend_one;
}

//현재 배터리가 방전될 때까지 사용할 수 있는 시간
void LastingTime(float remain, float spend_one) {
	printf("현재 배터리 사용가능 시간: %f", remain / spend_one);
}

//배터리가 100퍼센트일 때, 방전까지 사용할 수 있는 값을 60분의 단위로 변환하는 함수
int FullTime() {

}

