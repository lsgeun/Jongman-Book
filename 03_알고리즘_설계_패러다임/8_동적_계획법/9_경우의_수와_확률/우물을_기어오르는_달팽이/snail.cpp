#include <iostream>

// 8.18 우물을 기어오르는 달팽이 문제를 해결하는 동적 계획법 알고리즘

const int MAX_N = 50;
int n, m;
int cache[MAX_N][2*MAX_N+1];

int climb(int days, int climbed)
{
    // 비 오지 않을 확률 50%, 비 올 확률 50%
    if(days == m)
    {
        return climbed >= n ? 1 : 0;
    }

    int& ret = cache[days][climbed];
    if(ret != -1)
    {
        return ret;
    }
    
    ret = climb(days+1, climbed+1) + climb(days+1, climbed+2);
    return ret;
}
// 마지막에 확률 계산
// climb(0,0) / 2^m 이 확률임.

int climb2(int days, int climbed)
{
    // 비 오지 않을 확률 25%, 비 올 확률 75%
    if(days == m)
    {
        return climbed >= n ? 1 : 0;
    }

    int& ret = cache[days][climbed];
    if(ret != -1)
    {
        return ret;
    }

    ret = 0.25*climb2(days+1, climbed+1) + 0.75*climb2(days+1, climbed+2);
    return ret;
}
// climb2(0,0)이 확률임.