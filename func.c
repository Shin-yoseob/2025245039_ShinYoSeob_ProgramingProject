#include <stdio.h>
#include <math.h>
#include "header.h"
#include <string.h>

//입력받은 기기와 배터리 용량을 저장하는 함수 
void BetteryCapacity(name arr[],int list_num, int mah, char machine_name[], char weather[], char microdust[], char humidity[]) {
	//각 구조체 변수안에 메인함수에서 입력받은 값들을 저장하는 과정
	strcpy(arr[list_num].name, machine_name);
	strcpy(arr[list_num].weather, weather);
	strcpy(arr[list_num].microdust, microdust);
	strcpy(arr[list_num].humidity, humidity);
	arr[list_num].mah = mah;
}

//입력받은 날씨에 따라서 배터리 사용시간을 조정하는 함수
float weather_bettery(name arr[],int list_num, float pre_fulltime) {
	if (strcmp(arr[list_num].weather, "더움") == 0) {
		//더운 날씨, 배터리 사용시간 11%감소
		return pre_fulltime * 0.89;
	}
	else if (strcmp(arr[list_num].weather, "추움") == 0) {
		//추운 날씨, 배터리 사용시간 20%감소
		return pre_fulltime * 0.80;
	}
	else if (strcmp(arr[list_num].weather, "온화") == 0) {
		//온화한 날씨, 배터리 사용시간 영향 X
		return pre_fulltime;
	}
}

//미세먼지 상태에 따라 배터리 사용시간을 조정하는 함수
//미세먼지는 긴 기간동안의 누적이 영향을 주기 때문에 사이클 나누기 365.0f를 하게 되었음.
float microdust_bettery(name arr[], int list_num, float pre_fulltime, int cycle) {
	if (strcmp(arr[list_num].weather, "나쁨") == 0) {
		//미세먼지 나쁨, 연간 배터리 사용시간 3%감소
		return pre_fulltime * (0.97 * (cycle / 365.0f));
	}
	else if (strcmp(arr[list_num].weather, "보통") == 0) {
		//미세먼지 보통, 연간 배터리 사용시간 2%감소
		return pre_fulltime * (0.98 * (cycle / 365.0f));
	}
	else if (strcmp(arr[list_num].weather, "좋음") == 0) {
		//미세먼지 좋음, 배터리 사용시간 영향 X
		return pre_fulltime;
	}
}

float humidity_bettery(name arr[], int list_num, float pre_fulltime, int cycle) {
	if (strcmp(arr[list_num].humidity, "습함") == 0) {
		//습한 장소, 연간 배터리 사용시간 15%감소
		return pre_fulltime * (0.85 * (cycle / 365.0f));
	}
	else if (strcmp(arr[list_num].humidity, "안습함") == 0) {
		//안습한 장소, 연간 배터리 사용시간 감소 X
		return pre_fulltime;
	}
}


//배터리의 수명을 계산주는 함수
void BetteryLifeTime(name arr[], int list_num, float mah, int cycle) {
	float first_fulltime = 0;	
	//초기 배터리 최대 사용가능 시간
	float pre_fulltime = 0;											//현재 배터리 최대 사용가능 시간

	first_fulltime = (mah / 1000) * 3.7f / 2;						//소비전력 W의 평균적인 값을 2으로 설정
	pre_fulltime = first_fulltime * (1 - 0.00275 * sqrt(cycle));	//감쇠계수 K는 일반적으로 0.0005 ~ 0.005이므로 그 중간으로 설정


	pre_fulltime = weather_bettery(arr, list_num, pre_fulltime);			//날씨 요인 적용
	
	pre_fulltime = microdust_bettery(arr, list_num, pre_fulltime, cycle);	//미세먼지 요인 적용

	pre_fulltime = humidity_bettery(arr, list_num, pre_fulltime, cycle);	//습도 요인 적용


	arr[list_num].full_time = pre_fulltime;
}

//배터리 사용량 감쇠율을 계산하는 함수
void minus_bettery(name arr[], int list_num, int cycle) {
	int bet_decline = 0;											//배터리 감쇠율 저장함수 
	bet_decline = 100 * (1 - 0.00275 * sqrt(cycle));

	arr[list_num].minus = bet_decline;
}

