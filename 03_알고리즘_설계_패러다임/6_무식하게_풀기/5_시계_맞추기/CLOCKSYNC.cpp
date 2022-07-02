// 내 알고리즘

// 이거 될 거 같긴한데 책에서 나온대로 4^10(1048576)개의 경우만 따지면 될 거 같긴 함.
// 입력에서 솔루션으로 가는 방법이 4^10개 중 적어도 한 가지 경우라면 솔루션에서 입력으로 가는 방법도 4^10개 중 적어도 한 가지 경우가 있음.
// 입력에서 솔루션으로 가는 방법이 없다면 솔루션에서 입력으로 가는 방법도 없음.

vector<int> input; // 초기 시계 배열, 입력 값에 따라 달라짐.
vector<int> clock; // 현재 시계 배열, 모두 12시로 설정, 즉 솔루션.

// count는 솔루션에서 뒤로 간 횟수임.
// 솔루션에서 초기 입력으로 가장 먼저 도달할 때 그 count 값을 리턴하면 최소의 횟수로 솔루션을 찾을 수 있는 값 중 하나이 됨.
// 뒤에서부터 모든 경우를 따져서 앞으로 가는데 제일 먼저 입력값을 찾는 count 값을 찾는 거임.
// 0~9 스위치에서 출발하는 것으로 10 가지 경우가 되므로 각 경우에 대한 최솟값을 리턴받을 수 있고 그 값들 중에서 가장 작은 값을 리턴하면 됨.
int ClockMinSwitch(vector<int> clock, int count)
{   

    int count 
}

// 책의 알고리즘

// 코드 6.8 시계 맞추기 문제를 해결하는 완전 탐색 알고리즘

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
// linked[i][j] = 'x': i번 스위치와 j번 시계가 연결되어 있다.
// linked[i][j] = '.': i번 스위치와 j번 시계가 연결되어 있지 않다.
const char linked[SWITCHES][CLOCKS+1] = 
{ // 0123456789101112131415
 "xxx.............",
 "...x...x.x.x....",
 "....x.....x...xx",
 "x...xxxx........",
 "......xxx.x.x...",
 "x.x...........xx",
 "...x..........xx",
 "....xx.x......xx",
 ".xxxxx..........",
 "...xxx...x...x.."
};
// 모든 시계가 12시를 가리키고 있는지 확인하다.
bool areAligned(const vector<int>& clocks);
// swtch번 스위치를 누른다.
void push(vector<int>& clocks, int swtch)
{
    for(int clock = 0; clock < CLOCKS; ++clocks)
    {
        if(linked[swtch][clock] == 'x')
        {
            clocks[clock] += 3;
            // 12시에서 3을 더해 15시가 될 경우 3시로 바꾼다는 말.
            if(clocks[clock] == 15)
            {
                clocks[clock] = 3;
            }
        }
    }
}
// clocks: 현재 시계들의 상태
// swtch: 이번에 누를 스위치의 번호
// 가 주어질 때, 남은 스위치들을 눌러서 clocks를 12시로 맞출 수 있는 최소 횟수를 반환한다.
// 만약 불가능하다면 INF 이상의 큰 수를 반환한다.

int solve_(vector<int>& clocks, int swtch)
{
    if(swtch == SWITCHES)
    {
        return areAligned(clocks) ? 0 : INF;
    }
    // 이 스위치를 0번 누르는 경우부터 세 번 누르는 경우까지를 모두 시도한다.
    int ret = INF;
    for(int cnt = 0; cnt < 4; ++cnt)
    {
        ret = min(ret, cnt + solve_(clock, swtch+1));
        push(clocks, swtch);
    }
    // push(clocks,swtch)가 네 번 호출되었으니 clocks는 원래와 같은 상태가 된다.
    return ret;
}

// 아직(->지금은) 위의 알고리즘도(알고리즘이) 이해가 안되서(->되서) 아래와 같이 쓰는게 맞는지 모르겠음.(->맞음.)
int solve(vector<int>& clocks)
{
    solve_(clocks, 0);
}