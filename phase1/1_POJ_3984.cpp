//迷宫问题
//经典bfs问题， 用string记录路径
//值得记录的是， string的操作问题， sprintf的使用
//


#include<cstdio>
#include<string>
#include<queue>
#include<iostream>
using namespace std;
int fx[4] = {0, 1, -1, 0};
int fy[4] = {1, 0, 0, -1};
int maze[6][6];

typedef struct node{
    int x, y;
    string op;
    node(int x_, int y_, string op_):x(x_), y(y_), op(op_){}
}node;

queue<node > q;

void bfs(int x, int y){
    while(!q.empty()) q.pop();
    maze[x][y] = 1;
    node tmp(x, y, "");
    q.push(tmp);

    char buf[3];
    string buf_;
    while(!q.empty()){
        node p = q.front();
        q.pop();
        for(int i = 0; i < 4; ++i){
            int dx = p.x + fx[i];
            int dy = p.y + fy[i];
            if(dx >= 0 && dx < 5  && dy >= 0 && dy < 5 && maze[dx][dy] == 0){
                sprintf(buf, "%d", i);
                buf_ = buf;
                if(dx == 4 && dy == 4){
                    printf("(0, 0)\n");
                    int sx = 0, sy = 0;
                    for(int j = 0; j < p.op.size(); ++j){
                        int ops = p.op[j] - 48;
                        sx = sx + fx[ops];
                        sy = sy + fy[ops];
                        printf("(%d, %d)\n", sx, sy);
                    }
                    printf("(4, 4)\n");
                    return ;
                }
                tmp.x = dx, tmp.y = dy, tmp.op = p.op+buf_;
                q.push(tmp);
            }
        }
    }
}

int main(){
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            scanf("%d", &maze[i][j]);
        }
    }
    bfs(0, 0);
    return 0;
}
