#include<bits/stdc++.h>
using namespace std;
const int maxn = 100000+ 10;
//update_add:把A[L]~A[R]的值全部加v_add
//update_set:把A[l]~A[R]的值设为v_set
//query:计算子序列的元素和，最小值，最大值
int sumv[2*maxn],minv[2*maxn],maxv[2*maxn];
int addv[2*maxn], setv[2*maxn];
int y11, y2, v_add, v_set;

void maintain(int o, int L, int R) {
    int lc = 2*o, rc = 2*o + 1;
    sumv[o] = minv[o] = maxv[o] = 0;
    if(setv[o] >= 0) {
        sumv[o] = setv[o] * (R-L+1);
        minv[o] = maxv[o] = setv[o];
    }
    else if(R > L) {
        sumv[o] = sumv[lc] + sumv[rc];
        minv[o] = min(minv[lc], minv[rc]);
        maxv[o] = max(maxv[lc], maxv[rc]);
    }
    minv[o] += addv[o]; maxv[o] += addv[o]; sumv[o] += addv[o] * (R-L+1);
}
void pushdown(int o) {
    int lc = 2*o, rc = 2*o+1;
    if(setv[o] >= 0) {
        setv[lc] = setv[rc] = setv[o];
        addv[lc] = addv[rc] = 0;
        setv[o] = -1;
    }
    if(addv[o] > 0) {
        addv[lc] += addv[o];
        addv[rc] += addv[o];
        addv[o] = 0;
    }
}
void update_add(int o, int L, int R) {
    int lc = 2*o, rc = o*2+1;
    if(y11 <= L && y2 >= R) {
        addv[o] += v_add;
    }
    else {
        pushdown(o);
        int M = L + (R-L)/2;
        if(y11 <= M) update_add(lc, L, M); else maintain(lc, L, M);
        if(y2 > M) update_add(rc, M+1, R);else maintain(rc, M+1, R);
    }
    maintain(o, L, R);
}
void update_set(int o, int L, int R) {
    int lc = 2*o, rc = o*2+1;
    if(y11 <= L && y2 >= R) {
        setv[o] = v_set;
        addv[o] = 0;
    }
    else {
        pushdown(o);
        int M = L + (R-L)/2;
        if(y11 <= M) update_set(lc, L, M); else maintain(lc, L, M);
        if(y2 > M) update_set(rc, M+1, R); else maintain(rc, M+1, R);
    }
    maintain(o, L, R);
}
int _min, _max, _sum;
void query(int o, int L, int R, int add) {
    if(setv[o] >= 0) {
        _sum += (add+setv[o]+addv[o]) * (min(R, y2)-max(L, y11)+1);
        _min = min(_min, setv[o]+addv[o]+add);
        _max = max(_max, setv[o]+addv[o]+add);
    }
    else if(y11 <= L && y2 >= R) {
        _sum += sumv[o] + add * (R-L+1);
        _min = min(_min, minv[o]+add);
        _max = max(_max, maxv[o]+add);
    }
    else {
        int M = L + (R-L)/2;
        if(y11 <= M) query(o*2, L, M, add+addv[o]);
        if(y2 > M) query(o*2+1, M+1, R, add + addv[o]);
    }
}
void init() {
    memset(setv, -1, sizeof setv);
    memset(addv, 0, sizeof addv);
    memset(sumv, 0, sizeof sumv);
    memset(minv, 0, sizeof minv);
    memset(maxv, 0, sizeof maxv);
}



int main(int argc, char *argv[])
{
	int n,m;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d",&v_add);
		y11 = y2 = i;
		update_add(1,1,n);	
	}	
	scanf("%d",&m);
	while(m--)
	{
		int x,a,b,c;
		scanf("%d",&x);
		if (x == 1)
		{
			scanf("%d %d %d",&y11,&y2,&c);
			v_add = c;
			update_add(1,1,n);
		}
		else
		{
			_sum = 0;
			scanf("%d",&y11);
			y2 = y11;
			query(1,1,n,0);
			printf("%d\n",_sum);
		}
	}
	return 0;
}
