#include<iostream>
#include<assert.h>
#include<vector>
#include<bitset>

//#include "debughelp.hpp"

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple

int n;
vector<int> arr;
vector<bool> exist;
vector<int> parti;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	arr = vector<int>(n);
	for(int i=0;i<n;i++) cin >> arr[i];

	int maxI = 23;
	int maxS = 1<<maxI;
	int allU = maxS-1;
	exist = vector<bool>(maxS,0);
	parti = vector<int>(maxS,0);

	for(int i=0;i<n;i++) {
		exist[arr[i]]=1;
		parti[arr[i]]=arr[i];
	}

	for(int i=0;i<maxI;i++){
		for(int s=0;s<maxS;s++)
			if(s & (1<<i)){
				exist[s] = exist[s] | exist[s^(1<<i)];
				parti[s] = max(parti[s], parti[s^(1<<i)]);
			}
	}

	for(int i=0;i<n;i++){
		int cur = arr[i];
		int contra = allU ^ cur;
		if(exist[contra]){
			assert((parti[contra] & cur) == 0);
			cout<<parti[contra]<<" ";
		}else{
			cout<<-1<<" ";
		}
	}
	cout<<endl;

}