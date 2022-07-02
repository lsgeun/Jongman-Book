#include <iostream>
#include <vector>

// 코드 8.22 두니발 박사의 탈옥 문제를 해결하는 완전 탐색 알고리즘

// n은 마을의 수
// d는 탈옥 후 경과된 시간
// p는 감옥이 있는 마을 번호
// q는 감옥에서 탈옥한 다음 d일이 경과된 후 도착한 마을
int n, d, p, q;
// connected는 마을 간에 통행할 수 있는 산길이 있는지 여부를 알려줌
// deg[i]는 i번째 마을에 인접한 다른 마을의 개수임. 확률 계산할 때 쓰임.
int connected[51][51], deg[51];

int search(std::vector<int>& path)
{
    // 확률을 계산하는 부분
    if(path.size() == d+1)
    {
        if(path.back() != q)
        {
            return 0.0;
        }

        double ret = 1.0;
        // for(int i = 0; i < path.size()-1 - 1; ++i) // 이 표현이 더 적절할 것 같음.
        for(int i = 0; i + 1 < path.size(); ++i)
        {
            ret /= deg[path[i]];
        }
        return ret;
    }
    // 모든 경로를 탐색하는 부분
    double ret = 0;
    for(int there = 0; there < n; ++there)
    {
        if(connected[path.back()][there])
        {
            path.push_back(there);
            ret += search(path);
            path.pop_back();
        }
    }

    return ret;
}

// 코드 8.23 두니발 박사의 탈옥 문제를 해결하는 동적 계획법 알고리즘

// int n, d, p, q; // 위에서 초기화 함.
double cache[51][101];
// int connected[51][51], deg[51]; // 위에서 초기화 함.

// 전체 부분 문제의 수가 n(마을의 수) x d(경과될 시간)이고
// for 문이 n번 도니까 
// d일이 경과된 후 도착할 한 마을에 대한 전체 시간 복잡도는 O(n^2 x d)이다.
// * 한 테스트 케이스의 도착할 마을의 수가 t일 때 시간 복잡도는 O(n^2 x d x t)이다.
// 도착할 마을마다 다시 cache를 계산해야 하기 때문이다.
// 테스트 케이스의 개수가 k개일 때 시간 복잡도는 O(n^2 x d x t x k)이다.
double search2(int here, int days)
{
    if(days == d)
    {
        return (here == q ? 1.0 : 0.0);
    }

    double& ret = cache[here][days];
    if(ret > -0.5) // ? 왜 이런지는 잘 모르겠음.
    {
        return ret;
    }

    ret = 0.0;
    for(int there = 0; there < n; ++there)
    {
        if(connected[here][there])
        {
            ret += search2(there, days+1) / deg[here];
        }
    }

    return ret;
}

// 코드 8.24 두니발 박사의 탈옥 문제를 해결하는 동적 계획법 알고리즘

// int n, d, p, q; // 위에서 초기화 함.
// double cache[51][101]; // 위에서 초기화 함.
// int connected[51][51], deg[51]; // 위에서 초기화 함.

// 전체 부분 문제의 수가 n(마을의 수) x d(경과될 시간)이고
// for 문이 n번 도니까 
// d일이 경과된 후 도착할 한 마을에 대한 전체 시간 복잡도는 O(n^2 x d)이다.
// * 한 테스트 케이스의 도착할 마을의 수가 t일 때 시간 복잡도는 O(n^2 x d)이다.
// 도착할 마을마다 다시 cache를 계산할 필요가 없고 기존의 cache 데이터를 재활용할 수 있기 때문이다.
// 테스트 케이스의 개수가 k개일 때 시간 복잡도는 O(n^2 x d x k)이다.
double search3(int here, int days)
{
    if(days == 0)
    {
        return (here == p ? 1.0 : 0.0);
    }

    double& ret = cache[here][days];
    if(ret > -0.5)
    {
        return ret;
    }

    ret = 0.0;
    for(int there = 0; there < n; ++there)
    {
        if(connected[here][there])
        {
            ret += search3(there, days-1) / deg[there];
        }
    }

    return ret;
}