#include <stdio.h>
#include <conio.h>
#include <math.h>

const int CoordinateMaxValue = 1000;
const int MaxPointOfSetS = 50; // Max Point of S
const int MaxSetOfD = 10;// Max Set of D
const int MaxPointOfSetD = 50;// Max Point of every set D
const float MAX_DISTANCE = 1000000000000;

float Distance[MaxPointOfSetS+MaxPointOfSetD*MaxSetOfD+1][MaxPointOfSetS+MaxPointOfSetD*MaxSetOfD+1];
int P[MaxPointOfSetS+MaxPointOfSetD*MaxSetOfD+1][2];
int S[MaxPointOfSetS][2];
int D[MaxSetOfD][MaxPointOfSetD][2];
int M[MaxSetOfD]; // Number Point of every set D

int List[MaxPointOfSetS+MaxPointOfSetD];

//Function
void printMST(int V,int *list);
int Extract_Min(int V);
float Prime(int *List, int V, int start);



int K;// Number Set in D
int N;// Number points of S
int TP;// Total point 
struct Node {
	int idSet;
	int stNode;
	int desNode;
	float distance;
};
Node HeapNode[10000];
int sizeHeap;
void swapNode(int x,int y) {
	int temp ;
	float temp2;
	// swap id Set
	temp = HeapNode[x].idSet;
	HeapNode[x].idSet = HeapNode[y].idSet;
	HeapNode[y].idSet = temp;
	// swap start Node
	temp = HeapNode[x].stNode;
	HeapNode[x].stNode = HeapNode[y].stNode;
	HeapNode[y].stNode = temp;
	// swap destination Node
	temp = HeapNode[x].desNode;
	HeapNode[x].desNode = HeapNode[y].desNode;
	HeapNode[y].desNode = temp;

	temp2 = HeapNode[x].distance;
	HeapNode[x].distance = HeapNode[y].distance;
	HeapNode[y].distance = temp2;
}
//Dung heap

int findMin(int x, int y) {
	if (HeapNode[x].distance  < HeapNode[y].distance ) return x;
	return y;
}


//Di xuong duoi
void sink(int p) {
	int x = p*2;
	int y = p*2+1;
	int min;
	if (p*2 +1 <= sizeHeap) {
		min = findMin(x,y);
		if (HeapNode[p].distance > HeapNode[min].distance) {
			swapNode(min,p);
			sink(min);
		}
	} else if (p*2 == sizeHeap ) {
		min = x;
		if (HeapNode[p].distance > HeapNode[min].distance) {
			swapNode(min,p);
		}
	}
} 
//Di chuyen len tren
void swim(int p) {
	if (p>1) {
		if (HeapNode[p].distance < HeapNode[p/2].distance) {
			swapNode(p,p/2);
			swim(p/2);
		}
	}
}
void push(Node *node) {
	if (sizeHeap == 0) {
		sizeHeap++;
		HeapNode[sizeHeap] = *node;
	} else {
		sizeHeap++;
		HeapNode[sizeHeap] = *node;
		swim(sizeHeap);
	}
}
Node *pop() {
	Node *node = new Node();

	if (sizeHeap >0) {
		node->idSet= HeapNode[1].idSet;
		node->stNode= HeapNode[1].stNode;
		node->desNode= HeapNode[1].desNode;
		node->distance= HeapNode[1].distance;
		swapNode(1,sizeHeap);
		sizeHeap--;
		sink(1);
	}
	return node;
};
//////----------------------------------------------------------///

struct Set{
	int id;
	int start;
	int end;
};
Set SetS, SetD[MaxSetOfD];
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

