#include "Game.h"

Game :: Game(int n):data(vector<vector<int>>(n,vector<int>(n))),N(n),status(S_NORMAL),maxnumber(0){
    randNew();
    randNew();
}

void Game::draw()
{
    clear();
    const int offset = 12;
    for (int i = 0; i <= N; ++i) 
        for (int j = 0; j <= N; ++j) {
            // 相交点
            drawItem(i * 2, 1 + j * (N+1) + offset, '+');
            // 竖线
            if (i !=  N) 
               drawItem(i * 2 + 1, 1 + j *(N+1) + offset, '|');
            // 横线
            for (int k = 1; j !=  N && k < (N+1) ; ++k) 
                drawItem(i * 2, 1 + j * (N+1)  + k + offset, '-');
            // 每个格子里的数
            if (i !=  N && j !=  N) 
                drawNum(i * 2 + 1, (j + 1) *(N+1)  + offset, data[i][j]);
         }
        // 提示文字
        mvprintw(2 *  N + 2, (5 * ( N - 4) - 1) / 2, "W(UP),S(DOWN),A(LEFT),D(RIGHT),R(RESTART),Q(QUIT)");
        mvprintw(2 *  N + 3, 12 + 5 * ( N - 4) / 2, "https://pansn.xyz");

        if (status == S_WIN) {
            mvprintw( N, 5 * N / 2 - 1, " YOU WIN,PRESS C TO CONTINUE ");
        } else if (status == S_FAIL) {
            mvprintw( N, 5 * N / 2 - 1, " YOU LOSE,PRESS R TO CONTINUE ");
        }
}

void Game::processInput() {
        char ch = getch();
        // 转化成大写
        if (ch >= 'a' && ch <= 'z') 
            ch -= 32;

        if(status==S_WIN)
        {
             if (ch == 'C')
             {
                status = S_NORMAL;
                maxnumber=INT32_MAX;
             }
        }
        if (status == S_NORMAL) {
            int update=0;
            if (ch == 'A') {
                update=moveLeft();
            }else if(ch=='D')
            {
                rotate();
                rotate();
                update=moveLeft();
                rotate();
                rotate();
            }else if(ch=='W')
            {
                rotate();
                rotate();
                rotate();
                update=moveLeft();
                rotate();
            }else if(ch=='S')
            {
                rotate();
                update=moveLeft();
                rotate();
                rotate();
                rotate();
            }
            if(update)
            {
                randNew();
                if(maxnumber==2048)
                    status=S_WIN;
                else if(isOver())
                    status=S_FAIL;
            }
                
        }
        
        if (ch == 'Q') 
            status = S_QUIT;
        else if(ch=='R')
            restart();

    }
