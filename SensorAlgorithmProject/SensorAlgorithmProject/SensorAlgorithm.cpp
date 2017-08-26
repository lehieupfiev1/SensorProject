#include <stdio.h>
#include <conio.h>
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
int ListMST[MaxPointOfSetS+MaxPointOfSetD];// List Node Minimum Spanning Tree

int K;// Number Set in D
int N;// Number points of S
int TP;// Total point 

struct Set {
	int id;
	int start;
	int end;
};
Set SetS,SetD[MaxPointOfSetD];

struct Node{
	int idSet;
	int stNode;
	int desNode;
	float distance;
};

Node HeapNode[1000000];

void swapNode(int x,int y) {
	int temp;
	float temp1;
	//swape isSet
	temp = HeapNode[x].idSet;
	HeapNode[x].idSet = HeapNode[y].idSet;
	HeapNode[y].idSet = temp;
	//Swap start node
	temp = HeapNode[x].stNode;
	HeapNode[x].stNode = HeapNode[y].stNode;
	HeapNode[y].stNode = temp;
	//Swap end node
	temp = HeapNode[x].desNode;
	HeapNode[x].desNode = HeapNode[y].desNode;
	HeapNode[y].desNode = temp;
	//Swap distance node
	temp1 = HeapNode[x].distance;
	HeapNode[x].distance = HeapNode[y].distance;
	HeapNode[y].distance = temp1;
}
//Dung heap
int sizeHeap;
int findMin(int x, int y) {
	if (HeapNode[x].distance < HeapNode[y].distance ) return x;
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
	Node *result = new Node();
	if (sizeHeap >0) {
		result->idSet= HeapNode[1].idSet;
		result->stNode = HeapNode[1].stNode;
		result->desNode = HeapNode[1].desNode;
		result->distance = HeapNode[1].distance;

		swapNode(1,sizeHeap);
		sizeHeap--;
		sink(1);
	}
	return result;
};
//-------------------------/////////////////////////


void findMinConnectFromSetToSet(Set *setA, Set *setB) {
	int i,j;
	int startA = setA->start;
	int endA = setA->end;
	int startB = setB->start;
	int endB = setB->end;

	Node *n = new Node();
	n->idSet = setB->id;
	n->distance = MAX_DISTANCE;

	for (i= startA; i<=endA; i++) {
		for (j= startB; j<=endB; j++) {
			if (n->distance > Distance[i][j]) {
				n->distance = Distance[i][j];
				n->stNode = i;
				n->desNode = j;
			}
		}
	}
	//Add node to Heap;
	push(n);

}

void findMinConnectFromNodeToSet( int node, Set *set) {
	int i,j;
	int start = set->start;
	int end = set->end;

	Node *n = new Node();
	n->idSet = set->id;
	n->distance = MAX_DISTANCE;
    for (i = start;i<=end;i++) {
		if (n->distance > Distance[node][i]) {
			n->distance = Distance[node][i];
			n->stNode = node;
			n->desNode = i;
		}
	}
	//Add node to Heap
	push(n);

}

void run() {
	int i,j;
	bool visisted[MaxPointOfSetD];
	sizeHeap =0;
	// Add min to Heap

	for (i=0;i<K;i++) {
		findMinConnectFromSetToSet(&SetS,&SetD[i]);
	}
	//resetArray
	for (i=0;i<K;i++) {
		visisted[i] = false;
	}
	for(i =0;i<N;i++) {
		ListMST[i] = i;
	}

	bool finish = true;
	int count = 0;
	while (finish) {
     //get header of Heap
		Node *header = pop();
		while (visisted[header->idSet]) {
			header = pop();
		}

		//
		visisted[header->idSet] = true;
		int point = header->desNode;
		ListMST[N+count] = point;
		count++;
		delete(header);
		if (count == K) finish = false;

	 // find Node from header to other Node
		for (i = 0;i<K;i++) {
			if (!visisted[i]) {
				findMinConnectFromNodeToSet(point,&SetD[i]);
			}
		}

	}


}

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

int main(void)
{
	int test_case;
	int T,i,j;

	int Answer;


	freopen("DATA.OUT", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d\n", &T);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		Answer = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
		readData();
		createMtrixDistance();
		run();



	
		/////////////////////////////////////////////////////////////////////////////////////////////
		// Print the answer to standard output(screen). 
		printf("Case #%d \n", test_case);
		for (i =0;i<N+K;i++) {
			printf("%d ", ListMST[i]);
		}
		printf("\n");
	}
	_getch();
	return 0; //Your program should return 0 on normal termination.
}