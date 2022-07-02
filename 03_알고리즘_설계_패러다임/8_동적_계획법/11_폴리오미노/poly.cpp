#include <iostream>

const int MOD = 10*100*1000;
int cache[101][101];

// 최초 입력시
// 1. 0 <= first <= n <= 100 이면 반환값은 양의 정수이고
//    0 <= first <= n <= 100 을 만족하도록 재귀호출함.
// 2. 0 <= n < first <= 100 이면 반환값은 0임.
//    그리고 재귀 호출하지 않음.
// 3. 추가한 것
//    함수 header에 int first = 0로 디폴트 값을 주어서 first를 선언함.
//    if(first == 0){...}을 추가하여 함수에 n의 값만 인자로 전달했을 때
//    n개로 만들어지는 세로 단조 폴리오미노의 수를 반환하도록 했음.
int poly(int n, int first = 0)
{
    // 0 <= first, n <= 100
    if(n == first)
    {
        return 1;
    }
    // n != first
    // i.e. n > first or n < first
    int& ret = cache[n][first];
    if(ret != -1)
    {
        return ret;
    }

    ret = 0;

    // n개로 만들어지는 세로 단조 폴리오미노 개수를 반환
    if(first == 0)
    {
         for(int second = 1; second <= n - first; ++second)
         {
            ret = (ret + poly(n, second)) % MOD;
         }
         return ret;
    }
    // 1 <= first <= 100
    for(int second = 1; second <= n - first; ++second)
    {
        // n > first
        int add = second + first - 1;
        add *= poly(n-first, second);
        add %= MOD;
        ret += add;
        ret %= MOD;
    }
    // ret는 MOD의 나머지이므로 0 <= ret <= MOD - 1;
    return ret;
}

int main(void)
{
    for(int i = 0; i< 102; ++i)
    {
        for(int j = 0; j< 102; ++j)
        {
            cache[i][j] = -1;
        }
    }

    for(int i = 1; i <= 10; ++i)
    {
        std::cout << poly(i, 3) << '\n';
    }

    return 0;
}