#include <stdio.h>
#include "product.h"
#include <stdlib.h>
#include <string.h>

    void create_record();
    void read_record();
    void update_record();
    void delete_record();
    void save_record();
    void list_record();
    void showall_record();
    void brlist_record();
    void mflist_record();
    void stupdate_record();
    void orderbyname();
    void recordopt();
    void discount();

int main(){
int menu;
    while(1){
        printf("\nMenu : 1.Create 2.Read 3.Update 4.StockUpdate 5.Delete 6.List(Brand) 7.List(Gender) 8.List(all) \n       9.SaveFile 10.RecallFile 11.OrderByName 12.Record Optimization 13.ApplyDiscount 0.Quit > ");
        scanf("%d", &menu);
        printf("\n");
        switch(menu){
            case 1: 
                create_record();
                break;
            case 2: 
                read_record();
                break;
            case 3: 
                update_record();
                break;
            case 4: 
                stupdate_record();
                break;
            case 5: 
                delete_record();
                break;
            case 6: 
                brlist_record();
                break;
            case 7: 
                mflist_record();
                break;
            case 8: 
                list_record();
                break;
            case 9: 
                save_record();
                break;
            case 10: 
                showall_record();
                break;
            case 11: 
                orderbyname();
                break;
            case 12: 
                recordopt();
                break;
            case 13: 
                discount();
                break;
            case 0: 
            default: 
                return 0;
        }
    }
    return 0;
}
void create_record(){
    char name[20], brname[20],size[10],gender[10];
    float price; int stock;
    if(w_is_available()==0){
        printf("There is no space\n");
        return;
    }
    printf("Enter a new product's info.\n");
    printf("Name?:");
    scanf("%s",name);
    if(w_search_by_name(name)) {
        printf("Duplicated name!\n");
        return;
    }
    printf("Brand Name?:");
    scanf("%s",brname);
    printf("Size?:");
    scanf("%s",size);
    while(1){
    printf("Gender(Man or Woman)?:");
    scanf("%s",gender);
    if((strcmp(gender,"Man")==0)||(strcmp(gender,"Woman")==0)){break;}
    else {
        printf("Please Enter Man or Woman!\n");
    }
    }
    printf("Price($)?:");
    scanf("%f",&price);
    printf("Stock?:");
    scanf("%d",&stock);
    w_create(name,brname,size,gender,price,stock);
}
    void read_record(){
        char name[20];
printf("Enter a name ->");
scanf("%s",name);
W_Record* records=w_search_by_name(name);
if(records==NULL){
    printf("No such product!\n");
    return;
}
else {
printf("\nWatch's info\n");
printf("Name: %s\n",w_getname(records));
printf("Brand: %s\n",w_getbrname(records));
printf("Size: %s\n",w_getsize(records));
printf("Gender: %s\n",w_getgender(records));
printf("Price: %.f$\n",w_getprice(records));
printf("SalePrice: %.f$\n",w_getprice(records)*(1-(float)w_getsale(records)/100));
printf("Stock: %d\n",w_getstock(records));
printf("Sale: %d Percent\n",w_getsale(records));
}
    }

    void update_record(){
        char name[20], brname[20],size[10],gender[10];
    float price; int stock;
    printf("Enter a name ->");
scanf("%s",name);
W_Record* records=w_search_by_name(name);
if(records==NULL){
    printf("No such product!\n");
    return;
}
else {
printf("Update %s's info\n",name);
printf("Brand Name?:");
    scanf("%s",brname);
    printf("Size?:");
    scanf("%s",size);
    while(1){
    printf("Gender(Man or Woman)?:");
    scanf("%s",gender);
    if((strcmp(gender,"Man")==0)||(strcmp(gender,"Woman")==0)){break;}
    else {
        printf("Please Enter Man or Woman!\n");
    }
    }
    printf("Price($)?:");
    scanf("%f$",&price);
    printf("Stock?:");
    scanf("%d",&stock);
    w_update(records,brname,size,gender,price,stock);
    printf("%s's info is updated!",name);
    }
}
    void delete_record(){
        char name[20];
    printf("Enter a name ->");
    scanf("%s",name);
    W_Record *records=w_search_by_name(name);
    if(records==NULL){
    printf("No such product!\n");
    return;
}
else {
    w_delete(records);
    printf("The record is deleted!\n");
}
    }
    void save_record(){
        char fm[20];
        printf("Enter a file you want to save->");
        scanf("%s",fm);
        w_save_file(fm);
        printf("Records are stored in %s!\n",fm);
    }
    void list_record(){
        printf("All products's records.\n");
    int size = w_count();
    W_Record* records[MAX_PRODUCTS];
    w_get_all(records);
    for(int i=0; i<size; i++){
        W_Record* p = records[i];


	printf("%d. Brand:%-10s Name:%-12s Size:%-8s Gender:%-8s Price($):%-8.f SalePrice($):%-8.f Stock:%-8d sale:%d Percent\n",i+1, p->brname, p->name, p->size, p->gender, p->price,p->price*(1-(float)p->sale/100),p->stock,p->sale);   
 }
    }
    void showall_record(){
        char fm[20]; int ch;
        printf("Enter a file you want to recall->");
        scanf("%s",fm);
	while(1){
        printf("1.Erase all and Recreate\n");
        printf("2.Just add > ");
        scanf("%d",&ch);
	if(ch!=1&&ch!=2)
	printf("please Enter 1 or 2\n");
	else break;
	}        
        if(w_recall_file(fm,ch))
        printf("Records are recalled in %s!\n",fm);
        else printf("There is no file!\n");
    }
    void brlist_record(){
        char brname[20]; int c,i;
        printf("Brand name->");
        scanf("%s",brname);
        W_Record *record[MAX_PRODUCTS];
        c=w_get_all_brand(record,brname);
        if(c==0){
            printf("No such Brand!\n");
            return;
        }
        for(i=0; i<c; i++){
            W_Record* p = record[i];
       
	printf("%d. Brand:%-10s Name:%-12s Size:%-8s Gender:%-8s Price($):%-8.f SalePrice($):%-8.f Stock:%-8d sale:%d Percent\n",i+1, p->brname, p->name, p->size, p->gender, p->price,p->price*(1-(float)p->sale/100),p->stock,p->sale);   

 }
    }
    void mflist_record(){
        char mf[10]; int c,i;
        printf("Man or Woman?->");
        scanf("%s",mf);
        if((strcmp(mf,"Man")==0)||(strcmp(mf,"Woman")==0)){
            
        }else{
            printf("Please Enter Man or Woman!\n");
            return ;
        }   
        
        W_Record *record[MAX_PRODUCTS];
        c=w_get_all_gender(record,mf);
        if(c==0){
            if(strcmp(mf,"Man")==0){
            printf("No Man's data\n");}
            else{ printf("No Woman's data\n");}
            return;
        }
        
        for(i=0; i<c; i++){
            W_Record* p = record[i];
    
	printf("%d. Brand:%-10s Name:%-12s Size:%-8s Gender:%-8s Price($):%-8.f SalePrice($):%-8.f Stock:%-8d sale:%d Percent\n",i+1, p->brname, p->name, p->size, p->gender, p->price,p->price*(1-(float)p->sale/100),p->stock,p->sale);   

 }
    
    }
    void stupdate_record(){
        char name[20];
        int st;
        printf("Enter a name ->");
        scanf("%s",name);
W_Record* records=w_search_by_name(name);
if(records==NULL){
    printf("No such product!\n");
    return;
}
else {
printf("%s's stock is %d\n",name,w_getstock(records));
printf("Enter the now stock->");
scanf("%d",&st);
w_stock_update(records,st);
}
    }
    void orderbyname(){
        w_order_by_name();
        printf("Order by name is completed!\n");
    }
    void recordopt(){
        w_record_op();
        printf("Record optimization is completed!\n");
    }
    void discount(){
        char name[20]; int sale;
        float pr;
        printf("Enter a name ->");
    scanf("%s",name);
W_Record* records=w_search_by_name(name);
if(records==NULL){
    printf("No such product!\n");
    return;
    }
    else {
        sale=w_getsale(records);
	pr=w_getprice(records);
        printf("%s's price is %.f\n",name,pr);
        if(sale!=0){
            printf("%d Percent is applyed\n",sale);
	    printf("SalePrice is %.f\n",pr*(1-(float)sale/100));
        }
        printf("How many percent do you apply?->");
        scanf("%d",&sale);
        w_apply_sale(records,sale);
        printf("Completed!\n");
    }
    }
    
