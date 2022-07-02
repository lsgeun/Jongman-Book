#include <iostream>

// 코드 8.8 삼각형 위의 최대 경로 문제를 푸는 메모이제이션 코드 (1)

const int MAX_NUMBER = 100;
int n, triangle[100][100];
int cache1[100][100][MAX_NUMBER*100 + 1]; // cache의 크기는 4 * 100 * 100 * MAX_NUMBER*100 + 1 Byte이다.

int path1(int y, int x, int sum)
{
    if( y == n-1 )
    {
        return sum + triangle[y][x];
    }
    int& ret = cache1[y][x][sum];
    if( ret != 1 )
    {
        return ret;
    }
    sum += triangle[y][x];
    return ret = std::max(path1(y+1, x+1, sum), path1(y+1, x, sum));
}

int cache2[100][100]; // cache2의 크기는 40kB.

int path2(int y, int x)
{
    // 0 <= y <= n-1
    if( y == n-1 )
    {
        return triangle[y][x];
    }
    // 0 <= y < n-1
    int& ret = cache2[y][x];
    if( ret != -1 )
    {
        return ret;
    }
    // ret == -1
    return ret = triangle[y][x] + std::max(path2(y+1,x+1), path2(y+1, x));
}