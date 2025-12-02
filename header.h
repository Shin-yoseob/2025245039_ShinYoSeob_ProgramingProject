typedef struct {
	char name[50];		//기기 이름
	char weather[10];	//날씨
	char microdust[10];	//미세먼지
	char humidity[10];	//습도
	int mah;			//배터리 용량
	int minus;			//배터리 사용 감쇠율
	float full_time;	//현재 기기 최대 사용시간
	float remain;		//현재 배터리 잔여량	
}name;

//배터리 용량을 입력받는 함수.
void BetteryCapacity(name arr[], int list_num, int mah, char machine_name[], char weather[], char microdust[], char humidity[]);

//날씨가 미치는 영향을 적용하는 함수
float weather_bettery(name arr[], int list_num, float pre_fulltime);

//습도가 배터리 사용시간에 미치는 영향을 적용하는 함수(연간 누적치에 따라 계산)
float humidity_bettery(name arr[], int list_num, float pre_fulltime, int cycle);

//미세먼지가 미치는 영향을 적용하는 함수(연간 누적치에 따라 계산)
float microdust_bettery(name arr[], int list_num, float pre_fulltime, int cycle);

//배터리의 수명을 알려주는 함수
void BetteryLifeTime(name arr[], int list_num, float mah, int cycle);

//배터리 사용시간 감쇠율을 계산하는 함수
void minus_bettery(name arr[], int list_num, int cycle);

//배터리 1퍼센트가 소모되는 시간
float Spend_per_one(name arr[], int list_num, int mah, int cycle);

//현재 배터리 잔여량
float remain_Bettery(name arr[], int list_num, float spend_one, float spend_today);

//현재 배터리가 방전될 때까지 사용할 수 있는 시간
void LastingTime(float remain, float spend_one);

//특정기기의 정보찾아 출력
void search_device(name arr[], char name[], int list_num);

//모든 기기의 정보를 기록한 순서대로 출력
void printing_list(name arr[], int list_num);

//float형 시간을 60분으로 보정하기
void Time_revise(name arr[], int list_num);

