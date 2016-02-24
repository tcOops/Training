//经典的并查集问题， 程序虽然很短， 但是运用了不少的东西
//这道题目给出A，B，C三种类型的动物， A->B, B->C, C->A 循环食物链
//给出一些描述， 一共分两种： 1 X Y 表示X，Y同类，  2 X Y 表示X可以吃Y
//这些描述中如果与之前的状态冲突， 那么就是假话， 需要找出所有的假话
//
//很快就可以分析出应该用并查集来解决。 OK， fa数组维护是否属于一个集合
//但是普通意义上的并查集并不能完整表示状态， 因为仅仅能维护属于同一种生物的集合是不能判断谁能吃谁， 所以需要一些附加状态
//所以改变思维方式， 增加一个rank数组， 将fa数组的意义设置成： 当两个动物的关系确定的时候放在一个集合， 也就是有一个共同的fa. 而rank数组表示的是x与fa[x]之间
//的关系 依据题目的意思， rank数组的取值有三种， 将其设置为0,1,2(0表示x与fa[x]是同类生物， 1表示x被fa[x]吃， 2表示x吃fa[x]）
//所以在合并的时候， 既需要设置fa的关系， 肯定也要描述rank关系
//
//所以本质上来说， 判断x,y之间的关系， 实际上是以x,y的共同祖先fa来描述的， 通过fa这个中继， 以及x，y 与 fa的关系来推导出x,y的关系

//本题中有几个需要推导rank的地方：

//第一是op == 2的时候，也就是x吃y， 如果当前x,y之间的fa一样，也就是x,y的关系已经确定的时候， 需要推导当前x,y是什么关系才与x吃y矛盾：
//显然x,y为同种生物的时候，矛盾， 此时rank[x] = rank[y]
//或者y吃x， 这种时候可以分类出三种情况:(1)x与fa同类， y吃fa  (2)y与fa同类， fa吃x  (3)x吃fa fa吃y, 则y吃x， 可以用向量式表达
//
//第二 合并的时候(union_ function), 将fy的集合fa设置为fx, 那么要更新fy的rank， 将其设置为fy与fy的逻辑关系。 如何去联系， 当然是通过x,y这个渠道，
//以及x与fx, y与fy这个渠道， 这里有一种向量表达式的手段， 理清关系发现本质上， 吃与被吃可以用一个线性的关系表示， 这样比较容易写出表达式（很神奇）
//
//第三 合并的时候只是更新了fy的rank值， 也就是只更新了fy这一点与fa的关系， 那么fy的孩子们与新的fa之间的关系不需要更新吗？ 当然要， 不过这个过程可以留在find这个过程，
//这是一个很巧妙的设计， 在find中， 不仅更新fa, 同时也将rank保持同步更新， 而且显然可以用线性表达式来表示这个关系
//
//本题值得思考的地方在于， 如何用常见的算法， 加上特殊的状态转移， 而获取更多的信息量， 也能传递更多的信息量， 从而达到状态巧妙的转化

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 50010;
int fa[N], rank[N];

int find(int x){
    int curFather = fa[x];
    if(fa[x] != x){
        fa[x] = find(fa[x]);
    }
    rank[x] = (rank[curFather] + rank[x])%3;
    return fa[x];
}

void union_(int x, int y, int fx, int fy, int d){
    fa[fy] = fx;
    rank[fy] = (rank[x] - rank[y] + 2 + d)%3;
}

int main(){
    int n, k;
   // while(~scanf("%d%d", &n, &k)){
        int op, x, y;
        int ans = 0;
        for(int i = 0; i <= n; ++i){
            fa[i] = i;
            rank[i] = 0;
        }

        for(int i = 0; i < k; ++i){
            scanf("%d%d%d", &op, &x, &y);
            if((op == 2 && x == y) || (x > n || y > n)){
                ++ans;
                continue;
            }
            int fx = find(x), fy = find(y);
            if(fx == fy){
                if(op == 1){
                    if(rank[x] != rank[y]){
                        ++ans;
                    }
                }
                else{
                    if(rank[x] != (rank[y] + 2)%3){
                        ++ans;
                    }
                }
            }
            else{
                union_(x, y, fx, fy, op);
            }
        }
        printf("%d\n", ans);
    //}
    return 0;
}
