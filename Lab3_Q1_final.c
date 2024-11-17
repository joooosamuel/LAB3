#include<stdio.h> 
#include <stdbool.h> 


#define SIZE 24
#define Rows 8
#define Cols 3


// PROTOTYPES
bool isValid(const int arr[],int length, int pos);
void remove_element(int arr[],int length, int pos);
void insert_element(int arr[], int length, int pos, int value);
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]);
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transpose[nCols][ nRows]);
bool found_duplicate(int arr[],int length);

int main()
{
   // Declaring variables
   int selection;
   int position;
   int arr[SIZE]; //24
   int value=80; //element that will be added in the insert an element function
   
   // Creation of 1D array
   for(int i=0;i<SIZE;i++){
      arr[i]=i;
   }
   
   //Menu seleciton and call to associated functions
   printf("1. Remove element\n2. Insert element\n3. Reshape\n4. Transpose\n5. Check for duplicates \nEnter your choice: ");
   scanf("%d", &selection);
   if(selection==1){
      printf("Enter the position: ");
      scanf("%d",&position); //storing the position entered by the user
      if(isValid(arr, SIZE, position)){ //calling the isValid function to ensure its in the range
         printf("Position is in the range\n");
          remove_element(arr,SIZE,position); //calling the remove element function here
            for (int j=0; j<SIZE;j++){
            printf("%d ",arr[j]); //printing the array
            }
         }else{
            printf("Wrong Value");
         }
   }  
   if (selection==2){
      printf("Enter the position: ");
      scanf("%d",&position);
      if(isValid(arr, SIZE, position)){ //calling the isValid function to ensure its in the range
         printf("Position is in the range\n");
         insert_element( arr, SIZE, position, value); //calling the insert element function here
         for(int j=0; j<SIZE;j++){
            printf("%d ",arr[j]); //printing the array
         }
      }else{
            printf("Wrong Value");
         }
   }
  
   if(selection==3){   
      int arr2d[Rows][Cols]; //initialising a 2D array wuth 8 rows and 3 columns
      reshape(arr, SIZE,Rows,Cols,arr2d);
      for(int x=0; x<Rows; x++){ //loop for each row
         for(int y=0;y<Cols;y++){ //loopf for column
            printf("%d ",arr2d[x][y]); //printing the 2D matrix
         }
         printf("\n"); //moving to next line after printing columns of the current row
      }
   }

   if(selection==4){   
      int arr2d[Rows][Cols];
      int mat_transpose[Cols][Rows];
      reshape(arr, SIZE,Rows,Cols,arr2d); //calling reshape function to create the 2D array from the 1D array
      trans_matrix(Rows, Cols, arr2d, mat_transpose); //calling function to create transpose


      for(int f=0;f<Cols;f++){
         for(int b=0;b<Rows;b++){
            printf("%d ", mat_transpose[f][b]); //printing the transposed 2D matrix
         }
      printf("\n"); //moving to next line after printing columns of the current row
      }
   }

   if(selection==5){
      bool duplicate=found_duplicate(arr,SIZE);
      printf("Array has duplicate: %s", duplicate ? "true" : "false");
   }
}



//FUNCTION DEFINITIONS

//Checking if the position entered by the user is within the range
bool isValid(const int arr[],int length, int pos){
   if (pos>=0 && pos<length){
      return true; 
   }else
   return false;
}

//Removes the element at the position entered by the user
void remove_element(int arr[],int length, int pos){
   for(int i=pos ; i>0 ; i--){
      if (i<=pos){
         arr[i]=arr[i-1];
      }
   }
}

//inserts the element at the position entered by the user
void insert_element(int arr[], int length, int pos, int value){
   for(int i=0; i < pos; i++){
         arr[i] = arr[i + 1];
      }
      arr[pos] = value;
}

//converts the 1D matrix into a 2D matrix column by column
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]){
   if (length!=nRows * nCols){
      printf("Dimensions of 1D array do not match the 2D\n");
   }else{
      int l=0;
      for(int i= 0; i<nCols; i++){
         for(int k=0; k<nRows; k++){
            arr2d[k][i]= arr[l];
            l++;
         }
      }
   }
}

//makes the 2D matrix from 8x3 to 3x8
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transpose[nCols][ nRows]){
   for(int i=0;i<nRows;i++){
      for(int j=0;j<nCols;j++){
         mat_transpose[j][i]=mat[i][j];
      }
   }
}

//checks for duplicates in the 2D matrix
bool found_duplicate(int arr[],int length){
   for(int i=0;i<length;i++){
      for(int g=i+1;g<length;g++){
         if(arr[i]==arr[g]){
         return true;
         }
      }
   }
   return false;   
}










