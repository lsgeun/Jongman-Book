#include <iostream>

// 코드 8.15 Quantization 문제의 구현

const int INF = 987654321;

int n;
int A[101], pSum[101], pSqSum[101];

void precalc()
{
    // 시간 복잡도는 O(n)이다.
    std::sort(A, A+n);
    pSum[0] = A[0];
    pSqSum[0] = A[0]*A[0];
    for(int i = 1; i < n; ++i)
    {
        pSum[i] = pSum[i-1] + A[i];
        pSqSum[i] = pSqSum[i-1] + A[i]*A[i];
    }
}

int minError(int lo, int hi)
{
    // 브루트포스는 O(n^3)이지만 이 방법은 O(1)
    // 부분 합을 구하기 위한 부분.
    // 삼항 연산자 ( ? : )을 쓴 이유는 lo == 0일 경우
    // 아무 것도 빼면 안 되기 때문.
    int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo-1]);
    int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo-1]);

    int m = int(0.5 + (double)sum / (hi - lo + 1));
    int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);
    return ret;
}

int cache[101][11];
int quantize(int from, int parts)
{
    if(from == n)
    {
        return 0;
    }
    // 0 <= from < n
    if(parts == 0)
    {
        return INF;
    }
    // parts > 0
    int& ret = cache[from][parts];
    if(ret != -1)
    {
        return ret;
    }

    ret = INF;
    // for(int partSize = 1; from + partSize - 1 <= n-1; ++partSize) // minError 끝 인덱스 관점
    for(int partSize = 1; from + partSize <= n; ++partSize) // quantize 시작 인덱스 관점
    {
        ret = std::min(ret, minError(from, from + partSize - 1) +
                        quantize(from + partSize, parts - 1));
    }
    return ret;
}