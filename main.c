#include "header.h"
#include <stdio.h>
#include <string.h>

int main() {

	name arr[20];
	int count;

	while (1) {
		char machine_name[50], search_name[20];		
		int mah, cycle;
		float spend_one, spend_today, remain;
		int i;
		int switch_num = 0, list_num = 0;

		printf("==================================================\n");
		printf("1 => 기기등록, 2 => 등록한 기기 검색, 3 => 전체 기기 정보 출력, 4 => 프로그램 종료\n");
		printf("원하시는 동작의 번호를 입력해주세요: ");
		scanf("%d", &switch_num);

		switch (switch_num) {
		case 1:
			printf("기기 이름을 입력하세요:");
			scanf("%s", machine_name);

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
			scanf("%f", &spend_today);

			remain = remain_Bettery(spend_one, spend_today);

			LastingTime(remain);

			list_num++;
			arr + 1;
			printf("\n");
			break;

		case 2:
			printf("특정기기의 이름을 입력해주세요: ");
			scanf("%s", search_name);
			search_device(arr, search_name, list_num);
			printf("\n");
			break;

		case 3:
			printf("등록한 전체기기의 리스트를 출력합니다.\n");
			printing_list(arr, list_num);
			break;

		case 4:
			printf("프로그램 종료\n");
			return 0;

		default:
			printf("잘못된 값을 입력하셨습니다. 프로그램 종료\n");
			return 0;
		}
	}
	return 0;
}