#include<iostream>
#include<vector>
#include<assert.h>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	llong tt; cin >> tt;
	while(tt--){
		llong n, k, x;
		cin >> n >> k >> x;
		string s; cin >> s;
		vector<llong> bc;
		llong c = 0;
		for(llong i=0;i<s.size();i++){
			if(s[i] == 'a'){
				if(c==0) continue;
				bc.pb(c*k);
				c=0;
			}else c++;
		}
		if(c!=0) bc.pb(c*k);

		//deb(bc)

		vector<char> temp;
		for(int i=0;i<s.size();i++){
			if(s[i] == 'a') temp.pb('a');
			if(s[i] == '*') {
				while(i<s.size() && s[i] == '*') i++;
				i--;
				temp.pb('*');
			}
		}

		//deb(temp)

		vector<llong> pfix(bc.size()+5,0);
		pfix[bc.size()] = 1;
		int idx = 0;
		for(int i=bc.size()-1;i>=0;i--){
			llong div = (x + pfix[i+1] - 1) / pfix[i+1];
			if(div <=  bc[i]+1){
				// 5/2=3; 4/2=2 
				idx = i;
				break;
			}
			pfix[i] = pfix[i+1]*(bc[i]+1);
		}

		//deb(pfix)

		vector<int> counts(bc.size()+5,0); // counts[i]-1 is answer
		for(int i=idx;i<bc.size();i++){
			//deb(mp(x,pfix[i+1]))
			counts[i] = x/pfix[i+1]; // if not perfect
			if(x%pfix[i+1] != 0){
				counts[i]++;
				x = x%pfix[i+1];
			}else{
				x = pfix[i+1];
			}
		}
		for(int i=0;i<bc.size();i++) counts[i]--;

		//deb(counts)

		int j = 0;
		vector<char> output;
		for(int i=0;i<temp.size();i++){
			if(temp[i] == 'a') output.pb('a');
			if(temp[i] == '*'){
				for(int k=0;k<counts[j];k++) output.pb('b');
				j++;
			}
		}

		string oo(output.begin(), output.end());
		cout<<oo<<endl;
	}
}






