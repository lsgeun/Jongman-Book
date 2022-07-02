// 내 풀이

// 무식하게 풀기
// 책을 보고나니 이건 무식하게 풀기가 아님. 조금 더 효율적인 어딘가의 알고리즘.

vector<int> boardHeight; // 입력 순서대로 back_push한 판자들

// 'vector<int> boardHeight'에서
// 책의 코드 7.7처럼 'const'와 '&'를 추가해 'const vector<int>& boardHeight'로 만듦
// 1. 값이 복사가 되지 않아 속도가 더 빠르고 2. 레퍼런스로 그냥 변수처럼 사용할 수 있으며 3. const로 값을 변경할 걱정도 없음.
int getMaxCutBoard (const vector<int>& boardHeight)
{
    int max_size = 0;
    for(vector::iterator iter_i = boardHeight.start(); iter_i != boardHeight.end(); ++iter_i)
    {
        int max_i = (*iter_i);
        vector::iterator iter_sameValue;

        for(iter_sameValue = iter_i-1; boardHeight.start() <= iter_sameValue; --iter_sameValue)
        {
            if((*iter_sameValue) < (*iter_i))
            {
                break;
            }
            max_i += (*iter_i);
        }

        for(iter_sameValue = iter_i+1; iter_sameValue <= boardHeight.end()-1; ++iter_sameValue)
        {
            if((*iter_sameValue) < (*iter_i))
            {
                break;
            }
            max_i += (*iter_i);
        }
        if(max_size < max_i)
        {
            max_size = max_i;
        }
    }
    return max_size;
}
// 길이가 모두 같을 때, W(n) = O(n^2)
// 길이가 모두 다를 때, B(n) = O(n)

// 책 풀이 ------------------------------------------------------------------------------------------------------------------------

// 무식하게 풀기
// 코드 7.7 울타리 잘라내기 문제를 해결하는 O(n^2) 알고리즘

// 판자의 높이를 담은 배열 h[]가 주어질 때 사각형의 최대 너비를 반환한다.
int bruteForce(const vector<int>& h)
{
    int ret = 0;
    int N = h.size();
    // 가능한 모든 left, right 조합을 순회한다.
    for(int left = 0; left < N; ++left)
    {
        int minHeight = h[left];
        for(int right = left; right < N; ++right)
        {
            minHeight = min(minHeight, h[right]);
            ret = max(ret, (right - left + 1) * minHeight);
        }
    }
    return ret;
}
// comment: 이게 진짜 brute force 방식이다.

// 분할 정복
// 코드 7.8 울타리 잘라내기 문제를 해결하는 분할 정복 알고리즘

vector<int> h;
int solve(int left, int right)
{
    // 기저 사례: 판자가 하나밖에 없는 경우
    if(left == right)
    {
        return h[left];
    }
    // [left,mid], [mid+1,right]의 두 구간으로 문제를 분할한다.
    int mid = (left + right) / 2;
    // 분할한 문제를 각개격파(일면 분할 정복인가?), 부분 문제 1, 2
    int ret = max(solve(left,mid), solve(mid+1,right));
    // 부분 문제 3: 두 부분에 모두 걸치는 사각형 중 가장 큰 것을 찾는다.
    int lo = mid, hi = mid+1;
    int height = min(h[lo], h[hi]);
    // [mid,mid+1]만 포함하는 너비 2인 사각형을 고려한다.
    ret = max(ret, height * 2);
    // 사각형이 입력 전체를 덮을 때까지 확장해 나간다.
    while(left < lo || hi < right)
    {
        // 항상 높이가 더 높은 쪽으로 확장한다.
        if(hi < right && (lo == left || h[lo-1] < h[hi+i]))
        {
            ++hi;
            height = min(height, h[hi]);
        }
        else
        {
            --lo;
            height = min(height, h[lo]);
        }
        // 확장한 후 사각형의 넓이
        ret = max(ret, height * (hi - lo + 1));
    }
    return ret;
}
// comment: 알고리즘은 빠르겠지만 가독성이 있는 코드는 아니다. c나 c++ 낮은 버전에 대한 호환성도 없다.

