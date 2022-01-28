#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000000LL

struct NodeP{
	llong sum;
	llong p, a;
	NodeP(){sum = -inf; p = -inf;}
	NodeP(llong val){
		sum = val;
		p = val;
		a = p;
	}
	NodeP merge(NodeP r){
		NodeP m;
		m.sum = sum+r.sum;
		m.p = max(p, sum+r.p);
		m.a = m.p;
		return m;
	}
};

int main(){
	NodeP p1, p2(0);
	NodeP p3 = p1.merge(p2);
	print(p3.a);

}