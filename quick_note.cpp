
Xenia and Tree
Gameplan:
1. Create centroid tree:
	1. build function to compute the size of subtrees: get_size()
	2. build function that finds centroid in a tree (use mask to avoid
		some vertices): get_centroid()
	3. build function that constructs the centroid tree via this procedure:
		build_tree(int i, int p):
			1. get_size(i); // roots subtree at i and compute size based on that
			2. c = get_centroid(i); // get centroid from subtree i
				when finding centroid c, track dist(c,i). dist(c,p)=dist(c,i)+1
				dist(c,p) should be recorded in dist2par[c].
			3. parent[c] = p;
2. Compute distance of a node to every single ancestor
	1. Compute distance to father node in centroid tree
		1. When finding centroid, track its distance to original start point
			see above
	2. Iteration upward the centroid tree: 
		dist2ancestor[i][j] = dist2ancestor[i][j-1]+dist2ancestor[j-1][j]
3. Compute the queries:
	initialize the reddist[i] = inf;
	update the first node in;
	if(update):
		1. update every parent j of i to min(dist2ancestor[i][height]). 
	if(query):
		2. query every parent j of reddist
	
