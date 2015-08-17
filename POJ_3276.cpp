//经典的反转开关问题（见挑战程序设计竞赛3.2）
//枚举k
//第一头牛只被一个区间包含， 所以在确定第一头牛的是否反转，就可以确定第二头牛是否反转， 同样可以继续确定下去， 每次缩小一个
//区间
//所以每头牛当前是否需要翻转， 是由前面的k-1头牛翻转状态决定的， 用r[i]来记录区间[i, i+k-1]是否进行了翻转，
//如果单纯的在枚举之后， 然后暴力翻转每头牛， 然后对当前牛之前的k-1头牛的翻转状态进行统计的话， 最坏的时间复杂度将达到O(n^3)
//所以要进行优化， 显然在计算k-1头牛翻转状态的时候， 可以利用之前的结果进行递推。 这样可以省去一维而将时间复杂度将至O(n^2)


#include<cstdio>
#include<cstring>
using namespace std;
const int N = 5010;

int r[N], dir[N];
int n;

int solve(int k){
    memset(r, 0, sizeof(r));
    int ans = 0, sum = 0;
    for(int i = 0; i+k <= n; ++i){
        if((sum + dir[i]) & 1){
            ++ans;
            r[i] = 1;
        }

        sum += r[i];
        if(i-k+1 >= 0){
            sum -= r[i-k+1];
        }
    }

    for(int i = n-k+1; i < n; ++i){
        if((sum + dir[i]) & 1){
            return -1;
        }
        if(i-k+1 >= 0){
            sum -= r[i-k+1];
        }
    }
    return ans;
}

int main(){
    scanf("%d", &n);
    char op[2];
    for(int i = 0; i < n; ++i){
        scanf("%s", op);
        if(op[0] == 'B'){
            dir[i] = 1;
        }
        else{
            dir[i] = 0;
        }
    }

    int K, M = n;
    for(int k = 1; k <= n; ++k){
        int tmp = solve(k);
        if(tmp > 0 && tmp < M){
            M = tmp;
            K = k;
        }
    }
    printf("%d %d\n", K, M);
    return 0;
}
