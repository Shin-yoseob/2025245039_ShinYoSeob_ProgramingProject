typedef struct {
	char name[50];		//기기 이름
	int mah;			//배터리 용량
	int minus;			//배터리 사용 감쇠율
	float full_time;	//현재 기기 최대 사용시간
	float remain;		//현재 배터리 잔여량	
}name;

//배터리 용량을 입력받는 함수.
void BetteryCapacity();

//배터리의 수명을 알려주는 함수
void BetteryLifeTime();

//배터리 사용시간 감쇠율을 계산하는 함수
void minus_bettery();

//배터리 1퍼센트가 소모되는 시간
float Spend_per_one();

//현재 배터리 잔여량
float remain_Bettery();

//현재 배터리가 방전될 때까지 사용할 수 있는 시간
void LastingTime();	

//특정기기의 정보찾아 출력
void search_device();

//모든 기기의 정보를 기록한 순서대로 출력
void printing_list();

//float형 시간을 60분으로 보정하기
void Time_revise();

