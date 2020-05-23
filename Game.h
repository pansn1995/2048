#include <vector>
#include <cstdlib>
#include <algorithm>
#include <curses.h>
#include <queue>
using namespace std;

#define S_FAIL 0
#define S_WIN 1
#define S_NORMAL 2
#define S_QUIT 3


class Game{
public:
    Game(int n);
    void draw();
    inline int getStatus(){return status;}
    void processInput();

private:
    void drawItem(int row, int col, char c) {//画框
        move(row, col);
        addch(c);
    }

    void drawNum(int row, int col, int num){//画数字
        while (num > 0) {
            drawItem(row, col, num % 10 + '0');
            num /= 10;
            --col;
        }
    }
    
    void restart() {
        for (int i = 0; i < N; ++i) 
            for (int j = 0; j < N; ++j) 
                data[i][j] = 0;

        randNew();
        randNew();
        status = S_NORMAL;
        maxnumber=0;
    }

      bool randNew() {
        vector<pair<int,int>> emptyPos;
        // 把空位置先存起来
        for (int i = 0; i < N; ++i) 
            for (int j = 0; j < N; ++j) 
                if (data[i][j] == 0) 
                    emptyPos.push_back({i,j});

        if (emptyPos.size() == 0) {
            return false;
        }
        // 随机找个空位置
        auto value = emptyPos[rand() % emptyPos.size()];
        // 10%的概率产生4
        int r=rand() % 10 == 1 ? 4 : 2;
        data[value .first][value.second] = r;
        return true;
    }
    
    int  moveLeft() {
        int z=0;
        for(int i=0;i<N;i++)
        {
            vector<int> v=data[i];
            queue<int> que;
            for(int j=0;j<N;j++)
                if(data[i][j])
                    que.push(data[i][j]);
            if(que.empty())continue;
            if(que.size()==1)
            {
                data[i][0]=que.front();
                for(int j=1;j<N;j++)
                    data[i][j]=0;
            }else
            {
                int start=0;
                int x=que.front();
                que.pop();
                while(que.size())
                {
                    if(x==que.front())
                    {
                        data[i][start]=2*x;
                        maxnumber=max(maxnumber,2*x);
                        start++;
                        que.pop();
                        if(que.size())
                        {
                            x=que.front();
                            que.pop();
                        }else
                            x=0;
                    }else
                    {
                        data[i][start]=x;
                        start++;
                        x=que.front();
                        que.pop();
                    }
                }
                data[i][start]=x;
                start++;
                while(start<N)
                {
                    data[i][start]=0;
                    start++;
                }
            }
            if(!equal(v.begin(),v.end(),data[i].begin(),data[i].end()))
                z=1;
        }
        return z;
    }
    bool isOver() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                // 有空位或者相邻有一样的都可以继续
                if ((j + 1 < N) && (data[i][j] * data[i][j+1] == 0 || data[i][j] == data[i][j+1])) return false;
                if ((i + 1 < N) && (data[i][j] * data[i+1][j] == 0 || data[i][j] == data[i+1][j])) return false;
            }
        }
        return true;
    }

    void ro(vector<vector<int>>& matrix,int ii,int ij,int xi,int xj)
    {
        if(xi<=ii)
            return ;
        int n=xi-ii;
        for(int i=0;i<n;i++)
        {
            int t=matrix[ii][ij+i];
            matrix[ii][ij+i]=matrix[xi-i][ij];
            matrix[xi-i][ij]=matrix[xi][xj-i];
            matrix[xi][xj-i]=matrix[ii+i][xj];
            matrix[ii+i][xj]=t;
        }
        ro(matrix,++ii,++ij,--xi,--xj);
    }

    void rotate() {//矩阵顺时针旋转九十度
        ro(data,0,0,N-1,N-1);
    }
private:
    vector<vector<int>> data;
    int N;
    int status;
    int maxnumber;
};
