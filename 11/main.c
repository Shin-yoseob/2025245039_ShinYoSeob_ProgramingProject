#include "header.h"
#include <stdio.h>
#include <string.h>

int main() {

	name arr[20];
	int count;

	while (1) {
		char machine_name[50];
		int mah, cycle;
		float spend_one, spend_today, remain;
		int i;

		printf("기기 이름을 입력하세요(프로그램 종료는 'EXIT' 입력):");
		scanf("%s", machine_name);

		if (strcmp(machine_name, "EXIT") == 0){
			return 0;
		}

		printf("배터리의 용량을 입력(mah):");
		scanf("%d", &mah);

		BetteryCapacity(arr, mah, machine_name);

		printf("(하루에 방전이 되고 충전을 했다면 1번의 사이클이 지난 것)\n");
		printf("충전(방전)을 한 사이클 입력(잘 모르겠다면 1일에 1번 사이클이 돈 것으로 계산하면 됩니다.): ");
		scanf("%d", &cycle);

		BetteryLifeTime(arr, mah, cycle);

		minus_bettery(arr, cycle);

		spend_one = Spend_per_one(mah);

		printf("오늘 기기를 몇 분 사용하셨나요: ");
		scanf("%f", spend_today);

		remain = remain_Bettery(spend_one, spend_today);

		LastingTime(remain);

		arr + 1;
	}

	return 0;
}