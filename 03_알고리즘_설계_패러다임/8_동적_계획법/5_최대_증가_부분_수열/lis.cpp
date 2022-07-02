#include <iostream>
#include <vector>

// 코드 8.10 최대 증가 부분 수열 문제를 해결하는 완전 탐색 알고리즘

int lis(const std::vector<int>& A)
{
    if(A.empty())
    {
        return 0;
    }

    int ret = 0;
    for(int i = 0; i < A.size(); ++i)
    {
        std::vector<int> B;
        for(int j = i+1; j < A.size(); ++j)
        {
            if(A[i] < A[j])
            {
                B.push_back(A[j]);
            }
        } 
        ret = std::max(ret, 1 + lis(B));
    }
    return ret;
}

// 코드 8.11 최대 증가 부분 수열 문제를 해결하는 동적 계획법 알고리즘(1)

int n;
int cache[100], S[100];

int lis2(int start)
{
    int& ret = cache[start];
    if(ret != -1)
    {
        return ret;
    }
    // S[start]의 값은 항상 존재하니 적어도 길이는 1이상임.
    ret = 1;
    for(int next = start+1; next < n; ++next)
    {
        if(S[start] < S[next])
        {
            ret = std::max(ret, lis2(next) + 1);
        }
    }
    return ret;
}
/*
예를 들어, main 문에
int maxLen = 0;
for(int begin = 0; begin < n; ++ begin)
{
    maxLen = std::max(maxLen, lis2(begin))
}
을 추가해야 하여 사용함.
for 문을 빼고 구현하려면 아래와 같이 구현하면 됨.
*/

// 코드 8.12 최대 증가 부분 수열 문제를 해결하는 동적 계획법 알고리즘(2)

// int n;
// int cache[101], S[100];
int lis3(int start)
{
    int& ret = cache[start+1];
    if(ret != -1)
    {
        return ret;
    }

    ret = 1;
    for(int next = start+1; next < n; ++next)
    {
        if(start == -1 || S[start] < S[next])
        {
            ret = std::max(ret, lis3(next) + 1);
        }
    }
    return ret;
}
/*
예를 들어, main 문에
lis3(-1) - 1;
을 적어서 사용함.
*/

