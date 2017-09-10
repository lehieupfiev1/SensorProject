#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>
const int CoordinateMaxValue = 1000;
const int MaxPointOfSetS = 50; // Max Point of S
const int MaxSetOfD = 10;// Max Set of D
const int MaxPointOfSetD = 50;// Max Point of every set D
const float MAX_DISTANCE = 10000000000;

float Distance[MaxPointOfSetS+MaxPointOfSetD*MaxSetOfD+1][MaxPointOfSetS+MaxPointOfSetD*MaxSetOfD+1];
int P[MaxPointOfSetS+MaxPointOfSetD*MaxSetOfD+1][2];
int S[MaxPointOfSetS][2];
int D[MaxSetOfD][MaxPointOfSetD][2];
int M[MaxSetOfD]; // Number Point of every set D

int K;// Number Set in D
int N;// Number points of S
int TP;// Total point 

struct Set {
	int id;
	int start;
	int end;
};
Set SetS,SetD[MaxPointOfSetD];

void readData() {
	int testcase;
	int i,j;
	int pi = 0;
	scanf("%d %d %d\n", &testcase,&N,&K);
	//Read N points of set S
	for (i=0;i<N;i++) {
		scanf("%d %d", &S[i][0],&S[i][1]);
		P[pi][0] = S[i][0];
		P[pi][1] = S[i][1];
		pi++;
	}
	scanf("\n");
	SetS.id = -1;
	SetS.start = 0;
	SetS.end = N-1;
	//Read K set D
	for (i =0;i<K;i++) {
		scanf("%d", &M[i]);
		SetD[i].id = i;
		SetD[i].start = pi;
		SetD[i].end = pi+M[i]-1;

		for (j = 0;j<M[i];j++) {
			scanf("%d %d", &D[i][j][0],&D[i][j][1]);
			P[pi][0] = D[i][j][0];
		    P[pi][1] = D[i][j][1];
		    pi++;
		}
		scanf("\n");
	}
}

