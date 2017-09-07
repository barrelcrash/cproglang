// create two binary search loops with different
// checks and measure the difference in runtime

#include <stdio.h>
#include <time.h>

int binsearch(int x, int v[], int n);
int altbinsearch(int x, int v[], int n);

int main() {
  int time_taken;
  int index;
  int arraylen = 9;
  int array[] = {1, 3, 6, 7, 11, 15, 16, 19, 25};

  time_taken = clock();
  index = binsearch(array[7], array, arraylen);
  printf("Finding %d at position %d took %lu\n",
      array[7], index, clock() - time_taken / CLOCKS_PER_SEC);

  time_taken = clock();
  index = altbinsearch(array[7], array, arraylen);
  printf("Finding %d at position %d took %lu\n",
      array[7], index, clock() - time_taken / CLOCKS_PER_SEC);

}

int binsearch(int x, int v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

int altbinsearch(int x, int v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low < high) {
    mid = (low + high) / 2;
    if (x <= v[mid])
      high = mid;
    else
      low = mid + 1;
  }

  return x == v[high] ? x : -1;
}
