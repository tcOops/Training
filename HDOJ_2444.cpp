//二分图匹配简单题
//题目首先要求判断图是否为二分图
//这里有经典的dfs染色算法可以用来进行判断， 算法具体流程很像对图进行染色（0表示未染色， 1表示染成白色， -1表示染成黑色）
//得到一个二分图之后， 可以用经典的hungary算法对二分图求最大匹配
//hungary算法的核心部分也是用dfs找增广路， 当找到增广路之后就可以将之前匹配好的路径进行求反， 从而获得更大的一个匹配
//既然这里都用到了求增广路的思想， 所以二分图也可以用网络流算法进行求解， 后面会涉及到


#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int N = 201;
vector<int > g[N];
int col[N];
bool vis[N];
int n, m;
int link[N];


bool dfs(int u, int c){
    col[u] = c;
    for(int i = 0; i < g[u].size(); ++i){
        int v = g[u][i];
        if(col[v] == c)return false;
        if(col[v] == 0 && !dfs(v, -c)) return false;
    }
    return true;
}

bool isBiGraph(){
    for(int i = 1; i <= n; ++i){
        if(col[i] == 0){
            if(!dfs(i, 1)){
                return false;
            }
        }
    }
    return true;
}

bool find(int u){
    for(int i = 0; i < g[u].size(); ++i){
        int v = g[u][i];
        if(vis[v] == 0){
            vis[v] = 1;
            if(link[v] == -1 || find(link[v])){
                link[v] = u;
                return true;
            }
        }
    }
    return false;
}

void hungary(){
    int ans = 0;
    for(int i = 1; i <= n; ++i){
        memset(vis, 0, sizeof(vis));
        if(find(i)){
            ++ans;
        }
    }
    printf("%d\n", ans>>1);
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        for(int i = 1; i <= n; ++i){
            g[i].clear();
        }
        for(int i = 0; i < m; ++i){
            int x, y;
            scanf("%d%d", &x, &y);
            g[x].push_back(y);
            g[y].push_back(x);
        }

        memset(link, -1, sizeof(link));
        memset(col, 0, sizeof(col));

        if(!isBiGraph()){
            printf("No\n");
        }
        else{
            hungary();
        }
    }
    return 0;
}
