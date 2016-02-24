//经典搜索题， 虽然数据不大， 但是暴力dfs搜索的复杂度将是阶乘级别(o(n!))
//所以如果搜索过程中， 没有强力剪枝， 肯定是不行的
//所谓剪枝， 是指在搜索的过程中， 在进行解答树拓展的时候， 提前做一些计算进行判断， 如果按某条路径搜下去肯定没有结果， 那么就不要做无用功
//设计剪枝的方法需要总结， 从各种状态入手， 考虑数据的极限情况。

//这道题目有几个经典的剪枝：
//1： dfs到某一个stick的时候， 如果当前这一块的stick长度和加上这个stick刚好为val(设定的stick拼接长度)， 如果这种情况无法拼接的话， 那肯定不能拼接
//因为， 换成其他的效果也一样， 无非就是用几个小的来组合， 那肯定也是不行的（case1）
//
//2. 一个很重要的剪枝， 将stick按长度从大到小排序， 先搜大的。 这样做的好处是， 将越灵活的组合放在后面， 这样获得解的机会更大点。 就可以提前获得结果
//因为， 比如6， 或者2+4, 显然2+4比6更灵活， 将2+4放到后面使用， 具备更多的构造解的可能性。 这是一个关键的剪枝
//
//3. 如果是case2， 也就是当前的和加起来还不够设定值val， 在不选该stick的时候， 可以提前做一些判断： 比如当前的和为0， 那么显然这根stick是无用的，
//所以放到后面也是同样的局面， 这个解空间就是无效的。 或者：如果剩下的stick的总长度都不及这一组所需要的长度， 那肯定也是无效的

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 65;
int l[N];
bool vis[N];
int n, cnt;

bool cmp(const int &x, int const &y){
    return x > y;
}

bool solve(int k, int s, int p, int sum, int val){
    if(k == cnt) return true;

    for(int i = p; i < n; ++i){
        if(vis[i]) continue;

        //case1
        if(s + l[i] == val){
            vis[i] = 1;
            if(solve(k+1, 0, 0, sum-l[i], val))
                return true;
            vis[i] = 0;
                return false;
        }

        //case2
        else{
            if(s + l[i] < val){
                vis[i] = 1;
                if(solve(k, s+l[i], i+1, sum-l[i], val)){
                    return true;
                }
                vis[i] = 0;
                if(s == 0 || sum-l[i] < val-s)
                    return false;
                while(l[i] == l[i+1]){
                    ++i;
                }
            }
        }
    }
    return false;
}

int main(){
    while(~scanf("%d", &n)){
        if(n == 0) break;
        memset(vis, 0, sizeof(vis));
        int sum = 0;
        for(int i = 0; i < n; ++i){
            scanf("%d", &l[i]);
            sum += l[i];
        }

        sort(l, l+n, cmp);
        for(int i = l[0]; i <= sum; ++i){
            if(sum % i == 0){
        //        printf("%d %d\n", i, sum/i);
                cnt = sum / i;
                if(solve(0, 0, 0, sum, i)){
                    printf("%d\n", i);
                    break;
                }
            }
        }
    }
    return 0;
}
