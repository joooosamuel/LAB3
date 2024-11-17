//Headers
#include <stdio.h>

int intial_amt= 1000; //store initial amount

int main(){
    int gg=0; //keep track of invalid transactions
    int transactions[]={200,-150,-500,-400,-50,-200,300}; //array of transactions negative numbers indicate withdrawl
    int tobeproccessed[10]; //blank arry initialized to store the invalid transactions
    int siz_arr=sizeof(transactions)/sizeof(transactions[0]); //calculate the size of the transaction array
    for (int i=0; i<siz_arr; i++){ //looping through the transaction array
        if (transactions[i]>=0){ //if the element in the array is >=0 (deposit)
            intial_amt=intial_amt+transactions[i]; //it adds it to the initial amount
            }
        if(transactions[i]<0){ //if the element is <0 (withdrawl)
            if(intial_amt<(transactions[i]*(-1))){ //checking if there is sufficient money to withdraw
                tobeproccessed[gg]=transactions[i]; //if there isnt sufficient fund its stored in the tobeproccessed array
                gg++; //increment the invalid transaction index
            }else{
                intial_amt=intial_amt+transactions[i]; //if theres sufficient funds to proceed with the withdrawl
            }
            if (intial_amt==0){ //when the balance reaches 0 after transactions
                for(int ff=i;ff<=siz_arr;ff++){ //makes all the other transactions and moves them to the tobeproccessed array
                    tobeproccessed[gg]=transactions[ff+1]; //storing them in the tobeproccessed array
                    gg++;
                }
                gg=gg-2; //making sure the index is in order, avoiding unnecessary errors
                break; //exits the loop as all other transactions will be invaild
            }
            
        }
    
    }
    printf("final amt= %d\n", intial_amt); //prints the final amount 
    for(int ll=0;ll<(gg);ll++){
        printf("Invalid transaction: \n%d\n", tobeproccessed[ll]); //printing all the invalid transactions
    }
}