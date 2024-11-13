#include <stdio.h>

int intial_amt= 1000;

int main(){
    int gg=0;
    int transactions[]={200,-150,-500,-400,-50,-200,300,-2000};
    int tobeproccessed[10];
    int siz_arr=sizeof(transactions)/sizeof(transactions[0]);
    for (int i=0; i<siz_arr; i++){
        if (transactions[i]>=0){
            intial_amt=intial_amt+transactions[i];
            }
        if(transactions[i]<0){
            if(intial_amt<(transactions[i]*(-1))){
                // printf("Invalid transaction\n");
                tobeproccessed[gg]=transactions[i];
                gg++;
            }else{
                intial_amt=intial_amt+transactions[i];
            }
            if (intial_amt==0)
            {
                for(int ff=i;ff<=siz_arr;ff++){
                    tobeproccessed[gg]=transactions[ff+1];
                    gg++;
                }
                gg=gg-2;
                break;
            }
            
        }
    
    }
    printf("final amt= %d\n", intial_amt);
    for(int ll=0;ll<(gg);ll++){
        printf("Invalid transaction: \n%d\n", tobeproccessed[ll]);
    }
}