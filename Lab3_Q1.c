#include<stdio.h> 
#include <stdbool.h> 
#define SIZE 24
#define nRows 8
#define nCols 3
// PROTOTYPES
// void print_array(int array[], int length);
// void print_matrix(int mat[][nCols], int rows);
bool isValid(const int arr[],int length, int pos);
void remove_element(int arr[],int length, int pos);

int main()
{
   int position;
   int arr[SIZE];//24
   for(int i=0;i<SIZE;i++){
      arr[i]=i;
   }
   // int arr2d[nRows][nCols]; //8x3
// print_matrix(arr2d,nRows);
//Call to different functions
   printf("Enter the position: ");
   scanf("%d",&position);
   if(isValid(arr, SIZE, position)){
      printf("Position is in the range\n");
      remove_element(arr,SIZE,position);
      for (int j=0; j<SIZE;j++){
         printf("%d\n",arr[j]);
      }
   }

   else{
      printf("Wrong Value");
   }
}



//FUNCTION DEFINITIONS
bool isValid(const int arr[],int length, int pos){
   if (pos>=0 && pos<length){
      return true;
   }else
   return false;
}

void remove_element(int arr[],int length, int pos){
   for(int i=pos ; i>0 ; i--){
      if (i<=pos){
         arr[i]=arr[i-1];
      }
   }
}













// void print_array(int array[], int length){
//    for(int i=0;i<length; i++)
//       printf("array[%d]= %d\n", i, array[i]);
// }  

// void print_matrix(int mat[][nCols], int rows){
//    for(int i=0;i<rows; i++){
//     for(int j=0;j<nCols; j++)
//          printf("mat[%d][%d]= %d\n", i,j, mat[i][j]);
//     puts("");     
//    }     
// }