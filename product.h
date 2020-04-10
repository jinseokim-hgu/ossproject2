
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 5      // 저장할 수 있는 레코드 최대 갯수

// 회원 정보 레코드의 데이터 타입을 정의함
typedef struct st_watch{
    char name[20];  // 시계 이름
    char brname[20]; // 브랜드 이름
    char size[20];  // 시계 사이즈
    char gender[10];// 남성용,여성용
    float price;  // 시계 가격
    int stock; // 재고 수
    int sale; //세일율
} W_Record;

// 라이브러리 함수 원형을 선언함
int w_is_available();       // 현재 추가할 수 있는 데이터 공간이 있는가?/ 공간이 있으면 1 없으면 0을 리턴
int w_first_available();    // 추가할 수 있는 가장 빠른 포인터 배열의 인덱스 찾기/ 포인터 배열의 인덱스를 리턴하거나 없으면 -1을 리턴
int w_count();              // 현재 저장된 시계 레코드의 개수 가져오기/ 레코드의 개수를 리턴
void w_create(char* n, char* bn, char *s, char *g, float pr, int st);   // 새로운 신규 시계 레코드 추가 /파라메터-> 시계이름,브랜드,시계크기,가격,재고 수
W_Record* w_search_by_name(char* n); // 이름이 일치하는 시계 레코드 포인터 찾기/파라메터-> 이름 /이름이 일치하는 시계 레코드 포인터를 리턴
void w_update(W_Record* p, char* bn, char *s, char *g, float pr, int st);  // 특정 시계 레코드의 정보 업데이트/파라메터-> 특정 시계의 구조체 포인터,브랜드,시계크기,가격,재고 수
void w_delete(W_Record* p);         // 특정 시계 레코드의 상세정보 제거/파라메터->특정 시계의 구조체 포인터
void w_get_all(W_Record* a[]);   // 시계정보가 들어있는 모든 레코드 포인터의 배열을 만들기/파라메터-> 시계 정보를 저장할 구조체 포인터 배열
int w_get_all_brand(W_Record* a[],char* bn);    // 시계정보가 들어있는 특정 브랜드별 레코드 포인터의 배열을 만들기/파라메터->특정 브랜드별 레코드 포인터를 저장할 구조체 포인터 배열, 브랜드이름/저장된 특정브랜드의 시계의 정보 개수를 리턴
int w_get_all_gender(W_Record* a[],char *g);  // 시계정보가 들어있는 특정 성별별 레코드 포인터의 배열을 만들기/파라메터->특정 성별 별 레코드 포인터를 저장할 구조체 포인터 배열, 성별/저장된 특정 성별의 시계의 정보 개수를 리턴
void w_save_file(char *t);    // 작성한 레코드 저장하기//파라메터-> 저장할 파일의 이름
int w_recall_file(char *t,int ch);  //파일 불러오기//파라메터->불러올 파일의 이름//파일로드에 성공하면 1을 리턴하고 실패하면 0을 리턴한다.
void w_stock_update(W_Record *p, int s);   //재고 업데이트하기//파라메터-> 특정시계의 레코드 포인터, 바꿀 재고의 수
void w_order_by_name(); //이름별로 정리하기
void w_record_op();    //레코드 최적화 시키기
void w_apply_sale(W_Record *p,int sa);   //할인율 적용하기//파라메터->특정시계의 레코드 포인터, 적용할 할인율
char* w_getname(W_Record* p);   // 특정 시계 정보 레코드의 시계이름 가져오기//파라메터-> 특정시계의 레코드포인터//특정 시계의 이름을 문자열로 리턴
char* w_getbrname(W_Record* p);  // 특정 시계 정보의 브랜드이름 가져오기//파라메터-> 특정시계의 레코드포인터//특정 시계의 브랜드를 문자열로 리턴
char* w_getsize(W_Record* p);// 특정 시계 정보 레코드의 사이즈 가져오기//파라메터-> 특정시계의 레코드포인터//특정 시계의 사이즈를 문자열로 리턴
char* w_getgender(W_Record* p);   // 특정 시계 정보 레코드의 gender 가져오기//파라메터-> 특정시계의 레코드포인터//특정 시계의 gender를 문자열로 리턴
float w_getprice(W_Record* p);   // 특정 시계 정보 레코드의 가격 가져오기//파라메터-> 특정시계의 레코드포인터//특정 시계의 가격을 리턴
int w_getstock(W_Record* p);  // 특정 시계 정보 레코드의 재고 가져오기//파라메터-> 특정시계의 레코드포인터//저장 할 특정 시계의 재고를 리턴
int w_getsale(W_Record *p); //특정 시계 세일율 가져오기//파라메터-> 특정시계의 레코드포인터//저장 할 특정 시계의 세일율을 리턴
