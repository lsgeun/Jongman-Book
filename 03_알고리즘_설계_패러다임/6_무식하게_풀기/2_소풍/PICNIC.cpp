// 코드 6.4 소풍 문제를 해결하는 (잘못된) 재귀 호출 코드

int n;
bool areFriends[10][10];
// taken[i] = i번째 학생이 짝을 이미 찾았다면 true, 아니면 false
int countPairings(bool taken[10])
{
    // 기저 사례: 모든 학생이 짝을 찾았으면 true, 아니면 false
    bool finished = true;
    for(int i = 0; i < n; ++i) { if( taken[i] == false ) { finished = false; } }
    if( finished ) { return 1; }
    int ret = 0;
    // 서로 친구인 두 학생을 찾아 짝을 지어 준다.
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if( taken[i] == false && taken[j] == false && areFriends[i][j] )
            {
                taken[i] = taken[j] = true;
                ret += countPairings(taken);
                taken[i] = taken[j] = false;
            }
        }
    }
    return ret;
}

// 문제점: 올바른 경우를 찾는 알고리즘은 맞으나 중복이 된 케이스가 존재함. 따라서 짝의 수를 셀 때 중복해서 세는 경우가 발생할 수도 있음.
// 해결법: 순서를 강제함으로써 중복을 없앰. 오름차나 내림차순으로 순서를 강제하면 됨.

// 코드 6.5 소풍 문제를 해결하는 재귀 호출 코드

int n;
bool areFriends[10][10];
// taken[i] = i번째 학생이 짝을 이미 찾았으면 true, 아니면 false
int countPairings(bool taken[10])
{
    // 남은 학생들 중 가장 번호가 빠른 학생을 찾는다.
    int firstFree = -1;
    for(int i = 0; i < n ++i)
    {
        if( taken[i] == false )
        {
            firstFree = i;
            break;
        }
    }
    // 기저 사례: 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
    if( firstFree == -1 ) { return 1; }
    int ret = 0;
    // 이 학생과 짝지을 학생을 결정한다.
    for(int pairWith = firstFree+1; pairWith < n; ++pairWith)
    {
        if( taken[pairWith] == false && areFriends[firstFree][pairWith] == true )
        {
            taken[firstFree] = taken[pairWith] = true;
            ret += countPairings(taken);
            taken[firstFree] = taken[pairWith] = false;
        }
    }
    return ret;
}