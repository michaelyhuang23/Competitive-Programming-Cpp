#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int  ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint t; cin>>t;
    while(t--){
    	string str; cin>>str;
    	unordered_map<char,iint> uniqueChar;
    	For(i,str.length()){
    		if(uniqueChar.find(str[i]) == uniqueChar.end()) uniqueChar[str[i]]=0;
    		uniqueChar[str[i]]++;
    	}
    	iint numOp = uniqueChar.size();
    	iint len = str.length();
    	unordered_map<char, iint> nOccur;
    	bool suc = true;
    	string s;
    	stack<char> seq;
    	for(iint op=numOp; op>=1; op--){
    		unordered_map<char, iint> counts;
    		unordered_set<char> newChar;
    		iint i;
    		for(i=len-1; i>=0; i--){
    			if(counts.find(str[i]) == counts.end()) counts[str[i]]=0;
    			counts[str[i]]++;
    			//cout<<str[i]<<" "<<counts[str[i]]<<endl;
    			if(nOccur.find(str[i]) == nOccur.end()){
    				newChar.insert(str[i]);
    				if(newChar.size()>1){
    					newChar.erase(str[i]); break;
    				}
    				iint res = uniqueChar[str[i]]/op;
    				//cout<<str[i]<<" "<<op<<" "<<res<<endl;
    				if(res*op != uniqueChar[str[i]]){
    					suc=false; break;
    				}
    				if (counts[str[i]]>res){
    					counts[str[i]]--;
    					break;
    				}
    			}else if(counts[str[i]] > nOccur[str[i]]){
    				counts[str[i]]--;
    				break;
    			}
    		}
    		if(op==1 && i!=-1){
    			suc=false;
    		}
    		if(!suc) break;
    		for(auto cc : nOccur){
    			if(counts.find(cc.first) == counts.end()){
    				//cout<<cc.first<<" not found"<<endl;
    				suc=false; break;
    			}
    			if(counts[cc.first]<cc.second){
    				//cout<<cc.first<<" : "<<counts[cc.first]<<" "<<cc.second<<endl;
    				suc=false; break;
    			}
    		}
    		if(!suc) break;
    		//cout<<"pass1"<<endl;
    		if(newChar.size()!=1){
    			suc=false; break;
    		}
    		for(char chr : newChar){
    			//cout<<"add "<<chr<<" "<<uniqueChar[chr]/op<<" "<<op<<endl;
    			nOccur[chr] = uniqueChar[chr]/op;
    			seq.push(chr);
    		}
    		if(suc && op==1){
    			s = str.substr(0, len);
    		}
    		len = i+1;
    		//cout<<len<<endl;
    	}
    	if(!suc){
    		cout<<-1<<endl; continue;
    	}
    	// we need to perform final forward check (since sequence matters)
    	stack<char> cseq = seq;
    	vector<char>* newS = new vector<char>();
    	for(char c : s) newS->pb(c);
    	vector<char> t(*newS);
    	while(!cseq.empty()){
    		vector<char>* nnS = new vector<char>();
    		char forbid = cseq.top();
    		For(i, newS->size()){
    			if((*newS)[i] == forbid) continue;
    			nnS->pb((*newS)[i]);
    		}
    		cseq.pop();
    		delete newS;
    		newS = nnS;
    		For(i, newS->size()) t.pb((*newS)[i]);
    	}
    	assert(t.size() == str.size());
    	For(i, t.size()) if(t[i] != str[i]){ suc=false; break;}
    	if(!suc){
    		cout<<-1<<endl; continue;
    	}
    	cout<<s<<" ";
    	while(!seq.empty()){
    		cout<<seq.top(); seq.pop();
    	}
    	cout<<endl;
    }
}

/*
the last letter == last removed

abacabaaacaac
abacabaaacaa
abacaba

first by getting unique letters, we know how mnay operations there are
in each operation, the same number of each letter must be added 
(if it's not removed) 

v, e, r, y, w, h
everywherevrywhrvryhrvrhrvhv
v
everywherevrywhrvryhrvrhrvh
vh
everywherevrywhrvryhrvrhr
vrhr
everywherevrywhrvryhr
vryhr
everywherevrywhr
vrywhr
everywhere
*/










