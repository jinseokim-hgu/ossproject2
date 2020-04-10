#include "product.h"
W_Record* product[MAX_PRODUCTS]; // 회원정보데이터 (전역)
int _count = 0;

int w_is_available(){
    int i;
    for(i=0; i<MAX_PRODUCTS; i++){
        if(product[i]==NULL){
#ifdef DEBUG
	printf("[DEBUG] Space is available!\n");
#endif
	 return 1;}
    }
    return 0;
}

int w_first_available(){
    int i;
    for(i=0; i<MAX_PRODUCTS; i++){
        if(product[i]==NULL){
#ifdef DEBUG
	printf("[DEBUG] %d is fisrt available space\n",i);
#endif

 return i;}
    }
    return -1;
}

int w_count(){
    return _count;
}

void w_create(char* n, char* bn, char *s, char *g, float pr, int st){
    int index = w_first_available();
    product[index] = (W_Record*)malloc(sizeof(W_Record));
    W_Record* p = product[index];
    strcpy(p->name, n);  
    strcpy(p->brname, bn);
    strcpy(p->size, s);
    strcpy(p->gender, g);
    p->price = pr;
    p->stock = st;
    p->sale=0;
    _count++;
#ifdef DEBUG
	printf("[DEBUG] %s's data is saved in %d array\n",n,index);
#endif
}

W_Record* w_search_by_name(char* n){
    int i;
    for(i=0; i<MAX_PRODUCTS; i++){
        if(product[i] && strcmp(product[i]->name, n)==0){
#ifdef DEBUG
	printf("[DEBUG] %s's address is found!\n",product[i]->name);
#endif
 	return product[i];
}
    }
    return NULL;
}

void w_update(W_Record* p, char* bn, char *s, char *g, float pr, int st){
    strcpy(p->brname, bn);
    strcpy(p->size, s);
    strcpy(p->gender, g);
    p->price = pr;
    p->stock = st;
    p->sale=0;
}

void w_delete(W_Record* p){
    int i, index;
    for(i=0; i<MAX_PRODUCTS; i++)
        if(product[i]==p) {
            index=i;
            break;
        }
    free(p);
    product[index] = NULL;
    _count--;
}
void w_delete_all(){
    int i;
    for(i=0; i<MAX_PRODUCTS; i++){
        if(product[i]!=NULL){
            free(product[i]);
        }
        product[i]=NULL;
    }
    _count=0;
#ifdef DEBUG
	printf("[DEBUG] Delete all is success!\n");
#endif
}


void w_get_all(W_Record* a[]){
    int i, c=0;
    for(i=0; i<MAX_PRODUCTS; i++){
        if(product[i]){
            a[c]=product[i];
            c++;
        }
}
#ifdef DEBUG
	printf("[DEBUG] All Record's number is %d\n",c);
#endif
    
}int w_get_all_brand(W_Record* a[],char* bn){
    int i, c=0;
    for(i=0; i<MAX_PRODUCTS; i++){
        if(product[i]){
            if(strcmp(product[i]->brname,bn)==0){
            a[c]=product[i];
            c++;
		}
}
}
#ifdef DEBUG
	printf("[DEBUG] We get %s's %d record\n",bn,c);
#endif

        
return c;
}
int w_get_all_gender(W_Record* a[], char *g) {
    int i, c=0;
    for(i=0; i<MAX_PRODUCTS; i++){
        if(product[i]){
            if(strcmp(product[i]->gender,g)==0){
            a[c]=product[i];
}            c++;
}
}
#ifdef DEBUG
	printf("[DEBUG] We get %s's %d record\n",g,c);
#endif

        
return c; 
} // 시계정보가 들어있는 특정 성별별 레코드 포인터의 배열을 만들기

