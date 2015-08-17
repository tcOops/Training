#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
const int N = 2002;
char s[N];

int main(){
    int n;
    scanf("%d", &n);
    getchar();
    for(int i = 0; i < n; ++i){
        scanf("%c", &s[i]);
        getchar();
    }

    int l = 0, r = n-1;
    int cnt = 1;
    while(l <= r){
        bool flag = false;
        for(int i = 0; l + i <= r; ++i){
            if(s[l+i] < s[r-i]){
                flag = true;
                break;
            }
            else if(s[l+i] > s[r-i]){
                flag = false;
                break;
            }
        }
        if(flag){
            putchar(s[l++]);
        }
        else{
            putchar(s[r--]);
        }
        if(cnt % 80 == 0){
            puts("");
        }
        ++cnt;
    }
    puts("");
    return 0;
}
