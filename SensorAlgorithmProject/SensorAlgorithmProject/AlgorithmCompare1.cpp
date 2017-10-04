//#include <stdio.h>
//#include <conio.h>
//#include <time.h>
//#include <math.h>
//const int CoordinateMaxValue = 10000;
//const int MaxPointOfSetP = 1000; // Max Point of p taget 
//const int MaxSetOfD = 10;// Max Set of D
//const int MaxPointOfSetD = 1000;// Max Point of every set D
//const float MAX_DISTANCE = 1000000000000;
//
//float Distance[MaxPointOfSetP+MaxPointOfSetD*MaxSetOfD+1][MaxPointOfSetP+MaxPointOfSetD*MaxSetOfD+1];
//float P[MaxPointOfSetP+MaxPointOfSetD*MaxSetOfD+1][2];
//float Taget[MaxPointOfSetP][2];
//float S[MaxPointOfSetP][2];
//float D[MaxSetOfD][MaxPointOfSetD][2];
//int M[MaxSetOfD]; // Number Point of every set D
//
//int K;// Number Set in D
//int N;// Number points of S
//int TP;// Total point 
//int TagetPoint;// Total point of Taget
//float Rs, Rt;
//
// struct Sensor {
//	 float x;
//	 float y;
// };
// Sensor ListSensor[1000000];
// int numberSersor;
// void printListSensor(Sensor *listSensor, int number);
// void CalculateSensor(int number);
//
//struct Set {
//	int id;
//	int start;
//	int end;
//};
//Set SetS,SetD[MaxPointOfSetD];
//
//void readData() {
//	int testcase;
//	int i,j;
//	int with, height;
//	int numberSensor;
//	int tem;
//
//	scanf("%d %d %f %f",&with,&height, &Rs,&Rt);
//	scanf("%d %d %d\n", &TagetPoint,&K,&numberSensor);
//	//Read P points of taget Set
//	for (i=0;i<TagetPoint;i++) {
//		scanf("%f %f", &Taget[i][0],&Taget[i][1]);
//	}
//	scanf("\n");
//
//	//Read K set D
//	for (i =0;i<K;i++) {
//		scanf("%d", &M[i]);
//		for (j = 0;j<M[i];j++) {
//			scanf("%f %f %d", &D[i][j][0],&D[i][j][1],&tem);
//		}
//
//		scanf("\n");
//	}
//	//Read Rs and Rt
//	
//}
//
////Find Target-covering sensor
//void Find_Taget_Corvering_Sensor() {
//	// Vi du tim duoc tap S corvering
//	N = TagetPoint;
//	for (int i=0;i<N;i++) {
//		S[i][0] = Taget[i][0];
//		S[i][1] = Taget[i][1];
//	}
//	//  Code algorithm in here 
//
//
//
//	//---------------------------///
//
//
//	//---- Move to List  P--------/
//	int pi = 0;
//	int i,j;
//	//Add List S to List P
//	for (i=0 ;i<N; i++) {
//		P[pi][0] = S[i][0];
//		P[pi][1] = S[i][1];
//		pi++;
//	}
//	SetS.id = -1;
//	SetS.start = 0;
//	SetS.end = N-1;
//
//	//Add List Di to List P
//	for (i =0;i<K;i++) {
//		SetD[i].id = i;
//		SetD[i].start = pi;
//		SetD[i].end = pi+M[i]-1;
//
//		for (j = 0;j<M[i];j++) {
//			P[pi][0] = D[i][j][0];
//		    P[pi][1] = D[i][j][1];
//		    pi++;
//		}
//	}
//}
//
//// CalcularDistance between two point
//float calcuDistance(float x1, float y1,float x2,float y2) {
//	return (float)sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
//}
//
//void createMtrixDistance() {
//	int i,j;
//	//Total point
//	TP = N;
//	for (i=0;i<K;i++) {
//		TP+= M[i];
//	}
//	// Calculate Distance
//	for (i =0;i<TP;i++) {
//		for (j =0;j<=i;j++) {
//			if (i==j) {
//				Distance[i][j] = 0;
//			} else {
//				Distance[i][j] = Distance[j][i] = calcuDistance(P[i][0],P[i][1],P[j][0],P[j][1]);
//			}
//		}
//	}
//}
//
///// Minimun distance between two Sets ( D(i) and S)
//int findMinConnectFromSetDToS(Set *setD) {
//	int i,j;
//	int startD = setD->start;
//	int endD = setD->end;
//
//	int point;
//	float distance = MAX_DISTANCE;
//
//	for (i= 0; i<N; i++) {
//		for (j= startD; j<=endD; j++) {
//			if (distance > Distance[i][j]) {
//				distance = Distance[i][j];
//				point = j;
//			}
//		}
//	}
//
//	return point;
//}
//
//// Create matrix N+1 of S and representative of the setD(i)
//float Matrix[MaxPointOfSetP+1][MaxPointOfSetP+1];
//void createMatrix(int point) {
//	int i,j;
//	for (i=0;i<N;i++) {
//		for (j=0;j<=i;j++) {
//			Matrix[i][j] = Matrix[i][j] = Distance[i][j];
//		}
//	}
//	for (i =0;i<N;i++) {
//		Matrix[i][N] = Matrix[N][i] = Distance[i][point];
//	}
//	Matrix[N][N] = 0;
//}
//
////*-----------------------Start KRUKAL Algorithm ---------------------------------*/
//struct Edge {
//	int u,v;
//	float distance;
//};
////List Edges
//Edge ListEdge[MaxSetOfD][MaxPointOfSetP+2];// List Egde is egde result after using Krukal Algorithm with N+1 matrix
//Edge ListResult[(MaxPointOfSetP+1)*MaxSetOfD];//ListResult is egde result of this algorithm;
//Edge nEdgeList[MaxPointOfSetP*(MaxPointOfSetP+1)/2+1];
//
//int nEdge,V;//number edge and vertices.
//int parent[MaxPointOfSetP+2];
//
//
//void createListEdges(Edge *edgeList) {
//	int i,j;
//	int k = 0;
//	for (i = 0;i<=N;i++) {
//		for (j = 0;j<i;j++) {
//			if (i != j ) {
//				edgeList[k].u = i;
//				edgeList[k].v = j;
//				edgeList[k].distance = Matrix[i][j];
//				k++;
//			}
//		}
//	}
//}
//
////Sort Egde (Merge Sort Algorithm)
//void Merge(Edge *B,int start,int mid,int end) {
//	//Khoi tao
//	int i = start;
//	int j = mid+1;
//	Edge *temp = new Edge[end-start+1];
//
//	//
//	int k;
//	for (k=0;k<end-start+1;k++) {
//
//		if (B[i].distance < B[j].distance) {
//			temp[k].distance = B[i].distance;
//			temp[k].u = B[i].u;
//			temp[k].v = B[i].v;
//			i++;
//		} else {
//			temp[k].distance = B[j].distance;
//			temp[k].u = B[j].u;
//			temp[k].v = B[j].v;
//			j++;
//		}
//
//		if (i==mid+1) {
//			while (j <= end) {
//				k++;
//				temp[k].distance = B[j].distance;
//				temp[k].u = B[j].u;
//				temp[k].v = B[j].v;
//				j++;
//			}
//		}
//
//		if (j == end+1) {
//			while(i<= mid) {
//				k++;
//				temp[k].distance = B[i].distance;
//				temp[k].v = B[i].v;
//				temp[k].u = B[i].u;
//				i++;
//			}
//
//		}
//
//	}
//	///gan lai vao mang
//	for (k =0;k<end-start+1;k++) {
//		B[start+k].distance = temp[k].distance;
//		B[start+k].u = temp[k].u;
//		B[start+k].v = temp[k].v;
//	}
//	delete temp;
//}
//
//void MergeSort(Edge *B,int start,int end) {
//	if (start < end ) {
//		int mid  = (start+end) /2;
//		MergeSort(B,start,mid);
//		MergeSort(B,mid+1,end);
//		Merge(B,start,mid,end);
//	}
//}
//
/////------------------------------///
//
//
////Find parent node
//int Find_Set(int x) {
//	while (parent[x] > -1) x = parent[x];
//	return x;
//}
//
//// Union two node
//void Union(int u, int v) {
//	if (parent[u] > parent[v]) {
//		parent[v] += parent[u];
//		parent[u] = v;
//	} else {
//		parent[u] +=parent[v];
//		parent[v] = u;
//	}
//}
//
//
//void Kruskal(int Di, int point) {
//	V = N+1;
//	nEdge = V*(V-1)/2;
//	// Add edges in EdgeList
//	createListEdges(nEdgeList);
//
//	for (int i = 0;i<V;i++) {
//		parent[i] = -1;
//	}
//	//Sort edges in increasing order on basis of cost
//	MergeSort(nEdgeList,0,nEdge-1);
//
//
//	int k =0;
//	for (int i = 0; i< nEdge;i++) {
//		// u and v are vertices of edge i
//		// find parent of u,v
//		int u = Find_Set(nEdgeList[i].u);
//		int v = Find_Set(nEdgeList[i].v);
//
//		//Check u and v have the same parent
//		if (v != u) {
//			// Save in List;
//			if (nEdgeList[i].u == N) {
//			    ListEdge[Di][k].u = point;
//			} else {
//				ListEdge[Di][k].u = nEdgeList[i].u;
//			}
//			if (nEdgeList[i].v == N) {
//			    ListEdge[Di][k].v = point;
//			} else {
//				ListEdge[Di][k].v = nEdgeList[i].v;
//			}
//			ListEdge[Di][k].distance = nEdgeList[i].distance;
//			k++;
//			// Union u and v
//			Union(u,v);
//		}
//		if (k == (V-1)) break;
//	}
//}
//
//void printList(int Di) {
//	for (int i =0;i<N;i++) {
//		printf("%d-%d ",ListEdge[Di][i].u,ListEdge[Di][i].v);
//	}
//	printf("\n");
//
//}
////*-------------------------END KRUKAL ALGORITHM-----------------------------*/
//
//bool checkEdgeExit(int x, int y,int N1) {
//	for (int i =0;i<N1;i++) {
//		if ((ListResult[i].u == x && ListResult[i].v == y) || (ListResult[i].u == y && ListResult[i].v == x)) {
//			return true;
//		}
//	}
//	return false;
//}
//
//void printListResult(int N1) {
//	for (int i =0;i<N1;i++) {
//		printf("%d-%d ",ListResult[i].u,ListResult[i].v);
//	}
//	printf("\n");
//
//}
//void run() {
//
//	int i,j;
//	// Minimun Spaning Tree for N+1 Points ( N points of S and a representative point of the D(i)
//	for (i =0;i<K;i++) {
//		int point = findMinConnectFromSetDToS(&SetD[i]);
//		createMatrix(point);
//		// Call Kruskal Algorithm
//		Kruskal(i,point);
//		//printList(i);
//
//	}
//	// Calculates the sum of the spanning trees
//	int k1 =0;
//	float Total = 0;
//	for(i =0;i<K;i++) {
//		for (j =0;j<N;j++) {
//			if (!checkEdgeExit(ListEdge[i][j].u, ListEdge[i][j].v,k1)) {
//				//Add edge in the Result
//				ListResult[k1].u = ListEdge[i][j].u;
//				ListResult[k1].v = ListEdge[i][j].v;
//				ListResult[k1].distance = ListEdge[i][j].distance;
//				Total += ListEdge[i][j].distance;
//				k1++;
//			}
//		}
//	}
//
//	 CalculateSensor(k1);
//	 printf("Number Sensor = %d\n",numberSersor);
//	 //printListSensor(ListSensor,numberSersor);
//}
//
//// Calculate number of sensor a segment
// void addSensorInSegment(float x1, float y1,float x2, float y2, Sensor *listSensor) {
//	 float distance = calcuDistance(x1,y1,x2,y2);
//	 if (distance <= 2*Rt && distance > 0) {
//		 listSensor[numberSersor].x = (x1+x2)/2;
//		 listSensor[numberSersor].y = (y1+y2)/2;
//		 numberSersor++;
//	 } else {
//		 int k = (int) distance/Rt;
//		 float tempx = x2-x1;
//		 float tempy = y2-y1;
//		 float temp1 = x1*x1+y1*y1 -(x2*x2+y2*y2);
//		 float temp2 = x2*y1 - x1*y2;
//		 //He pt 2 an
//		 //  2tempx*X + 2tempy*Y + temp1 - (kRt)^2 + (distance - k*Rt)^2 = 0;
//		 //  (tempy/tempx)* X + temp2/tempx = Y;
//		 for (int i = 1;i<=k;i++) {
//			 if (tempx != 0) {
//				 float temp3 = (distance - i*Rt)*(distance - i*Rt) - (i*Rt)*(i*Rt);
//				 listSensor[numberSersor].x = -(2*tempy*temp2 + tempx*temp1+ tempx*temp3)/(2*tempx*tempx +2*tempy*tempy);
//				 listSensor[numberSersor].y = tempy*listSensor[numberSersor].x/tempx + temp2/tempx;
//				 numberSersor++;
//			 } else {
//				 float temp3 = (distance - i*Rt)*(distance - i*Rt) - (i*Rt)*(i*Rt);
//				 listSensor[numberSersor].x = x1;
//				 listSensor[numberSersor].y = -(temp1+temp3)/(2*tempy);
//				 numberSersor++;
//			 }
//		 }
//
//	 }
// }
//
// int count[MaxPointOfSetP+MaxSetOfD];
// void CalculateSensor(int number) {
//	 // Add Sensor S to ListSensor 
//	 numberSersor = N;
//	 for (int i=0; i<N ;i++ ) {
//		 ListSensor[i].x = S[i][0];
//		 ListSensor[i].y = S[i][1];
//	 }
//
//	 // Add point between a segment
//
//	 for(int i = 0;i<number;i++) {
//		 addSensorInSegment(P[ListResult[i].u][0],P[ListResult[i].u][1],P[ListResult[i].v][0],P[ListResult[i].v][1],ListSensor);
//	 }
// }
// void printListSensor(Sensor *listSensor, int number) {
//	for (int i = 0;i<number;i++) {
//		printf("%0.2f-%0.2f " ,listSensor[i].x,listSensor[i].y);
//	}
//	printf("\n");
// }
/////*-----------------------------------------------MAIN PROGAMMING-------------------------------------------*/
//int main(void)
//{
//	int test_case;
//	int T,i,j;
//
//	int Answer;
//
//
//	freopen("test.INP", "r", stdin);
////	freopen("COMPARE_DATA_02.OUT", "w", stdout);
//	setbuf(stdout, NULL);
//	//scanf("%d\n", &T);
//	for (test_case = 1; test_case <= 1; ++test_case)
//	{
//		Answer = 0;
//		
//		/////////////////////////////////////////////////////////////////////////////////////////////
//		readData();
//		printf("Case #%d P= %d D =%d\n", test_case,TagetPoint,K);
//		//Step 1: Find target-covering sensor
//		Find_Taget_Corvering_Sensor();
//
//		createMtrixDistance();
//
//		// Step 2: 
//
//        clock_t start = clock();
//		run();
//		printf("Time: %.4fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);
//
//		/////////////////////////////////////////////////////////////////////////////////////////////
//		// Print the answer to standard output(screen). 
//
//	}
//	_getch();
//	return 0; //Your program should return 0 on normal termination.
//}