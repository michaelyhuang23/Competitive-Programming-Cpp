int nodes[MAXSIZE];
int lefts[MAXSIZE], rights[MAXSIZE];
int DIR[4][2] = {{1,1},{-1,1},{1,-1},{-1,-1}};
int MOV[4][2] = {{2,0},{-2,0},{0,2},{0,-2}};
int counter = 0;

int updateIdx;
int updateVal;
struct DynamicSegtree{
	static void init(){ // must call before use
		fill(nodes, nodes+MAXSIZE, 0);
		fill(lefts, lefts+MAXSIZE, -1);
		fill(rights, rights+MAXSIZE, -1);
		counter = 0;
	}
	DynamicSegtree(){}
	void pull_up(int idx){
		nodes[idx] = int();
		if(lefts[idx]!=-1) nodes[idx] += nodes[lefts[idx]];
		if(rights[idx]!=-1) nodes[idx] += nodes[rights[idx]];
	}
	int query(int idx, int ll, int rr, int ts=0, int te=RANGE){
		if(ll>rr) return int();
		if(ll == ts && rr == te) return nodes[idx];
		int tm = (ts+te)/2;
		int leftNode, rightNode;
		if(lefts[idx]!=-1 && ll <= tm)
			leftNode = query(lefts[idx], ll, min(rr,tm), ts, tm);
		if(rights[idx]!=-1 && rr > tm)
			rightNode = query(rights[idx], max(ll,tm+1),rr,tm+1,te);
		return leftNode + rightNode;
	}
	void update(int idx, int ts=0, int te=RANGE){
		if(updateIdx==ts && updateIdx==te){
			// deb(mp(updateIdx,idx))
			nodes[idx]+=updateVal;
			return;
		}
		int tm = (ts+te)/2;
		if(updateIdx <= tm){
			if(lefts[idx]==-1) 
				lefts[idx] = ++counter;
			update(lefts[idx], ts, tm);
		}else{
			if(rights[idx]==-1) 
				rights[idx] = ++counter;
			update(rights[idx], tm+1, te);
		}
		pull_up(idx);
	}
};

struct BIT2D{
	vector<int> bits;
	DynamicSegtree tree;
	int n;
	BIT2D(int n_){
		n = n_+2; // safety
		bits = vector<int>(n);
		for(int i=0;i<n;i++) bits[i] = ++counter;
	}

	inline int low_bit(int num){
	    return num & (-num);
	}
	int query(int xp, int yp){ // idx starts at 1
		xp++; // shift index
	    int sum = 0;
	    for(int x = xp; x>0; x -= low_bit(x))
	    	sum += tree.query(bits[x], 0, yp);
	    return sum;
	}
	void update(int xp, int yp, int val){
		xp++; // shift index
	    for(int x = xp; x<=bits.size()-1; x+= low_bit(x)){
	    	updateIdx = yp;
	    	updateVal = val;
	    	tree.update(bits[x]); 
	    }
	}
};




























struct Node{
	int val, sum, len;
	Node():val(0),sum(0),len(0){}
	Node(int len_):val(0),sum(0),len(len_){}
	static Node merge(Node& ll, Node& rr){
		Node mm;
		mm.sum = ll.sum + rr.sum;
		mm.len = ll.len + rr.len;
		mm.val = ll.val + rr.val + rr.len*ll.sum;
		return mm;
	}
	void pull_up(Node& ll, Node& rr){
		(*this) = merge(ll,rr);
	}
	void update(int val_){
		val+=0*val_;
		sum+=val;
	}
	int ans(){return val;}
};

Node nodes[MAXSIZE];
int lefts[MAXSIZE], rights[MAXSIZE];
int counter = 0;
struct DynamicSegtree{
    DynamicSegtree(){}
    void pull_up(int idx){
        Node leftNode, rightNode;
        if(lefts[idx]!=-1) leftNode = nodes[lefts[idx]];
        if(rights[idx]!=-1) rightNode = nodes[rights[idx]];
        nodes[idx].pull_up(leftNode, rightNode);
    }
    Node query(int idx, int ll, int rr, int ts=0, int te=RANGE){
        if(ll == ts && rr == te) return nodes[idx];
        int tm = (ts+te)/2;
        Node leftNode, rightNode;
        if(lefts[idx]!=-1 && ll <= tm){
            leftNode = query(lefts[idx], ll, min(rr,tm), ts, tm);
        }
        if(rights[idx]!=-1 && rr > tm){
            rightNode = query(rights[idx], max(ll,tm+1),rr,tm+1,te);
        }
        return Node::merge(leftNode, rightNode);
    }
    void update(int idx, int loc, int val, int ts=0, int te=RANGE){
        if(loc==ts && loc==te){ nodes[idx].update(val); return; }
        int tm = (ts+te)/2;
        if(loc <= tm){
            if(lefts[idx]==-1){
            	lefts[idx] = ++counter; // instantiate
            	nodes[counter] = Node(tm-ts+1);
            }
            update(lefts[idx], loc, val, ts, tm);
        }else{
            if(rights[idx]==-1){
            	rights[idx] = ++counter; // instantiate
            	nodes[counter] = Node(te-tm);
            }
            update(rights[idx], loc, tm+1, te);
        }
        pull_up(idx);
    }
};


struct BIT2D{
	vector<int> bits;
	DynamicSegtree tree;
	int n;
	BIT2D(int n_){
		n = n_+2; // safety
		bits = vector<int>(n);
		for(int i=0;i<n;i++) bits[i] = ++counter;
	}

	inline int low_bit(int num){
	    return num & (-num);
	}
	int query(int xp, int yp){ // idx starts at 1
		xp++; // shift index
	    int sum = 0;
	    for(int x = xp; x>0; x -= low_bit(x))
	    	sum += tree.query(bits[x], 0, yp).ans();
	    return sum;
	}
	void update(int xp, int yp, int val){
		xp++; // shift index
	    for(int x = xp; x<=bits.size()-1; x+= low_bit(x)){
	    	tree.update(bits[x],yp,val); 
	    }
	}
};