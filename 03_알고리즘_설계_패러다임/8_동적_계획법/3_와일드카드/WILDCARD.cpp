#include <iostream>
#include <string>
// 코드 8.6 와일드카드 문제를 해결하는 완전 탐색 알고리즘

bool match(const std::string& w, const std::string& s)
{
    // w[pos]와 s[pos]를 맞춰나간다.
    int pos = 0;
    while( pos < s.size() && pos < w.size() && 
            (w[pos] == '?') || w[pos] == s[pos])
    {
        ++pos;
    }
    // 2. 3.
    if( pos == w.size() )
    {
        return pos == s.size();
    }
    // 0 <= pos < w.size()
    // 0 <= pos < s.size(), pos == s.size(), s.size() < pos
    // 3. 4.
    if( w[pos] == '*' )
    {
        for( int skip = 0; pos+skip <= s.size(); ++skip )
        {
            if( match(w.substr(pos+1), s.substr(pos+skip)) )
            {
                return true;
            }
        }
    }
    // w[pos] == '?' or w[pos] == '소문자'
    return false;
}

// 8.7 와일드카드 문제를 해결하는 동적 계획법 알고리즘
// 시간 복잡도 O(n^3)
int cache[100+1][100+1];
std::string W, S;

bool matchMemoized(int w, int s)
{
    int& ret = cache[w][s];
    if( ret != -1 )
    {
        return ret;
    }
    while( s < S.size() && w < W.size() && 
        (W[w] == '?' || W[w] == S[s]) )
    {
        ++w;
        ++s;
    }
    // 0 <= s <= S.size()
    // 2. 3.
    if( w == W.size() )
    {
        return ret = (s == S.size());
    }
    // 0 <= w < W.size()
    // 3. 4.
    if(W[w] == '*')
    {
        for( int skip = 0; s+skip <= S.size(); ++skip )
        {
            if( matchMemoized(w+1, s+skip) )
            {
                return ret = 1;
            }
        }
    }
    // W[w] == '?' or W[w] == '소문자'
    return ret = 0;
}
// 시간 복잡도 O(n^2)
// 이거 약간 신기하다.
bool matchMemoized(int w, int s)
{
    int& ret = cache[w][s];
    if( ret != -1 )
    {
        return ret;
    }
    while( s < S.size() && w < W.size() && 
        (W[w] == '?' || W[w] == S[s]) )
    {
        return ret = matchMemoized(w+1, s+1);
    }
    if( w == W.size() )
    {
        return ret = (s == S.size());
    }
    if( W[w] == '*' )
    {
        // || 연산자 특성상 || 앞의 표현식이 true 라면 뒤의 표현식을
        // 평가하지 않음.
        // 즉, 이 경우 연속된 *을 먼저 움직여서 평가받도록 하게 함.
        if( matchMemoized(w+1, s)  ||
            (s < S.size() && matchMemoized(w, s+1)) )
        {
            return ret = 1;
        }
    }
    return ret = 0;
}