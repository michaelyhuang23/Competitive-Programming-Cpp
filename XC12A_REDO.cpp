#include<bits/stdc++.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define inf 1000000007LL*8LL
#define print(x) cout<<x<<endl

int n;
int d;
vector<pair<int,int>> ptrs;
vector<llong> p2id;
vector<llong> xs;
llong minTC = inf;
int mid;

llong dist(llong xl, llong xr, llong yu, llong yd){
	return xr - xl + yu + yd + min(abs(xl), abs(xr)) + min(abs(yu), abs(yd));
}

llong get_min(vector<vector<llong>>& rmq, llong l, llong r){
	if(r<l) return inf;
	int j;
	for(j=19;j>=0;j--) if((1<<j) <= r-l+1) break;
	return min(rmq[j][l], rmq[j][r-(1<<j)+1]);
}

void solve_dir(){
	sort(ptrs.begin(), ptrs.end());
	//deb(ptrs)
	xs = vector<llong>(n);
	p2id = vector<llong>(n);
	for(int i=0;i<n;i++) xs[i]=ptrs[i].first;
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	d = xs.size();
	//deb(xs)
	int k=0;
	for(int i=0;i<n;i++){
		while(ptrs[i].first>xs[k]) k++;
		assert(xs[k] == ptrs[i].first);
		p2id[i]=k;
	}

	for(int i=0;i<d;i++) if(xs[i]==0) mid=i;
	//deb(mid)
	vector<llong> yminf(d,inf), ymaxf(d,inf), yminb(d,inf), ymaxb(d,inf);
	set<llong> ty; ty.insert(0);
	int pi = -1;
	for(int i=0;i<n;i++){
		if(p2id[i] > pi){
			yminf[p2id[i]] = max(0LL,-*ty.begin());
			ymaxf[p2id[i]] = max(0LL,*ty.rbegin());
			pi = p2id[i];
		}
		ty.insert(ptrs[i].second);
	}
	ty = set<llong>(); ty.insert(0);
	pi = d+1;
	for(int i=n-1;i>=0;i--){
		if(p2id[i] < pi){
			yminb[p2id[i]] = max(0LL,-*ty.begin());
			ymaxb[p2id[i]] = max(0LL,*ty.rbegin());
			pi = p2id[i];
		}
		ty.insert(ptrs[i].second);
	}
	// deb(yminf)
	// deb(ymaxf)
	// deb(yminb)
	// deb(ymaxb)
	// focus on ll[0][0], rr[1][1]
	// i'm not sure if this covers the case where it's contained in a quadrant
	int l=0, r=0;
	llong minC = inf;
	for(int i=d-1;i>=mid;i--){
		llong yminr = yminb[i];
		llong ymaxr = ymaxb[i];
		while(r<=mid && yminf[r]<=yminr && ymaxf[r]<=ymaxr){
			minC = min(minC,max(0LL,-xs[r]));
			r++;
		}
		r--;
		minTC = min(minTC, ymaxr*2 + yminr + xs[i]*2 + minC);
	} // this will deal with the case it's in the 1st and 4th quadrant

	// focus on ll[1][1], rr[0][0]
	l=mid; r=mid;
	minC = inf;
	for(int i=mid;i<d;i++){
		llong yminr = yminb[i];
		llong ymaxr = ymaxb[i];
		while(l>=0 && yminf[l]>=yminr && ymaxf[l]>=ymaxr){
			minC = min(minC,max(0LL,-xs[l])+2*ymaxf[l]+yminf[l]);
			l--;
		}
		l++;
		minTC = min(minTC, xs[i]*2 + minC);
	} // this will deal with the case it's in the 1st and 4th quadrant

	// focus on ll[1][0], rr[0][1]
	// ymax[l]>=ymax[r], ymin[l]<=ymin[r]
	vector<vector<llong>> rmq(20,vector<llong>(mid+1));
	for(int i=0;i<=mid;i++) rmq[0][i]=max(0LL,-xs[i])+2*ymaxf[i];
	for(int j=1;j<20;j++)for(int i=0;i<=mid;i++)
		rmq[j][i] = min(rmq[j-1][i],rmq[j-1][min(mid,i+(1<<(j-1)))]);

	l=0; r=0;
	minC = inf;
	for(int i=d-1;i>=mid;i--){
		llong yminr = yminb[i];
		llong ymaxr = ymaxb[i];
		while(r<=mid && yminf[r]<=yminr){
			r++;
		}
		r--;
		while(l<=mid && ymaxf[l]<ymaxr){
			l++;
		}
		minC = get_min(rmq, l, r);
		minTC = min(minTC, yminr + xs[i]*2 + minC);
	}

	// focus on ll[0][1], rr[1][0]
	// ymax[l]<=ymax[r], ymin[l]>=ymin[r]
	rmq = vector<vector<llong>>(20, vector<llong>(mid+1));
	for(int i=0;i<=mid;i++) rmq[0][i]=max(0LL,-xs[i])+yminf[i];
	for(int j=1;j<20;j++)for(int i=0;i<=mid;i++)
		rmq[j][i] = min(rmq[j-1][i],rmq[j-1][min(mid,i+(1<<(j-1)))]);

	l=0; r=0;
	minC = inf;
	for(int i=d-1;i>=mid;i--){
		llong yminr = yminb[i];
		llong ymaxr = ymaxb[i];
		while(r<=mid && ymaxf[r]<=ymaxr){
			r++;
		}
		r--;
		while(l<=mid && yminf[l]<yminr){
			l++;
		}
		minC = get_min(rmq, l,r);
		minTC = min(minTC, 2*ymaxr + xs[i]*2 + minC);
	}
	//deb(minTC)
}

void solve(){
	minTC = inf;
	cin >> n;
	ptrs = vector<pair<int,int>>(n);
	bool has0 = false;
	for(int i=0;i<n;i++){
		int a, b; cin>>a>>b;
		ptrs[i] = mp(a,b);
		if(a == 0 && b==0) has0=true;
	}
	if(!has0)
		ptrs.pb(mp(0,0));
	n = ptrs.size();

	{
		solve_dir();
	}
	{
		for(int i=0;i<n;i++) ptrs[i].second *= -1;
		solve_dir();
	}
	{
		for(int i=0;i<n;i++) ptrs[i].first *= -1;
		solve_dir();
	}
	{
		for(int i=0;i<n;i++) ptrs[i].second *= -1;
		solve_dir();
	}
	print(minTC);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--) solve();
}