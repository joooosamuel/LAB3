#include <stdio.h>

int intial_amt= 1000;

int main(){
    int gg=0;
    int transactions[]={200,-150,-500,-400,-50,-200,300};
    int tobeproccessed[10];
    for (int i=0; i<7; ++i){
        if (transactions[i]>=0){
            intial_amt=intial_amt+transactions[i];
            }
        if(transactions[i]<0){
            if(intial_amt<(transactions[i]*-1)){
                printf("Invalid transaction\n");
                tobeproccessed[gg]=transactions[i];
                gg++;
                for (int j=0; j<gg; j++){
                 printf("%d\n",tobeproccessed[j]);
                }   
            }else{
                intial_amt=intial_amt+transactions[i];
            }
        }
    
    }
    printf("final amt= %d\n", intial_amt);
}