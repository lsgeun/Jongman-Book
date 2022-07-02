// 코드 8.4 외발 뛰기 문제를 해결하는 재귀 호출 알고리즘

int n , board[100][100];
bool jump(int y, int x)
{
    // 기저 사례: 게임판 밖을 벗어난 경우
    if(y >= n || x >= n)
    {
        return false;
    }
    // 기저 사례: 마지막 칸에 도착한 경우
    if(y == n-1 && x == n-1)
    {
        return false;
    }
    int jumpSize = board[y][x];
    return jump(y + jumpSize, x) || jump(y, x + jumpSize);
}

// 코드 8.5 외발 뛰기 문제를 해결하는 동적 계획법 알고리즘

int n, board[100][100];
int cache[100][100];
int jump2(int y, int x)
{
    // 불변식1: 자기가 호출한 재귀 함수에 자기가 다시 호출되지 않는다. <-- 아마도?
    // 불변식1가 아니라면 공간복잡도와 시간복잡도가 무한임.
    // 함수 마지막 줄 return 쪽에서 아니라는 것이 나오는 거 같음.
    // 기저 사례 처리
    if(y >= n || x >= n)
    {
        return 0;
    }
    if(y == n-1 && x == n-1)
    {
        return 1;
    }
    // 메모이제이션
    // 불변식2: (y <= n-1 && x < n-1) || (y < n-1 && x <= n-1) <-- 확실
    int& ret = cache[y][x];
    if(ret != -1) // -1: None Calculation
    {
        return ret;
    }
    int jumpSize = board[y][x];
    return ret = (jump2(y + jumpSize, x) ||
                  jump2(y, x + jumpSize));
}