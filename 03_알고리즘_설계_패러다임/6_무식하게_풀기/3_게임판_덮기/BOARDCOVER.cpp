// 내 알고리즘
// 객체지향언어로써 클래스 안의 속성이라고 생각하면 더 좋을 듯

// 검증은 안 해봄.

int H, W;
int board[H][W];
enum {tromino, black, white};
enum {first, second};
enum {x, y};
int xy[4][2][2] = { {{-1, -1},{0, -1}}, {{0, -1},{1, -1}}, {{0, 1},{1, 1}}, {{1, 0},{1, -1}}};

int countBoardTromino(int board[H][W])
{
    int count = 0;
    int i, j, k;
    bool isWhiteIn = false, isTrominoIn = false;
    // 위에서 아래로 왼쪽에서 오른쪽으로 이동하는데 (0, 0)에서 이동.
    for(i = 0; i < H && !(isWhiteIn); ++i)
    {
        for(j = 0; j < W && !(isWhiteIn); ++j)
        {
            if( board[i][j] == tromino )
            {
                isTrominoIn = true;
            }
            if( board[i][j] == white )
            {
                isWhiteIn = true; 
                for(k = 0; k < 4; ++k)
                {
                    int x0 = i + xy[k][first][x], x1 = i + xy[k][second][x], y0 = j + xy[k][first][y], y1 = j + xy[k][second][y];
                    // 보드 밖에 있는 경우인지 확인
                    if( (0<=x0&&x0<=H-1 && 0<=y0&&y0<=W-1) && (0<=x1&&x1<=H-1 && 0<=y1&&y1<=W-1) )
                    {
                        if( board[x0][y0] == white && board[x1][y1] == white)
                        {
                            // tromino로 색칠하고
                            board[i][j] = board[x0][y0] = board[x1][y1] = tromino;
                            // 개수 센 다음
                            count += countBoardTromino(board);
                            // 다시 white로 비워두고
                            board[i][j] = board[x0][y0] = board[x1][y1] = white;
                        }
                        else // 색칠할 블록 중 하나라도 white가 아닐 때, 즉 tromino이거나 black일 경우,
                             // count에 0을 더함. 즉, 아무것도 하지 않음.
                        {
                            // count += 0;
                        }
                    }
                    else // 보드 밖에 있는 경우, count에 0을 더함. 즉, 아무것도 하지 않음.
                    {
                        // count += 0;
                    }
                }
            }
        }
    }
    if( (isTrominoIn == true) && (isWhiteIn == false) )
    {
        return 1;
    }
    return count;
}