// CalcularDistance between two point
float calcuDistance(int x1, int y1,int x2,int y2) {
	return (float)sqrt((float)(x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

void createMtrixDistance() {
	int i,j;
	//Total point
	TP = N;
	for (i=0;i<K;i++) {
		TP+= M[i];
	}
	// Calculate Distance
	for (i =0;i<TP;i++) {
		for (j =0;j<=i;j++) {
			if (i==j) {
				Distance[i][j] = 0;
			} else {
				Distance[i][j] = Distance[j][i] = calcuDistance(P[i][0],P[i][1],P[j][0],P[j][1]);
			}
		}
	}
}

/// Minimun distance between two Sets ( D(i) and S)
int findMinConnectFromSetDToS(Set *setD) {
	int i,j;
	int startD = setD->start;
	int endD = setD->end;

	int point;
	float distance = MAX_DISTANCE;

	for (i= 0; i<N; i++) {
		for (j= startD; j<=endD; j++) {
			if (distance > Distance[i][j]) {
				distance = Distance[i][j];
				point = j;
			}
		}
	}

	return point;
}

// Create matrix N+1 of S and representative of the setD(i)
float Matrix[MaxPointOfSetS+1][MaxPointOfSetS+1];
void createMatrix(int point) {
	int i,j;
	for (i=0;i<N;i++) {
		for (j=0;j<=i;j++) {
			Matrix[i][j] = Matrix[i][j] = Distance[i][j];
		}
	}
	for (i =0;i<N;i++) {
		Matrix[i][N] = Matrix[N][i] = Distance[i][point];
	}
	Matrix[N][N] = 0;
}

//*-----------------------Start KRUKAL Algorithm ---------------------------------*/
struct Edge {
	int u,v;
	float distance;
};
//List Edges
Edge ListEdge[MaxSetOfD][MaxPointOfSetS+2];// List Egde is egde result after using Krukal Algorithm with N+1 matrix
Edge ListResult[(MaxPointOfSetS+1)*MaxSetOfD];//ListResult is egde result of this algorithm;
Edge nEdgeList[MaxPointOfSetS*(MaxPointOfSetS+1)/2+1];

int nEdge,V;//number edge and vertices.
int parent[MaxPointOfSetS+2];


void createListEdges(Edge *edgeList) {
	int i,j;
	int k = 0;
	for (i = 0;i<=N;i++) {
		for (j = 0;j<i;j++) {
			if (i != j ) {
				edgeList[k].u = i;
				edgeList[k].v = j;
				edgeList[k].distance = Matrix[i][j];
				k++;
			}
		}
	}
}

//Sort Egde (Merge Sort Algorithm)
void Merge(Edge *B,int start,int mid,int end) {
	//Khoi tao
	int i = start;
	int j = mid+1;
	Edge *temp = new Edge[end-start+1];

	//
	int k;
	for (k=0;k<end-start+1;k++) {

		if (B[i].distance < B[j].distance) {
			temp[k].distance = B[i].distance;
			temp[k].u = B[i].u;
			temp[k].v = B[i].v;
			i++;
		} else {
			temp[k].distance = B[j].distance;
			temp[k].u = B[j].u;
			temp[k].v = B[j].v;
			j++;
		}

		if (i==mid+1) {
			while (j <= end) {
				k++;
				temp[k].distance = B[j].distance;
				temp[k].u = B[j].u;
				temp[k].v = B[j].v;
				j++;
			}
		}

		if (j == end+1) {
			while(i<= mid) {
				k++;
				temp[k].distance = B[i].distance;
				temp[k].v = B[i].v;
				temp[k].u = B[i].u;
				i++;
			}

		}

	}
	///gan lai vao mang
	for (k =0;k<end-start+1;k++) {
		B[start+k].distance = temp[k].distance;
		B[start+k].u = temp[k].u;
		B[start+k].v = temp[k].v;
	}
	delete temp;
}

void MergeSort(Edge *B,int start,int end) {
	if (start < end ) {
		int mid  = (start+end) /2;
		MergeSort(B,start,mid);
		MergeSort(B,mid+1,end);
		Merge(B,start,mid,end);
	}
}

///------------------------------///


//Find parent node
int Find_Set(int x) {
	while (parent[x] > -1) x = parent[x];
	return x;
}

// Union two node
void Union(int u, int v) {
	if (parent[u] > parent[v]) {
		parent[v] += parent[u];
		parent[u] = v;
	} else {
		parent[u] +=parent[v];
		parent[v] = u;
	}
}


void Kruskal(int Di, int point) {
	V = N+1;
	nEdge = V*(V-1)/2;
	// Add edges in EdgeList
	createListEdges(nEdgeList);

	for (int i = 0;i<V;i++) {
		parent[i] = -1;
	}
	//Sort edges in increasing order on basis of cost
	MergeSort(nEdgeList,0,nEdge-1);


	int k =0;
	for (int i = 0; i< nEdge;i++) {
		// u and v are vertices of edge i
		// find parent of u,v
		int u = Find_Set(nEdgeList[i].u);
		int v = Find_Set(nEdgeList[i].v);

		//Check u and v have the same parent
		if (v != u) {
			// Save in List;
			if (nEdgeList[i].u == N) {
			    ListEdge[Di][k].u = point;
			} else {
				ListEdge[Di][k].u = nEdgeList[i].u;
			}
			if (nEdgeList[i].v == N) {
			    ListEdge[Di][k].v = point;
			} else {
				ListEdge[Di][k].v = nEdgeList[i].v;
			}
			ListEdge[Di][k].distance = nEdgeList[i].distance;
			k++;
			// Union u and v
			Union(u,v);
		}
		if (k == (V-1)) break;
	}
}

void printList(int Di) {
	for (int i =0;i<N;i++) {
		printf("%d-%d ",ListEdge[Di][i].u,ListEdge[Di][i].v);
	}
	printf("\n");

}
//*-------------------------END KRUKAL ALGORITHM-----------------------------*/

bool checkEdgeExit(int x, int y,int N1) {
	for (int i =0;i<N1;i++) {
		if ((ListResult[i].u == x && ListResult[i].v == y) || (ListResult[i].u == y && ListResult[i].v == x)) {
			return true;
		}
	}
	return false;
}

void printListResult(int N1) {
	for (int i =0;i<N1;i++) {
		printf("%d-%d ",ListResult[i].u,ListResult[i].v);
	}
	printf("\n");

}
void run() {

	int i,j;
	// Minimun Spaning Tree for N+1 Points ( N points of S and a representative point of the D(i)
	for (i =0;i<K;i++) {
		int point = findMinConnectFromSetDToS(&SetD[i]);
		createMatrix(point);
		// Call Kruskal Algorithm
		Kruskal(i,point);
		//printList(i);

	}
	// Calculates the sum of the spanning trees
	int k1 =0;
	float Total = 0;
	for(i =0;i<K;i++) {
		for (j =0;j<N;j++) {
			if (!checkEdgeExit(ListEdge[i][j].u, ListEdge[i][j].v,k1)) {
				//Add edge in the Result
				ListResult[k1].u = ListEdge[i][j].u;
				ListResult[k1].v = ListEdge[i][j].v;
				ListResult[k1].distance = ListEdge[i][j].distance;
				Total += ListEdge[i][j].distance;
				k1++;
			}
		}
	}
	 printf("Min MST = %0.2f\n",Total);
	printListResult(k1);
}

///*-----------------------------------------------MAIN PROGAMMING-------------------------------------------*/
int main(void)
{
	int test_case;
	int T,i,j;

	int Answer;


	freopen("DATA.OUT", "r", stdin);
//	freopen("DATA.OUT1", "w", stdout);
	setbuf(stdout, NULL);
	scanf("%d\n", &T);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		Answer = 0;
		
		/////////////////////////////////////////////////////////////////////////////////////////////
		readData();
		printf("Case #%d N= %d D =%d\n", test_case,N,K);

		createMtrixDistance();

        clock_t start = clock();
		run();
		printf("Time: %.4fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);

		/////////////////////////////////////////////////////////////////////////////////////////////
		// Print the answer to standard output(screen). 

	}
	_getch();
	return 0; //Your program should return 0 on normal termination.
}