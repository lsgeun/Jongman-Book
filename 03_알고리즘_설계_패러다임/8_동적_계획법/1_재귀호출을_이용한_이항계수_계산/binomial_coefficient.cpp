#include <iostream>

// 코드 8.1 재귀 호출을 이용한 이항계수의 계산

int bino(int n, int r)
{
    // 기저 사례: n=r(모든 원소를 다 고르는 경우) 혹은 r=0 (고를 원소가 없는 경우)
    if( r == 0 || r == n )
    {
        return 1;
    }
    // else
    return bino(n-1, r-1) + bino(n-1,r);
}

// 코드 8.2 메모이제이션을 이용한 이항 계수의 계산

// -1로 초기화해 둔다.
int cache[30][30];
// 추가한 내용
void init_cache(int n)
{
    for( int i = 0; i <= n; ++i )
    {
        cache[i][i] = 1;
        cache[i][0] = 1;
        for( int j = 1; j < i; ++j )
        {
            cache[i][j] = -1;
        }
    }
}
//
int bino2(int n, int r)
{
    init_cache(n);
    // 기저 사례
    if( r == 0 || r == n )
    {
        return 1;
    }
    // -1이 아니라면 한 번 계산했던 값이니 곧장 반환
    if( cache[n][r] != -1 )
        return cache[n][r];
    // 직접 계산한 뒤 배열에 저장
    return cache[n][r] = bino2(n-1, r-1) + bino2(n-1, r);
}

int main(void)
{
    int a = bino2(10, 8);
    printf("%d", a);
    
    return 0;
}