void w_save_file(char *t){
    int size=w_count(),i;
    FILE *file=fopen(t,"wt");
#ifdef DEBUG   
	printf("[DEBUG] <%s> is opend!\n",t);
#endif
    W_Record *p[MAX_PRODUCTS];
    w_get_all(p);
    for(i=0; i<size; i++){

fprintf(file,"Name:%-10s Brand:%-10s Size:%-8s Gender:%-8s Price($):%-8.f Stock:%-8d sale:%d Percent\n",w_getname(p[i]),w_getbrname(p[i]),w_getsize(p[i]),w_getgender(p[i]),w_getprice(p[i]),w_getstock(p[i]),w_getsale(p[i]));



#ifdef DEBUG
        printf("[DEBUG] %s %s %s %s %.f %d %d ->saved\n",w_getname(p[i]),w_getbrname(p[i]),w_getsize(p[i]),w_getgender(p[i]),w_getprice(p[i]),w_getstock(p[i]),w_getsale(p[i]));
#endif 
 }

    fclose(file);
}    // 작성한 레코드 저장하기
int w_recall_file(char *t, int ch){
    int i, n;
    char name[20]; char brname[20]; char size[10]; char gender[10]; float price;
    int stock; int sale;
    FILE *file=fopen(t,"rt");
    if(!file){
        return 0;
    }
    if(ch==1){
        w_delete_all();
    }
    for(i=0; i<MAX_PRODUCTS; i++){
        if(!w_is_available()){
            printf("[Load] There is no space!\n");
            break;
        }

 n=fscanf(file,"Name:%s Brand:%s Size:%s Gender:%s Price($):%f Stock:%d sale:%d Percent\n",name,brname,size,gender,&price,&stock,&sale);
    if(n<7)  break;
    if(w_search_by_name(name)){
        printf("[Load] Duplicated name(%s)! Loading.\n",name);
        continue;
    }
    w_create(name,brname,size,gender,price,stock);
    w_search_by_name(name)->sale=sale;
        }        
    fclose(file);
    return 1;
}  //파일 불러오기
void w_stock_update(W_Record *p, int s){
        p->stock=s;
}   //재고 업데이트하기
void w_order_by_name(){
    W_Record*temp=(W_Record*)malloc(sizeof(W_Record));
    int i,j;
    for(i=0; i<MAX_PRODUCTS; i++){
        if(product[i]!=NULL){
        for(j=i+1; j<MAX_PRODUCTS; j++){
            if((product[j]!=NULL)&&(strcmp(product[i]->name,product[j]->name)>0)){
                *temp=*product[i];
                *product[i]=*product[j];
                *product[j]=*temp;
            }
        }
    }
    free(temp);
}
} //이름별로 정리하기
void w_record_op(){
    int i,j;
    for(i=0; i<MAX_PRODUCTS; i++){
        if(product[i]==NULL){
            for(j=i+1; j<MAX_PRODUCTS; j++){
                if(product[j]!=NULL){
                    product[i]=(W_Record*)malloc(sizeof(W_Record));
                    *product[i]=*product[j];
                    w_delete(product[j]);
                    _count++;
                    break;
                }
            }
        }
    }
}    //레코드 최적화 시키기
void w_apply_sale(W_Record *p,int sa){
    p->sale=sa;
}   //할인률 적용하기
char* w_getname(W_Record* p){
    return p->name;
}   // 특정 시계 정보 레코드의 시계이름 가져오기
char* w_getbrname(W_Record* p){
    return p->brname;
}  // 특정 시계 정보의 브랜드이름 가져오기
char* w_getsize(W_Record* p){
    return p->size;
    }// 특정 시계 정보 레코드의 사이즈 가져오기
char* w_getgender(W_Record* p){
    return p->gender;
}   // 특정 시계 정보 레코드의 성별 가져오기
float w_getprice(W_Record* p){
    return p->price;
}   // 특정 시계 정보 레코드의 가격 가져오기
int w_getstock(W_Record* p){
    return p->stock;
}  // 특정 시계 정보 레코드의 재고 가져오기
int w_getsale(W_Record *p){
    return p->sale;
}  //특정 시계 세일율 가져오기
