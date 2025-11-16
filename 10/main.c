#include "header.h"
#include <stdio.h>
#include <string.h>

int main() {

	name arr[20];
	int count;

	while (1) {
		char machine_name[50];
		int mah, cycle;
		int i;

		printf("기기 이름을 입력하세요(프로그램 종료는 'EXIT' 입력):");
		scanf("%s", machine_name);

		if (strcmp(machine_name, "EXIT") == 0){
			return 0;
		}

		printf("배터리의 용량을 입력(mah):");
		scanf("%d", &mah);

		printf("(하루에 방전이 되고 충전을 했다면 1번의 사이클이 지난 것)\n");
		printf("충전(방전)을 한 사이클 입력: ");
		scanf("%d", &cycle);

		strcpy(arr->name, machine_name);
		arr->mah = mah;
		arr->remain = remain_Bettery();
		arr->full_time = LastingTime();
		arr->minus = minus_bettery();

		arr + 1;
	}

	return 0;
}