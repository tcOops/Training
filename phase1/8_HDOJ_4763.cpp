//[提交地址](http://acm.hdu.edu.cn/showproblem.php?pid=4763)
//把一个字符串映射成'EAEBE',求最长的E
//KMP的经典题目， 关键要了解next数组的本质含义
//next数组的意义在于求最大长度的前缀跟后缀满足相等的条件
//在j = next[j]的过程中， 始终满足前缀跟后缀尽可能长的相等， 这一点性质可以让我们不停的迭代求解
//这样我们可以不停的枚举EAEBE中一头一尾的E， 剩下的事情是在剩下的字符串中寻找另外一个E， 这刚好可以用kmp搞定


#include<cstdio>
#include<cstring>
using namespace std;
const int N = 1e6 + 10;
char s[N];
int next[N], n, len;

void Gen_next(){
    next[0] = -1;
    int j = -1;
    for(int i = 1; i < n; ++i){
        while(j >= 0 && s[j+1] != s[i]){
            j = next[j];
        }
        if(s[i] == s[j+1]) ++j;
        next[i] = j;
    }
}

bool kmp(int a, int b){
    int j = -1;
    for(int i = a; i <= b; ++i){
        while(j >= 0 && s[j+1] != s[i]){
            j = next[j];
        }
        if(s[i] == s[j+1]) ++j;
        if(j == len) return true;
    }
    return false;
}

int main(){
    int m;
    scanf("%d", &m);
    while(m--){
        scanf("%s", s);
        n = (int)strlen(s);
        Gen_next();
        int i = n - 1;
        while(i > ((n/3) - 1)){
            i = next[i];
        }
        
        int ans = 0;
        while(i >= 0){
            len = i;
            bool success = kmp(i+1, n-i-1);
            if(success){
                ans = i + 1;
                break;
            }
            i = next[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}