void findMinConnectFromSetToSet(Set *setA,Set *setB) {
	int i,j;
	int startA = setA->start;
	int endA = setA->end;
	int startB = setB->start;
	int endB = setB->end;

	Node *n = new Node();
	n->distance = MAX_DISTANCE;

	for (i=startA;i<=endA;i++) {
		for (j=startB;j<=endB;j++) {
			if (n->distance > Distance[i][j] ) {
				n->distance = Distance[i][j];
				n->idSet = setB->id;
				n->stNode = i;
				n->desNode = j;
			}
		}
	}
	//Add node to List Heap
	push(n);
}
 void findMinConnectFromNodeToSet(int node, Set *set) {
	 int i,j;
	 int start = set->start;
	 int end = set->end;

	 Node *n = new Node();
	 n->distance = MAX_DISTANCE;


	 for (i = start;i<= end;i++) {
		 if (n->distance > Distance[node][i]) {
			 n->distance = Distance[node][i];
			 n->idSet = set->id;
			 n->stNode = node;
			 n->desNode = i;
		 }

	 }
	 //Add Node to List Heap
	 push(n);
 }

 void run() {
	 // Add list minimum point from Set D to Set S
	 int i,j;

	 int k;
	 sizeHeap = 0;
	 for (i=0;i<K;i++) {
		 findMinConnectFromSetToSet(&SetS,&SetD[i]);
	 }

	 for (i =0;i<N;i++) {
		 List[i] = i;
	 }

	 //reset Array
	 bool visisted[MaxPointOfSetD];
	 for (i =0;i<K;i++) {
		 visisted[i] = false;
	 }
	 //


	 
	 bool findResult = true;
	 int count =0;
	 while (findResult) {
       // get Min Point from Heap
		 
		 Node *headNode = pop();
		 while (visisted[headNode->idSet]) {
			 headNode = pop();
		 }
		 visisted[headNode->idSet] = true;
		 int point = headNode->desNode;
		 List[N+count] = point;
		 delete(headNode);
		 count++;
		 if (count == K) findResult = false;

	  // Add new point To heap find From MintPoint to set D
		 for (i=0;i<K;i++) {
			 if (!visisted[i]) {
				 findMinConnectFromNodeToSet(point,&SetD[i]);
			 }
		 }
	 }


	 //Add Prime Algorithm
	 float result = Prime(List,N+K,0);
	 printf("Min MST = %0.2f\n",result);
	 printMST(N+K,List);


 }

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

/// Thuat toan Prime
int parent[MaxPointOfSetS+MaxPointOfSetD];
float key[MaxPointOfSetS+MaxPointOfSetD];
bool visited[MaxPointOfSetS+MaxPointOfSetD];
float MinMSTLengh; // Do dai cay khung nho nhat


int Extract_Min(int V) {
	float min = MAX_DISTANCE;
	int u;
	for (int i = 0;i<V;i++) {
		if (!visited[i] && key[i] <min ) {
			min = key[i];
			u =i;
		}
	}
	MinMSTLengh+= min;
	return u;
}

float Prime(int *List, int V, int start) {
	// Khoi tao
	int i,j;
	MinMSTLengh = 0;
	for (i =0;i<V;i++) {
		parent[i] = -1;
		visited[i] = false;
		key[i] = MAX_DISTANCE;
	}

	//Start search
	key[start] = 0;

	for (i =0;i<V;i++) {
		//Tim dinh co canh nho nhat
		int u = Extract_Min(V);
		visited[u] = true;

		//Duyet tat ca ca nut
		for (int v = 0;v <V;v++) {
			if (!visited[v] && Distance[List[u]][List[v]] != 0 && Distance[List[u]][List[v]] < key[v]) {
				//Luu lai nut cha va trong so moi
				key[v] = Distance[List[u]][List[v]];
				parent[v] = u;
			}
		}
	}
	return MinMSTLengh;
}

void printMST(int V,int *list) {
	for (int i = 0;i<V;i++) {
		printf("%d-%d " ,list[i],list[parent[i]]);
	}
	printf("\n");
}




int main(void)
{
	int test_case;
	int T,i,j;

	int Answer;


	freopen("DATA.OUT", "r", stdin);
	freopen("DATA.IN", "w", stdout);
	setbuf(stdout, NULL);
	scanf("%d\n", &T);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		Answer = 0;
		printf("Case #%d \n", test_case);
		/////////////////////////////////////////////////////////////////////////////////////////////
		readData();
		createMtrixDistance();
		run();




	
		/////////////////////////////////////////////////////////////////////////////////////////////
		// Print the answer to standard output(screen). 

		for (i =0 ;i<K+N;i++) {
		  printf("%d ", List[i]);
		}
		printf("\n");
	}
	_getch();
	return 0; //Your program should return 0 on normal termination.
}