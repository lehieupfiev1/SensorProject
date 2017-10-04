#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>

const int CoordinateMaxValue = 10000;
const int MaxPointOfSetP = 1000; // Max Point of p taget 
const int MaxSetOfD = 10;// Max Set of D
const int MaxPointOfSetD = 1000;// Max Point of every set D
const float MAX_DISTANCE = 1000000000000;

float Distance[MaxPointOfSetP+MaxPointOfSetD*MaxSetOfD+1][MaxPointOfSetP+MaxPointOfSetD*MaxSetOfD+1];
float P[MaxPointOfSetP+MaxPointOfSetD*MaxSetOfD+1][2];
float Taget[MaxPointOfSetP][2];
float S[MaxPointOfSetP][2];
float D[MaxSetOfD][MaxPointOfSetD][2];
int M[MaxSetOfD]; // Number Point of every set D

int List[MaxPointOfSetP+MaxPointOfSetD];

//Function
void printMST(int V,int *list);
int Extract_Min(int V);
float Prime(int *List, int V, int start);
void CalculateSensor(int *list) ;

int K;// Number Set in D
int N;// Number points of S
int TP;// Total point 
int TagetPoint;// Total point of Taget
float Rs, Rt;

 struct Sensor {
	 float x;
	 float y;
 };
 Sensor ListSensor[1000000];
 int numberSersor;
 void printListSensor(Sensor *listSensor, int number);

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
	int with, height;
	int numberSensor;
	int tem;

	scanf("%d %d %f %f",&with,&height, &Rs,&Rt);
	scanf("%d %d %d\n", &TagetPoint,&K,&numberSensor);
	//Read P points of taget Set
	for (i=0;i<TagetPoint;i++) {
		scanf("%f %f", &Taget[i][0],&Taget[i][1]);
	}
	scanf("\n");

	//Read K set D
	for (i =0;i<K;i++) {
		scanf("%d", &M[i]);
		for (j = 0;j<M[i];j++) {
			scanf("%f %f %d", &D[i][j][0],&D[i][j][1],&tem);
		}

		scanf("\n");
	}
	//Read Rs and Rt
	
}

//Find Target-covering sensor
void Find_Taget_Corvering_Sensor() {
	// Vi du tim duoc tap S corvering
	N = TagetPoint;
	for (int i=0;i<N;i++) {
		S[i][0] = Taget[i][0];
		S[i][1] = Taget[i][1];
	}
	//  Code algorithm in here 



	//---------------------------///


	//---- Move to List  P--------/
	int pi = 0;
	int i,j;
	//Add List S to List P
	for (i=0 ;i<N; i++) {
		P[pi][0] = S[i][0];
		P[pi][1] = S[i][1];
		pi++;
	}
	SetS.id = -1;
	SetS.start = 0;
	SetS.end = N-1;

	//Add List Di to List P
	for (i =0;i<K;i++) {
		SetD[i].id = i;
		SetD[i].start = pi;
		SetD[i].end = pi+M[i]-1;

		for (j = 0;j<M[i];j++) {
			P[pi][0] = D[i][j][0];
		    P[pi][1] = D[i][j][1];
		    pi++;
		}
	}
}

float calcuDistance(float x1, float y1,float x2,float y2) {
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
	 CalculateSensor(List);
	 printf("Number Sensor = %d\n",numberSersor);
	 //printListSensor(ListSensor,numberSersor);
 }
 


/// Thuat toan Prime
int parent[MaxPointOfSetP+MaxPointOfSetD];
float key[MaxPointOfSetP+MaxPointOfSetD];
bool visited[MaxPointOfSetP+MaxPointOfSetD];
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
	for (int i = 1;i<V;i++) {
		printf("%d-%d " ,list[i],list[parent[i]]);
	}
	printf("\n");
}

