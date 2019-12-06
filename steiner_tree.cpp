#include<iostream>
#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;


// **** Function to find the representative of the element ****
int find(ll Parent[], ll a)
{
	return a == Parent[a] ? a : Parent[a] = find(Parent , Parent[a]);

}

// **** Unites the set that includes i and the set that includes j **** 
ll union1(ll Parent[] , ll i, ll j, ll * ptr) 
{
    // Find the representatives (or the root nodes) for the set that includes i
    ll irep = find(Parent , i);

    // And do the same for the set that includes j    
    ll jrep = find(Parent , j);
    //Both are from Same set and trying to create a cycle reject's it  
    if(irep == jrep)
    	return 0;

    // Make the parent of i’s representative be j’s  representative effectively 
    // moving all of i’s set into j’s set)
    Parent[irep] = jrep;

    /* **** Each time union operation occured number of connected components
		will decrement by 1
	*/

    *ptr = *ptr - 1;

    return 1;
}


// **** Function to check whether the edges form a Steiner Tree with atmost K edges or not ****
ll check_Steiner_Tree(vector<ll>V,vector<ll>W, vector <pair<ll , ll>> arr)
{
	ll flag = 0;
	ll v = V.size();
	ll w = W.size();
	ll Parent[v + w + 1];


	/*Initial there must be v + w connected components present
	 as each individual node will be it's own parent
	 */

	ll num_conn_comp = v + w; 
	for(ll k = 0;k < v + w + 1;k++)
	{
		// **** Initializing Parent of the node with it's own node ****
		Parent[k] = k;
	}

	for(ll i = 0;i < arr.size();i++)
	{
		ll a = arr[i].first;
		ll b = arr[i].second;

		ll ret = union1(Parent , a , b , &num_conn_comp);
		if(ret == 0)
		{
			return 0;
		}
	}
	/* **** If At the end if number of connected component equals to 1 and in includes all vertices of v 
		in atmost K_Edges then we will accept

		Else Check for other Case 
	*/

	// **** Check whether tree covers all the verticews of V ****
	flag = 1;
	ll parent = find(Parent , V[0]);
	for(ll i = 0;i < V.size();i++)
	{
		if(find(Parent , Parent[V[i]]) != parent)
		{
			flag = 0;
			break;
		}
	}
	if(flag == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


//  **** Function to convert a decimal number to binary_bits ****
void conv_binary(ll binary_bits[] , ll i , ll Edges)
{
	ll size1 = i;
	ll size2 = Edges;

	while(size1 != 0)
	{
		binary_bits[size2 - 1] = (size1 % 2);
		size1 = size1/2;
		size2--;
	}
}

// **** A utility function to add an edge in an undirected graph **** 
void addEdge(vector< ll > graph[], ll u, ll v) 
{ 
  	graph[u].push_back(v); 
    graph[v].push_back(u);   
} 

// **** Function to print the Bipartite Graph ****
void print_graph( vector< ll > graph[], ll n)
{

	cout << "Adjacency List for the Graph\n";
	for(ll i = 1;i < n;i++)
	{
		cout << i << "-> ";
		for(ll j = 0;j < graph[i].size();j++)
		{
			cout << graph[i][j] << " ";
		}
		cout << "\n";
	}


}

// **** Function to print all the edges in the graph **** 
void print_vect(vector <pair<ll , ll>> vect)
{
	cout << "All the Edges\n";
	for(ll j = 0;j < vect.size();j++)
	{
		cout << vect[j].first << " " << vect[j].second << "\n";
	}
}
int main()
{
	ll flag = 0;

	/*
	-->> Following inputs must be given while forming the Bipartite Graph :- 
	-->> The input are as follows :-
	1.) Number of Vertices in both parts of the graph and the values of vertices.
	2.) Number of Edges in the Graph
	3.) All the edges that will form bipartite graph
	4.) Input for the edges will be given in the form (a , b) where a represent vertex in V and b represent vertex in W
	5.) As there won't be any edges between the vertices of particlar graph. 
	6.) The Name of the vertices will start from 1 and will go upto (nV + nW)(count of Total Vertices in each part of the graph)
	*/


	/*
	-->> We have also given the edges in which we have to cover the tree
	-->> It will be stores in K_Edges
	-->> We have to find whether there exist a Steiner Tree that includes all the vertices of V and in not more than K edges 
		 if it exist we will print "YES" otherwise "NO" 
	*/
	ll nV; //Number of vertices in V
	ll nW; //Number of vertices in W

	ll Edges; //Number of edges in the graph
	ll K_Edges; // Atmost K_Edges


	cout << "Number of Vertices in V :-\n";
	cin >> nV;
	cout << "Number of Vertices in W :-\n";
	cin >> nW; //Input for Number of Vertices
	cout << "Number of Edges in the Graph :-\n";
	cin >> Edges;   //Input for Number of Edges in the Graph 
	cout << "Number of Atmost Edges to cover the tree :-\n";
	cin >> K_Edges;

	vector < ll > V; //Input vector for vertices in V
	vector < ll > W; //Input vector for vertices in W

//  **** Taking Input in the vector V as vertices ****
	cout << "Give Input as Vertices in V :-\n";
	for(ll i = 0;i < nV;i++)
	{
		ll a;
		cin >> a;
		V.push_back(a);
	}

// **** Taking Input in the vector W as vertices ****
	cout << "Give Input as Vertices in W :-\n";
	for(ll j = 0;j < nW;j++)
	{
		ll b;
		cin >> b;
		W.push_back(b);
	}


// **** Declaring a vector to keep track of edges *** 
	vector <pair<ll , ll>> vect;


// **** Declaration of graph ***
	vector < ll > graph[nV + nW + 1];


// **** Formation of Bipartite Graph ****
	cout << "Give all the Edges u and v as input one by one :-\n";
	for(ll k = 0;k < Edges;k++)
	{
		ll u, v;
		cin >> u >> v;

		// Calling function to add an edge in the graph  
		addEdge(graph , u , v);

		// Saving the edge in the vector 
		vect.push_back(make_pair(u , v));
	}
// ****

	// print_vect(vect);
	print_graph(graph , nV + nW + 1);

	ll n = pow(2 , Edges);
	for(ll i = 1;i < n;i++)
	{
		ll binary_bits[Edges] = {0};
		conv_binary(binary_bits , i , Edges);

		// **** For all binary_bits equal to 1 Include the corresponding edges from the vector vect into the vector arr****
		vector <pair<ll , ll>> arr; 

		for(ll k = 0;k < Edges;k++)
		{
			if(binary_bits[k] == 1)
			{
				ll u = vect[k].first;
				ll v = vect[k].second;

				arr.push_back(make_pair(u , v));
			}

		}
		//  **** Check Steiner Tree in atmost K edges **** 
		if(arr.size() >= V.size() && arr.size() <= K_Edges)
		{
			ll ret = check_Steiner_Tree(V , W , arr); 


			if(ret == 1)
			{
				// **** If we found a tree with atmost k edges which include all the vertices of V ****
				// **** Initialize the flag ****
				flag = 1;
				cout << "YES\n";

				for(ll k = 0;k < arr.size();k++)
				{
					cout << arr[k].first << " " << arr[k].second << "\n";
				}
				break;
			}  
		}
	}

// **** Not Possible to found a tree with atmost k edges and includes all vertices of V
	if(flag == 0)
		cout << "NO\n";

}
