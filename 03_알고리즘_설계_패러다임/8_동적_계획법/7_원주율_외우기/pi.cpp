#include <iostream>
#include <string>

// 코드 8.14 원주율 외우기 문제를 해결하는 동적 계획법 알고리즘
const int INF = 987654321;
std::string N;

int classify(int a, int b)
{
    std::string M = N.substr(a, b-a+1);
    // M이 같은 수로만 되어있다면
    if(M == std::string(M.size(), M[0]))
    {
        return 1;
    }
    // M이 등차수열인지 확인
    bool progressive = true;
    for(int i = 0; i < M.size()-1; ++i)
    {
        if(M[i+1] - M[i] != M[1] - M[0])
        {
            progressive = false;
        }
    }
    // M이 공차가 1인 등차수열이라면
    if(progressive && std::abs(M[1] - M[0]) == 1)
    {
        return 2;
    }
    // M에 두 수가 번갈아 나타나는지 확인
    bool alternating = true;
    for(int i = 0; i < M.size(); ++i)
    {
        if(M[i] != M[i%2])
        {
            alternating = false;
        }
    }
    // M에 두 수가 번갈아 나타난다면
    if(alternating)
    {
        return 4;
    }
    // 공차가 1이 아닌 등차수열라면
    if(progressive)
    {
        return 5;
    }
    // 위에 언급된 기준이 모두 아니라면
    return 10;
}

int cache[100002];

int memorize(int begin)
{
    // begin <= N.size()
    // begin을 포함한 이후의 원소들이 0인 경우 난이도는 0이다.
    if(begin == N.size())
    {
        return 0;
    }
    // begin < N.size()
    int& ret = cache[begin];
    if(ret != -1)
    {
        return ret;
    }

    ret = INF;
    for(int L = 3; L <= 5; ++L)
    {
        // begin을 포함한 이후의 원소들이 1개 이나 2개일 경우
        // 재귀호출이 되지 않으므로 난이도는 INF이 된다.
        // begin을 포함한 이후의 원소들이 3개 이상일 경우만 재귀호출된다.
        if(begin + L <= N.size())
        {
            ret = std::min(ret, memorize(begin + L) +
                            classify(begin, begin + L - 1));
        }
    }
    return ret;
}