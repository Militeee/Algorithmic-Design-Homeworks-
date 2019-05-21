#include "sorting.h"
#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define LIMIT pow(2, 20)

int
main()
{
  struct timespec b_time, e_time;
  for (size_t i = 4; i < LIMIT; i *= 2) {
    printf("Dimension of array = %ld\n", i);
    int* array1 = (int*)malloc(sizeof(int) * i);

    // for(int j = 0; j < i ; j++)
    //    array1[j] = j+1;

    random_fill_array(array1, i);
    // print_array(array1,i);

    clock_gettime(CLOCK_REALTIME, &b_time);
    int selected = select_i(array1, i / 3 + 1, 0, i - 1);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("Selection of %dth element  \t%lf\n",
           (int)i / 3 + 1,
           get_execution_time(b_time, e_time));
    printf("%ldth element=%d\n", i / 3 + 1, selected);
    quickSort(array1, 0, i - 1);
    if (i < 32)
      print_array(array1, i);

    free(array1);
  }
}