//TODO
// STEP 1
// if문을 단순화하는 방법 강구
if(left < lo && hi < right)
{
    // case1: (left < lo) && (hi < right) && (h[lo-1] < h[hi+1])
    if(h[lo-1] < h[hi+1])
    {
        ++hi;
        height = min(height, h[hi]);
    }
    // case2: (left < lo) && (hi < right) && (h[lo-1] >= h[hi+1])
    else // h[lo-1] >= h[hi+1]
    {
        --lo;
        height = min(height, h[lo]);
    }
}
// case3: (left == lo) && (hi < right)
//       =(left == lo) && (hi < right) && ((h[lo-1] < h[hi+1]) || (h[lo-1] >= h[hi+1])), 부울대수에 의해
else if(left == lo) // (left == lo) && (hi < right)
{
    ++hi;
    height = min(height, h[hi]);
}
// case4: (left < lo) && (hi == right)
//       =(left < lo) && (hi == right) && ((h[lo-1] < h[hi+1]) || (h[lo-1] >= h[hi+1])), 부울대수에 의해
else // (left < lo) && (hi == right)
{
    --lo;
    height = min(height, h[lo]);
}

// STEP 2

// FACT
// case1, case2, case3, case4는 mutual exclusive함.

// NOTATION
// A = (left < lo) ,  B = (hi < right) ,  C = (h[lo-1] < h[hi+1])
// ^A = (left == lo), ^B = (hi == right), ^C = (h[lo-1] >= h[hi+1])라 정의.

// case2: AB^C, case4: A^B
// case(2+4) = AB^C+A^B = A(B^C+^B) = A(B+^B)(^C+^B)
//           = A(^C+^B)
//      --lo;
//      height = min(height, h[lo]);

// case1: ABC, case3: ^AB
// case(1+3) = ABC+^AB = B(AC+^A) = B(A+^A)(C+^A)
//           = B(C+^A)
//      ++hi;
//      height = min(height, h[hi]);

// ^case(1+3) = ^(B(C+^A)) = ^B+^(C+^A) = ^B+^CA = (^B+^C)(^B+A) = (^B+^C)^B+(^B+^C)A
//            = (^B+^C)^B+case(2+4) = (^B^B+^C^B)+case(2+4) = (^B+^C^B)+case(2+4) = ^B(1+^C)+case(2+4)
//            = ^B+case(2+4)
// ^case(1+3) = case(2+4)+(^B+^C)^B => case(1+3) = ^((^B+^C)^B+case(2+4)) => case(1+3) = ^((^B+^C)^B)^case(2+4)
//                                  => case(1+3) = (^(^B+^C)+B)^case(2+4) => case(1+3) = (BC+B)^case(2+4)
//                                  => case(1+3) = B(C+1)^case(2+4)
//                                  => case(1+3) = B^case(2+4)

// ^case(2+4) = ^(A(^C+^B)) = ^A+^(^C+^B) = ^A+CB = (^A+C)(^A+B) = (^A+C)^A+(^A+C)B
//            = (^A+C)^A+case(1+3) = (^A^A+C^A)+case(1+3) = (^A+C^A)+case(1+3) = ^A(1+C)+case(1+3)
//            = ^A+case(1+3)
// ^case(2+4) = (^A+C)^A+case(1+3) => case(2+4) = ^((^A+C)^A+case(1+3)) => case(2+4) = ^((^A+C)^A)^case(1+3)
//                                 => case(2+4) = (^(^A+C)+A)^case(1+3) => case(2+4) = (A^C+A)^case(1+3)
//                                 => case(2+4) = A(^C+1)^case(1+3)
//                                 => case(2+4) = A^case(1+3)

// ^case(1+3) = ^B+case(2+4), case(2+4) = A^case(1+3)
// ^case(2+4) = ^A+case(1+3), case(1+3) = B^case(2+4)