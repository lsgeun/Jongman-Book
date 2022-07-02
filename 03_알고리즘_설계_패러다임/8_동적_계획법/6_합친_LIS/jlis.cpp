#include<iostream>

// 코드 8.13 합친 LIS 문제를 해결하는 동적 계획법 알고리즘

const long long NEGINF = std::numeric_limits<long long>::min();
int n, m, A[100], B[100];
int cache[101][101];

// 처음 호출할 경우 항상 indexA == indexB == -1 이다.
// 두번째 이후로 호출할 경우 A[indexA] != B[indexB]을 만족한다.
// A[indexA] > B[indexB] or A[indexA] < B[indexB]가 항상 보장되므로
int jlis(int indexA, int indexB)
{
    int& ret = cache[indexA+1][indexB+1];
    if(ret != -1)
    {
        return ret;
    }

    // A[indexA]와 B[indexB]는 항상 존재하므로
    ret = 2;
    // A[-1] == B[-1] == NEGINF 라는 가상의 값이 존재할 때,
    // a = A[indexA], b = B[indexB]라는 논리를 유지하기 위해서 아래와 같이 씀.
    long long a = (indexA == -1 ? NEGINF : A[indexA]);
    long long b = (indexB == -1 ? NEGINF : B[indexB]);
    long long maxElement = std::max(a,b);

    for(int nextA = indexA + 1; nextA < n; ++nextA)
    {
        // A[indexA], B[indexB] <= maxElement 이므로
        // maxElement < A[nextA] 일 경우
        // A[nextA] > B[indexB] 가 항상 보장됨.
        if(maxElement < A[nextA])
        {
            // ret >= 2
            ret = std::max(ret, jlis(nextA, indexB)+1);
        }
    }
    for(int nextB = indexB + 1; nextB < n; ++nextB)
    {
        // A[indexA] < B[nextB]가 항상 보장됨.
        if(maxElement < B[nextB])
        {
            // ret >= 2
            ret = std::max(ret, jlis(indexA, nextB)+1);
        }
    }
    // ret >= 2
    return ret;
}
// 좀 어렵긴 한데 다시 한 번 보면 알 수 있지 않을까?
// jlis(-1, -1)이면 그 값이 A, B에 대한 jils의 길이일 것 같다.
// lis3처럼 lis3(-1, -1) - 1과 같이 빼는 과정은 필요 없을 것 같다.