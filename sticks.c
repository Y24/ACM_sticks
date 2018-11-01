#include<stdio.h>
#include<stdlib.h>
typedef struct _int_array {
    int* element;
    int length;
} int_array ;
int CY(int_array*);
int Sum(const int_array*);
int_array* factrization(int);
void destory_factors(int_array* factors);
void sort(int_array*);
void exchange(int*,int*);
void init_loop_values(int* loop_values,int length);
int has_next_step(int* loop_valuse,int length,int max);
void step(int* loop_values,int length,int max);
int find(const int* array,int* loop_values,int length,int test_number);
int test(int_array*,int,int);
void part_test(int_array* array,int test_number,int* loop_values,int* flag);
int is_untouched(int* loop_values,int length,int* flag);
void change(int* loop_values,int length,int* flag);
int is_passed(int* flag,int length);
int Max(const int_array*);
int main(void)
{
    int_array array;
    while(1){
        scanf("%d",&array.length);
        if(array.length==0) break;
         else{
            array.element = (int*)malloc(array.length*sizeof(int));
            for(int i=0;i<array.length;i++){
                scanf("%d",&array.element[i]);
            }
            printf("%d\n",CY(&array));
            free(array.element);
        }
    }
    return 0;
}
int CY(int_array *array){
    int array_sum = Sum(array);
    int_array* factors = factrization(array_sum);
    if((*factors).length == 0){
        destory_factors(factors);
        abort();//problem has no solutions.
    }
    for(int i=0;i<(*factors).length;i++){
        if(test(array,array_sum,(*factors).element[i])){
            free ((*array).element);
        return (*factors).element[i];
        }
    }
    destory_factors(factors);
    abort();//problem has no solutions.
    return 0;
}
int Sum(const int_array* array){
     int sum = 0;
    for(int i=0;i<(*array).length;i++)
    sum +=(*array).element[i];
    return sum;
}
int_array* factrization(int origin){
    int_array* factors = (int_array*)malloc(sizeof(int_array));
    (*factors).length = 0;
    (*factors).element = (int*)malloc(origin*sizeof(int));
    for(int i=2;i<origin;i++)
        if(origin%i == 0) 
         (*factors).element[(*factors).length++] = i;
    return factors;    
}
void destory_factors(int_array* factors){
    free((*factors).element);
    free(factors);
}

int Max(const int_array *array){
    int max=0;
    for(int i=0;i<(*array).length;i++)
       if((*array).element[i]>=max)
         max = (*array).element[i];
    return max;
}
int test(int_array* array,int array_sum,int test_number){
     
    if(test_number<=Max(array))
    return 0;
    else {
        int *loop_values = (int*)malloc((*array).length*sizeof(int));
        int *flag = (int*)calloc(sizeof(int),(*array).length);
        part_test(array,test_number,loop_values,flag);
        free(loop_values);
        return is_passed(flag,(*array).length);
    }
}
int is_passed(int* flag,int length){
    for(int i=0;i<length;i++)
      if(flag[i]==0)
        return 0;
    return 1;
}
void part_test(int_array* array,int test_number,int* loop_values,int* flag){
    for(int i=2;i<=(*array).length-2;i++){
      init_loop_values(loop_values,i);
      while(has_next_step(loop_values,i,(*array).length)){
          step(loop_values,i,(*array).length);
          if(find((*array).element,loop_values,i,test_number)&&is_untouched(loop_values,i,flag))
                change(loop_values,i,flag);  
      }      
    }
}
int is_untouched(int* loop_values,int length,int* flag){
     for(int i=0;i<length;i++)
       if(flag[loop_values[i]]==1)
         return 0;
    return 1;
}
void change(int* loop_values,int length,int* flag){
    for(int i=0;i<length;i++)
      flag[loop_values[i]]=1;
}
void init_loop_values(int* loop_values,int length){
    for(int i=0;i<length;i++)
      loop_values[i] = i;
}
int has_next_step(int* loop_values,int length,int max){
    for(int i=0;i<length;i++)
      if(loop_values[i] != max+i-length)
      return 1;
    return 0;
}
void step(int *loop_values,int length,int max){
    for(int i=length-1;i>=0;i--){
        if(loop_values[i] !=max+i-length){
          if(length-1-i==0) {
              loop_values[i]++;
              break;
          }
          else{
              loop_values[i]++;
              for(int j=i+1;j<length;j++){
                  loop_values[j]=loop_values[i]+j-i;
              }
              break;
          }
        }
    }
}
int find(const int* array,int* loop_values,int length,int test_number){
    int sum =0;
    for(int i=0;i<length;i++)
      sum +=array[loop_values[i]];
    return sum==test_number;
}