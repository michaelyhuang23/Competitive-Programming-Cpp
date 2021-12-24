#include<iostream>
#include<vector>
#include<assert.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple

struct Point{
	int val;
	bool isUpdate;
	int fr,to;
	Point(int val_){ val = val_; isUpdate = false; }
	Point(int fr_, int to_){ fr = fr_; to = to_; isUpdate = true; }
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int q; 
	cin >> q;
	vector<Point> ptrs;
	for(int i=0;i<q;i++){
		int type; cin >> type;
		if(type == 1){
			int val; cin >> val;
			ptrs.pb(Point(val));
		}else{
			int fr, to; cin >> fr >> to;
			ptrs.pb(Point(fr, to));
		}
	}
	int S = 5*100000+5;

	vector<int> mapp(S);
	for(int i=0;i<S;i++) mapp[i]=i;

	for(int i=q-1;i>=0;i--){
		if(ptrs[i].isUpdate){ // guarantee one step map
			//deb("change map")
			//deb(mt(ptrs[i].fr, ptrs[i].to, mapp[ptrs[i].to]))
			mapp[ptrs[i].fr] = mapp[ptrs[i].to];
		}else{
			//deb("update")
			//deb(mp(ptrs[i].val, mapp[ptrs[i].val]))
			ptrs[i].val = mapp[ptrs[i].val];
		}
	}


	vector<int> newA;
	for(int i=0;i<q;i++){
		if(!ptrs[i].isUpdate) newA.pb(ptrs[i].val);
	}
	//deb(newA)
	for(int i=0;i<newA.size();i++)
		cout<<newA[i]<<" ";
	cout<<endl;
}
