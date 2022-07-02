#include <iostream>
// 코드 8.16 타일링의 수를 세는 동적 계획법 알고리즘

const int MOD = 1000000007;
int cache[101];

int tiling(int width)
{
    // 입력으로 width가 1이상의 자연수가 들어와야 함.
    // width의 최대값이 100이므로 정확히는 1 <= width <= 100임.

    // width <= 0 이거나 width >= 101이라면
    // tiling 가능 방법은 없으므로 0을 반환함
    if(width <= 0 || width >= 101)
    {
        return 0;
    }
    else if(width == 1)
    {
        return 1;
    }
    else if(width == 2)
    {
        // ret == 2
        return 2;
    }
    // width >= 3
    // 0 <= ret <= 2일 경우 캐싱되지 않고
    // 함수에서 값 바로 반환
    int& ret = cache[width];
    if(ret != -1)
    {
        return ret;
    }
    // => width-2 >= 1, width-1 >= 2
    // (width가 3일 경우) 3 <= ret <= MOD-1 (MOD 나머지의 최대 값)
    ret = (tiling(width-2) + tiling(width-1)) % MOD;
    return ret;
}

// ../10_비대칭_타일링/asymtiling.cpp의 main 함수와 충돌해서 주석 처리함.
// int main(void)
// {
//     for(int i = 0; i < 102; ++i)
//     {
//         cache[i] = -1;
//     }

//     for(int i = 20; i < 30; ++i)
//     {
//         printf("%d\n", tiling(i));
//     }
//     return 0;
// }