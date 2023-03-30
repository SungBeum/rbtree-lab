#include <stdio.h>

// int main(void) {
//     int i, sum;
//     sum = 0;
//     for (i=1; i<=10; i++) {
//         if (i%2 == 0){
//             sum = sum + i;
//         }
//     }
//     printf("짝수의 합 : %d\n",sum);

// }

int main() {
    int i, n, m, sum;
    sum = 0;
    printf("n 부터 m 까지 홀수들의 합을 구하는 프로그램입니다.\n");
    printf("n 값을 입력해주세요 :\n");
    scanf("%d",&n);
    printf("m 값을 입력해주세요 :\n");
    scanf("%d",&m);
    for (i=n; i<=m; i++) {
        if (i%2 ==1){
            sum = sum + i;
        }
    }
    printf("%d 부터 %d 까지의 홀수의 합은 : %d 입니다.\n",n ,m, sum);
}