#include<bits/stdc++.h>

using namespace std;
#define inf 1000000000

void solve(int tt){
	int ma=inf,mb=inf,mc=inf,md=inf;
	for(int i=0;i<3;i++){
		int a,b,c,d; cin >> a >> b >> c >> d;
		ma = min(ma,a);
		mb = min(mb,b);
		mc = min(mc,c);
		md = min(md,d);
	}

	if(ma+mb+mc+md < 1000000){
		cout<<"Case #"<<tt<<": IMPOSSIBLE"<<endl;
		return;
	}

	cout<<"Case #"<<tt<<":";

	int cur = 1000000;
	int arr[4] = {ma,mb,mc,md};
	for(int i=0;i<4;i++){
		int k = min(arr[i], cur);
		cout<<" "<<k;
		cur -= k;
	}

	cout<<endl;

}




int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	for(int t=1;t<=tt;t++)
		solve(t);
}