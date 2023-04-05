#include "rbtree.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    rbtree *p = new_rbtree();
    int arr[] = {10, 5, 8, 34, 67, 23, 156, 24, 2, 12};
    rbtree_to_array(p,arr,10);
    int n = sizeof(arr) / sizeof(int);
    printf("\n");
    for(int i =0; i<n; i++){
       printf("%d ",arr[i]);
    }
    return 0;
}