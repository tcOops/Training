//[提交地址](http://www.tyvj.cn/p/1228)
//有道搜索框， 给出一个词库， 查询时输出以查询字符串为前缀的字典序前8个查询结果
//经典数据结构-：字典树(trie)
//字典树主要操作有： Insert & find, 分别表示字典树的建立， 以及查询
//getRes函数使用了递归查询，由于需要按字典树输出， 所以先序遍历的结果便能满足条件
//如果字典的数据量特别大， 则需要考虑更深层次的问题， 比如外部排序， 比如结合堆排


#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 30;
char s[N], ans[N];

typedef struct trie{
    int val;
    bool isWord;
    trie *next[26];
    trie(){
        for(int i = 0; i < 26; ++i){
            next[i] = NULL;
        }
        isWord = false;
    }
}trie, *Trie;

Trie root;
int cnt = 0, limit;

void insert(char *word){
    Trie p = root, q;
    int idx = 0;
    while(word[idx] != '\0'){
        int pos = word[idx] - 'a';
        if(p->next[pos] == NULL){
            q = new trie;
            q->val = pos + 'a';
            p->next[pos] = q;
        }
        p = p->next[pos], ++idx;
    }
    p->isWord = true;
}

void getRes(Trie root, int pos, char *ans){
    ans[pos] = root->val;
    if(root->isWord && cnt < limit){
        for(int i = 0; s[i+1]; ++i){
            printf("%c", s[i]);
        }
        ans[pos+1] = '\0';
        printf("%s ", ans);
        ++cnt;
    }
    
    for(int i = 0; i < 26 && cnt < limit; ++i){
        if(root->next[i] != NULL){
            getRes(root->next[i], pos+1, ans);
        }
    }
}

bool find(char *word){
    int pos = 0;
    Trie p = root;
    
    while(word[pos]){
        int val = word[pos] - 'a';
        if(p->next[val] != NULL){
            p = p->next[val];
        }
        else{
            break;
        }
        ++pos;
    }
    
    if(word[pos]){
        return false;
    }
    
    getRes(p, 0, ans);
    return true;
}


int main(){
    int n, m;
    scanf("%d", &n);
    
    root = new trie;
    for(int i = 0; i < n; ++i){
        scanf("%s", s);
        insert(s);
    }
    
    scanf("%d", &m);
    limit = 8;
    for(int i = 0; i < m; ++i){
        scanf("%s", s);
        cnt = 0;
        bool ret = find(s);
        if(!ret){
            printf("%s", s);
        }
        puts("");
    }
    return 0;
}