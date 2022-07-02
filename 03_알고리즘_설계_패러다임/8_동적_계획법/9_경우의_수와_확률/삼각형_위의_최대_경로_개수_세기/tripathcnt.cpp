#include <iostream>
// 아래 파일에 변수 n과 함수 path2가 있음
#include "../../4_삼각형_위의_최대_경로/trianglepath.cpp"

// 코드 8.17 삼각형 위의 최대 경로의 수를 찾는 동적 계획법 알고리즘

int countCache[100][100];

int count(int y, int x)
{
    if(y == n-1)
    {
        return 1;
    }

    int& ret = countCache[y][x];
    if(ret != -1)
    {
        return ret;
    }

    ret = 0;
    // path2(y+1, x+1) == path2(y+1, x)인 경우
    // ret += count(y+1, x+1); ret += count(y+1, x+1);
    // 임에 유의하자.
    if(path2(y+1, x+1) >= path2(y+1, x))
    {
        ret += count(y+1, x+1);
    }
    if(path2(y+1, x+1) <= path2(y+1, x))
    {
        ret += count(y+1, x);
    }
    return ret;
}