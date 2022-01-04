#include<iostream>
#include<assert.h>
#include<vector>
#include<algorithm>
#include<stack>

//#include "debughelp.hpp"

using namespace std;
typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

struct info{
    int leftHP, rightHP;
    llong leftW, midW, rightW;
    info(){
        leftHP = -1; rightHP = -1;
        leftW = 0; midW = 0; rightW = 0;
    }
};

info tree[1048580];
//vector<info> tree;
llong H[524290];
//vector<llong> H;
llong pre[524290];
//vector<llong> pre;
int leftP[524290], rightP[524290];

struct segtree
{
	static int pow_up(int num){
		for(int i=0;i<65;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
    // vector<int> leftP;
    // vector<int> rightP;
	int n;
	segtree(vector<llong>& heights,int size){
		n = pow_up(size);
        fill(H, H+n, 0);
        //H = vector<llong>(n, 0);
        copy(heights.begin(), heights.end(), H);
        fill(leftP, leftP+n, -1);
        fill(rightP, rightP+n, -1);
        // leftP = vector<int>(n, -1);
        // rightP = vector<int>(n, -1);
        stack<int> pq;
        for(int i=0;i<n;i++){
            while(!pq.empty() && H[pq.top()] < H[i]) pq.pop();
            if(pq.empty()) {pq.push(i); leftP[i]=-1; continue;}
            leftP[i] = pq.top();
            pq.push(i);
        }
        pq = stack<int>();
        for(int i=n-1;i>=0;i--){
            while(!pq.empty() && H[pq.top()] < H[i]) pq.pop();
            if(pq.empty()) {pq.push(i); rightP[i]=-1; continue;}
            rightP[i] = pq.top();
            pq.push(i);
        }
        fill(pre, pre+n, 0);
        //pre = vector<llong>(n, 0);
        pre[0] = H[0];
        for(int i=1;i<n;i++) pre[i] = pre[i-1]+H[i];
        //tree = vector<info>(2*n);
        for(int i=0;i<2*n;i++) tree[i] = info();
        for(int i=n;i<2*n;i++) {
            tree[i].leftHP=i-n;
            tree[i].rightHP=i-n;
        }
		build();
	}
    info merge(info& left, info& right){
        info total;
        if(left.leftHP == -1) {
            total = right;
            return total;
        }
        if(right.leftHP == -1){
            total = left;
            return total;
        }
        if(H[left.leftHP] > H[right.leftHP]){
            total = left;
            int le = leftP[right.leftHP];
            total.rightW = (right.leftHP - le - 1) * H[right.leftHP] - (pre[right.leftHP-1] - pre[le]) + right.midW + right.rightW + get_range(left.rightHP, le);
            // consider base case. Infinite loop?
        }else if(H[left.leftHP] < H[right.leftHP]){
            total = right;
            int re = rightP[left.rightHP];
            total.leftW = (re - left.rightHP - 1) * H[left.rightHP] - (pre[re-1] - pre[left.rightHP]) + left.midW + left.leftW + get_range(re, right.leftHP);
        }else{
            total.leftHP = left.leftHP;
            total.rightHP = right.rightHP; // mind the case mid intersect
            total.leftW = left.leftW;
            total.rightW = right.rightW;
            total.midW = (right.leftHP - left.rightHP - 1) * H[right.leftHP] - (pre[right.leftHP-1] - pre[left.rightHP]) + left.midW + right.midW;
            // this should be the same result as just putting water throughout region
        }
        return total;
    }
	void build(){
		for(int i = n-1; i>=1; i--) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
	}
    llong get_range(int left, int right){
        if(right-left<2) return 0; 
		left+=n, right+=n;
		info ls, rs;
		for(;left<=right;left>>=1,right>>=1){
			if(left&1) 
				ls=merge(ls,tree[left++]);
			if(!(right&1))
				rs=merge(tree[right--],rs);
			if(left==right) break;
		}
        info final = merge(ls, rs);
		return final.leftW + final.midW + final.rightW;
	}
};

int n, q;
vector<llong> heights;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cin >> n >> q;
    heights = vector<llong>(n);
    for(int i=0;i<n;i++) cin >> heights[i];
    segtree tree(heights, n);
    for(int i=0;i<q;i++){
        int s, e; cin >> s >> e;
        s--; e--;
        print(tree.get_range(s,e));
    }
}