//배터리 1퍼센트가 소모되는 시간
float Spend_per_one(name arr[], int list_num, int mah, int cycle) {
	float Wh = (mah / 1000.0f) * 3.7f;								//배터리 단위를 미리암페어에서 와트로 전환
	float per_one = 60.0f * ((Wh / 2.0f) / 100.0f);					//1퍼센트 감소하는데 걸리는 시간(대략적인 값들로 계산) 
																	//2로 나눈 이유는 2W의 부하가 기기에 걸린다고 가정
																	
	//per_one의 값을 분모로, 분자의 값을 오늘 하루 사용한 시간으로 하므로 분모값이 클수록 
	// 값이 감소하기 때문에 11퍼센트 감소시, 1.11을 곱함

	//날씨가 더움일 때, 소모시간 11퍼센트 감소
	if (strcmp(arr[list_num].weather, "더움") == 0) {
		per_one *= 1.11f;
	}
	//날씨가 추움을 때, 소모시간 20퍼센트 감소
	else if (strcmp(arr[list_num].weather, "추움") == 0) {
		per_one *= 1.2f;
	}

	//미세먼지 나쁨일 때, 연간 3퍼센트의 사용시간 감소
	if (strcmp(arr[list_num].microdust, "나쁨") == 0) {
		per_one = per_one * 1.03f * (cycle / 365.0f);
	}
	//미세먼지 나쁨일 때, 연간 2퍼센트의 사용시간 감소
	else if (strcmp(arr[list_num].weather, "보통") == 0) {
		per_one = per_one * 1.02f * (cycle / 365.0f);
	}

	//습도가 습할 때, 배터리 부식으로 연간 사용시간 15퍼센트 감소
	if (strcmp(arr[list_num].humidity, "습함") == 0) {
		per_one = per_one * 1.15f * (cycle / 365.0f);
	}
	return per_one;
}

//현재 배터리 잔여량
float remain_Bettery(name arr[], int list_num, float spend_one, float spend_today) {

	//오늘 사용시간 / 1퍼센트 감소에 걸리는 시간 = 현재 배터리 소모량
	float used_percent = spend_today / spend_one;
	float remain = 100.0f - used_percent;

	//잔여량이 0퍼센트보다 작거나 같으면 0으로 초기화
	if (remain <= 0.0f) {
		remain = 0.0f;
	}
	
	//값 구조체에 저장
	arr[list_num].remain = remain;
	
	//값을 반환
	return remain;
}

//현재 배터리가 방전될 때까지 사용할 수 있는 시간
void LastingTime(float remain, float spend_one) {
	//현재 잔여량 / 1퍼센트 소모까지 걸리는 시간 = 현재 기기 최대 사용시간
	float pure_time = remain / spend_one;
	int time = 0, min = 0;
}

//배터리가 100퍼센트일 때, 방전까지 사용할 수 있는 값을 60분의 단위로 변환하여 출력하는 함수
void Time_revise(name arr[],int list_num) {
	//실수형으로 저장된 시간을 우리가 해석하기에 편한 시간 / 분으로 변환
	int time = arr[list_num].full_time / 1;
	int min = 60 * (arr[list_num].full_time - time);

	printf("100%에서 최대사용할 수 있는 시간: 약 %d시간 %d분\n", time, min);
}


//특정기기의 정보찾아 출력
void search_device(name arr[], char name[], int list_num) {
	for (int i = 0; i < list_num; i++) {
		//반복문과 strcmp함수를 통해 구조체에서 정보를 찾아 출력
		if (strcmp(arr[i].name, name) == 0) {
			printf("==============================\n");
			printf("기기이름: %s\n", arr[i].name);
			printf("배터리 감쇠율: %d%%\n", arr[i].minus);
			printf("현재 배터리 잔여량: 약 %.2f%%\n", arr[i].remain);
			Time_revise(arr, i);
			printf("==============================\n");
			printf("\n");
			break;
		}
		if (strcmp(arr[i].name, name) != 0) {
			printf("입력하신 이름의 기기가 존재하지 않거나 잘못 입력하셨습니다.\n");
			printf("\n");
		}
	}
}

//모든 기기의 정보를 기록한 순서대로 출력
void printing_list(name arr[], int list_num) {
	printf("\n");
	for (int i = 0; i < list_num; i++) {
		printf("==============================\n");
		printf("기기이름: %s\n", arr[i].name);
		printf("배터리 감쇠율: %d\n", arr[i].minus);
		printf("현재 배터리 잔여량: %.2f%%\n", arr[i].remain);
		Time_revise(arr, i);
		printf("==============================\n");
		printf("\n");
	}
}
