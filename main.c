#include "header.h"
#include <stdio.h>
#include <string.h>

int main() {	

	name arr[20];
	int list_num = 0;
	printf("최대 20가지 기기의 배터리 정보를 알 수 있는 프로그램.\n");
	printf("시간을 추정하는 것이므로 오차가 발생할 수 있음에 @주의@\n");

	while (1) {
		int switch_num = 0;
		int i, mah, cycle;
		char machine_name[50], search_name[20], weather[10], microdust[10], humidity[10];
		float spend_one, spend_today, remain;

		//프로그램 시작 가이드
		printf("------------------------------\n");
		printf("1 => 기기등록, 2 => 등록한 기기 검색, 3 => 전체 기기 정보 출력, 4 => 프로그램 종료\n");
		printf("원하는 동작의 번호를 입력: ");
		scanf("%d", &switch_num);
		printf("\n");

		switch (switch_num) {
		case 1:
			///////////////////////////////정보입력///////////////////////////////

			//기기이름 입력
			printf(" - 기기 이름을 입력:");
			scanf("%s", machine_name);

			//배터리 용량 정보 입력
			printf(" - 배터리의 용량을 입력(mah):");
			scanf("%d", &mah);

			//날씨와 온도를 고려한 배터리 사용률 적용시키기
			printf("더움: (28'C이상), 추움: 0 ~ 13(영하의 온도도 추움으로 입력), 온화(13~28)\n");
			printf(" - 오늘의 날씨를 입력:");
			//잘못된 날씨 입력을 방지하는 반복문
			while (1) {
				scanf("%s", weather);					
				if (strcmp(weather, "더움") == 0 || strcmp(weather, "추움") == 0 || strcmp(weather, "온화") == 0) {
					break;
				}
				else {
					printf("잘못된 날씨 입력, 다시 입력:");
					//날씨 문자열 초기화
					weather[0] = '\0';
				}
			}

			//미세먼지 상태를 입력받기
			printf(" - 기기를 사용한 곳의 미세먼지 상태(나쁨, 보통, 좋음): ");
			//잘못된 상태 입력을 방지하는 반복문
			while (1) {
				scanf("%s", microdust);
				if (strcmp(microdust, "나쁨") == 0 || strcmp(microdust, "보통") == 0 || strcmp(microdust, "좋음") == 0) {
					break;
				}
				else {
					printf(" - - 잘못된 상태 입력, 다시 입력:");
					//미세먼지 문자열 초기화
					microdust[0] = '\0';
				}
			}

			//습도 상태 입력받기
			//습도 70%이상의 장소에서는 전해질 분해의 가속화 때문에 배터리 사용시간 감소 
			printf("습함의 정도\n 샤워실, 온천, 장마철 차(car)내 = 습함\n 나머지 장소 = 안습함\n");
			printf(" - 사용장소의 습도 여부(습함, 안습함): ");
			while (1) {
				scanf("%s", humidity);
				if (strcmp(humidity, "습함") == 0 || strcmp(humidity, "안습함") == 0) {
					break;
				}
				else {
					printf(" - - 잘못된 습도 입력, 다시 입력:");
					//습도 문자열 초기화
					humidity[0] = '\0';
				}
			}

			//배터리 사용한 사이클 입력
			printf("(충전 후, 방전을 1번 했다면 한 사이클이 지난 것)\n");
			printf(" - 충전(방전)을 사이클 횟수 입력: ");
			scanf("%d", &cycle);

			//오늘 기기를 사용한 시간 입력
			printf(" - (100%를 시작으로)오늘 기기 사용시간(분): ");
			scanf("%f", &spend_today);

			///////////////////////////////////////////////////////////////////////

			///////////////////////////////함수 호출///////////////////////////////
			//배터리 정보 저장
			BetteryCapacity(arr, list_num, mah, machine_name, weather, microdust, humidity);

			//배터리 수명을 계산
			BetteryLifeTime(arr,list_num, mah, cycle);

			//배터리 감쇠율 계산
			minus_bettery(arr, list_num, cycle);

			//1퍼센트 소비되는데 걸리는 시간
			spend_one = Spend_per_one(arr,list_num, mah, cycle);

			//100%에서 현재 남아있는 잔여 배터리 계산
			remain = remain_Bettery(arr, list_num, spend_one, spend_today);
			
			//현재 잔여량에서 방전까지 남은 시간
			LastingTime(remain, spend_one);

			///////////////////////////////////////////////////////////////////////

			printf(" - 기기(%s) 등록이 완료.\n", machine_name);
			printf("\n");


			//기기 이름, 배터리용량, 날씨 문자열 초기화
			machine_name[0] = '\0';
			mah = 0;
			weather[0] = '\0';
			list_num++;
			break;

			//2 입력 시, 이름으로 기기 검색 
		case 2:
			printf(" - 특정기기의 이름을 입력: ");
			scanf("%s", search_name);
			printf("\n");
			search_device(arr, search_name, list_num);
			printf("\n");
			break;

			//2 입력 시, 구조체에 저장된 전체 기기 검색
		case 3:
			printf(" - 등록한 전체기기의 리스트를 출력.\n");
			printing_list(arr, list_num);
			printf("\n");
			break;
			
			//4 입력 시, 프로그램 종료 
		case 4:
			printf("프로그램 종료\n");
			return 0;

			//다른 값 입력 시, 프로그램 종료
		default:
			printf("잘못된 값을 입력. 프로그램 종료\n");
			return 0;
		}

		//모든 포인터 배열에 정보를 저장했다면 프로그램 종료
		if (list_num == 20) {
			printf("20가지 기기를 전부 입력. 프로그램을 종료.\n");
			break;
		}
	}
	return 0;
}