#include <iostream>
#include "../9_경우의_수와_확률/타일링_방법의_수_세기/tiling2.cpp"
// 코드 8.19 비대칭 타일링 문제를 해결하는 동적 계획법 알고리즘

int asymmetric(int width, int does_add_MOD)
{
    // tiling의 시간 복잡도가 O(n) 이므로
    // 이 함수의 시간 복잡도가 O(n) 임.
    // n의 길이가 홀수인 경우
    if(width%2 == 1)
    {
        // 가운데 세로로 타일을 1개를 깔았을 때
        // 왼쪽 타일의 패턴과 오른쪽 타일의 패턴이 일치되는 개수를 뺌
        return (tiling(width) - tiling(width/2) + MOD) % MOD;
    }
    // n의 길이가 짝수인 경우
    // MOD를 더하는 이유
        // MOD를 더하는 이유는 음수를 나머지 연산으로 계산하면 음수가 되기 때문
        // 나머지 연산은 왼쪽 인자와 우쪽 인자를 모두 양수로 보고 나머지 연산한 후
        // 왼쪽 인자의 부호를 붙이는 방법을 쓰기 때문임.
        // 따라서, a - b =(합동) a - b + MOD (mod MOD) 이더라도
        // 0 <= a, b <= MOD-1에 대해 1 <= a - b + MOD <= 2*MOD-1 < 2^32 - 1이므로
        // a - b + MOD로 써야 음수가 아닌 양수로 제대로 출력됨
     int ret = tiling(width);
    // 한 절반이 다른 절반과 대칭되는 개수를 뺌
    ret = (ret - tiling(width/2) + MOD*does_add_MOD) % MOD;
    // 가운데 가로로 타일을 2개를 깔았을 때
    // 왼쪽 타일의 패턴과 오른쪽 타일의 패턴이 일치되는 개수를 뺌
    ret = (ret - tiling(width/2-1) + MOD*does_add_MOD) % MOD;
    return ret;
}

// 코드 8.20 직접 비대칭 타일링의 수를 세는 동적 계획법 알고리즘

int cache2[101];

int asymmetric2(int width)
{
    if(width <= 2)
    {
        return 0;
    }

    int& ret = cache2[width];
    if(ret != -1)
    {
        return ret;
    }

    ret = asymmetric2(width-2) % MOD; // (a)
    ret = (ret + asymmetric2(width-4)) % MOD; // (b)
    ret = (ret + tiling(width-3)) % MOD; // (c)
    ret = (ret + tiling(width-3)) % MOD; // (d)

    return ret;
}

int main(void)
{
    int start = 0, end = 10;
    printf("-----------------------\nasymmetric\n");
    printf("-----------------------\nMOD를 더하지 않을 때\n");
    for(int i = start; i < end; ++i)
    {
        printf("%d\n", asymmetric(i, 0));
    }
    printf("-----------------------\nMOD를 더할 때\n");
    for(int i = start; i < end; ++i)
    {
        printf("%d\n", asymmetric(i, 1));
    }

    printf("-----------------------\nasymmetric2\n");
    for(int i = 0; i < 102; ++i)
    {
        cache2[i] = -1;
    }
    for(int i = 0; i < 20; ++i)
    {
        printf("%d\n", asymmetric2(i));
    }

    return 0;
}