// Calculate number of sensor a segment
 void addSensorInSegment(float x1, float y1,float x2, float y2, Sensor *listSensor) {
	 float distance = calcuDistance(x1,y1,x2,y2);
	 if (distance <= 2*Rt && distance > 0) {
		 listSensor[numberSersor].x = (x1+x2)/2;
		 listSensor[numberSersor].y = (y1+y2)/2;
		 numberSersor++;
	 } else {
		 int k = (int) distance/Rt;
		 float tempx = x2-x1;
		 float tempy = y2-y1;
		 float temp1 = x1*x1+y1*y1 -(x2*x2+y2*y2);
		 float temp2 = x2*y1 - x1*y2;
		 //He pt 2 an
		 //  2tempx*X + 2tempy*Y + temp1 - (kRt)^2 + (distance - k*Rt)^2 = 0;
		 //  (tempy/tempx)* X + temp2/tempx = Y;
		 for (int i = 1;i<=k;i++) {
			 if (tempx != 0) {
				 float temp3 = (distance - i*Rt)*(distance - i*Rt) - (i*Rt)*(i*Rt);
				 listSensor[numberSersor].x = -(2*tempy*temp2 + tempx*temp1+ tempx*temp3)/(2*tempx*tempx +2*tempy*tempy);
				 listSensor[numberSersor].y = tempy*listSensor[numberSersor].x/tempx + temp2/tempx;
				 numberSersor++;
			 } else {
				 float temp3 = (distance - i*Rt)*(distance - i*Rt) - (i*Rt)*(i*Rt);
				 listSensor[numberSersor].x = x1;
				 listSensor[numberSersor].y = -(temp1+temp3)/(2*tempy);
				 numberSersor++;
			 }
		 }

	 }
 }

 int count[MaxPointOfSetP+MaxSetOfD];
 void CalculateSensor(int *list) {
	 // Add Sensor S to ListSensor 
	 numberSersor = N;
	 for (int i=0; i<N ;i++ ) {
		 ListSensor[i].x = S[i][0];
		 ListSensor[i].y = S[i][1];
	 }
	 //Add point trung voi diem Di
	 // Reset count matrix 
	 for (int i =0;i<N+K;i++) {
		 count[i]= 0;
	 }
	 for (int i =1;i<N+K;i++) {
		 count[i]++;
		 count[parent[i]]++;
	 }
	 for (int i =N;i<N+K;i++) {
		 if(count[i] >1) {
			 //Add Sensor point
			 ListSensor[numberSersor].x = P[list[i]][0];
		     ListSensor[numberSersor].y = P[list[i]][1];
			 numberSersor++;
		 }
	 }

	 // Add point between a segment

	 for(int i = 1;i<N+K;i++) {
		 addSensorInSegment(P[list[i]][0],P[list[i]][1],P[list[parent[i]]][0],P[list[parent[i]]][1],ListSensor);
	 }
 }
 void printListSensor(Sensor *listSensor, int number) {
	for (int i = 0;i<number;i++) {
		printf("%0.2f-%0.2f " ,listSensor[i].x,listSensor[i].y);
	}
	printf("\n");
 }


int main(void)
{
	int test_case;
	int T,i,j;

	int Answer;


	freopen("test.INP", "r", stdin);
	//freopen("SENSOR_DATA_02.OUT", "w", stdout);
	setbuf(stdout, NULL);
	//scanf("%d\n", &T);
	for (test_case = 1; test_case <= 1; ++test_case)
	{
		Answer = 0;
				
		/////////////////////////////////////////////////////////////////////////////////////////////
		readData();
		printf("Case #%d P= %d D =%d\n", test_case,TagetPoint,K);

		//Step 1: Find target-covering sensor
		Find_Taget_Corvering_Sensor();

		createMtrixDistance();

		// Step 2: 
		clock_t start = clock();
		run();
		printf("Time: %.4fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);

		/////////////////////////////////////////////////////////////////////////////////////////////
		// Print the answer to standard output(screen). 

		//for (i =0 ;i<K+N;i++) {
		//  printf("%d ", List[i]);
		//}
		//printf("\n");
	}
	_getch();
	return 0; //Your program should return 0 on normal termination.
}