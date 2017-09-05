//#include <stdio.h>
//#include <conio.h>
//#include <math.h>
//const int CoordinateMaxValue = 1000;
//const int MaxPointOfSetS = 50; // Max Point of S
//const int MaxSetOfD = 10;// Max Set of D
//const int MaxPointOfSetD = 50;// Max Point of every set D
//const float MAX_DISTANCE = 10000000000;
//
//float Distance[MaxPointOfSetS+MaxPointOfSetD*MaxSetOfD+1][MaxPointOfSetS+MaxPointOfSetD*MaxSetOfD+1];
//int P[MaxPointOfSetS+MaxPointOfSetD*MaxSetOfD+1][2];
//int S[MaxPointOfSetS][2];
//int D[MaxSetOfD][MaxPointOfSetD][2];
//int M[MaxSetOfD]; // Number Point of every set D
//
//int K;// Number Set in D
//int N;// Number points of S
//int TP;// Total point 
//
//
//struct Set {
//	int id;
//	int start;
//	int end;
//};
//Set SetS,SetD[MaxPointOfSetD];
//void readData() {
//	int testcase;
//	int i,j;
//	int pi = 0;
//	scanf("%d %d %d\n", &testcase,&N,&K);
//	//Read N points of set S
//	for (i=0;i<N;i++) {
//		scanf("%d %d", &S[i][0],&S[i][1]);
//		P[pi][0] = S[i][0];
//		P[pi][1] = S[i][1];
//		pi++;
//	}
//	scanf("\n");
//	SetS.id = -1;
//	SetS.start = 0;
//	SetS.end = N-1;
//	//Read K set D
//	for (i =0;i<K;i++) {
//		scanf("%d", &M[i]);
//		SetD[i].id = i;
//		SetD[i].start = pi;
//		SetD[i].end = pi+M[i]-1;
//
//		for (j = 0;j<M[i];j++) {
//			scanf("%d %d", &D[i][j][0],&D[i][j][1]);
//			P[pi][0] = D[i][j][0];
//		    P[pi][1] = D[i][j][1];
//		    pi++;
//		}
//		scanf("\n");
//	}
//}
//
//float calcuDistance(int x1, int y1,int x2,int y2) {
//	return (float)sqrt((float)(x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
//}
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
/////
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
//// Create matrix N+1 of S and representative of the setD(i)
//float Matrix[MaxPointOfSetS+1][MaxPointOfSetS+1];
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
/////
//struct Edge {
//	int u,v;
//	int distance;
//};
////Lis
//Edge  ListEdge[MaxSetOfD][MaxPointOfSetS+1];
//Edge ListResult[MaxPointOfSetS*MaxPointOfSetS];
//// Kruskal Algorithm
//
////
//void run() {
//  //
//	int i,j;
//	for (i =0;i<K;i++) {
//		int point = findMinConnectFromSetDToS(&SetD[i]);
//		createMatrix(point);
//		// Call Kruskal Algorithm
//
//
//
//
//	}
//
//
//}
//
//
//int main(void)
//{
//	int test_case;
//	int T,i,j;
//
//	int Answer;
//
//
//	freopen("DATA.OUT", "r", stdin);
//	setbuf(stdout, NULL);
//	scanf("%d\n", &T);
//	for (test_case = 1; test_case <= T; ++test_case)
//	{
//		Answer = 0;
//		/////////////////////////////////////////////////////////////////////////////////////////////
//		readData();
//		createMtrixDistance();
//		run();
//
//
//
//
//
//	
//		/////////////////////////////////////////////////////////////////////////////////////////////
//		// Print the answer to standard output(screen). 
//		printf("Case #%d \n", test_case);
//	}
//	_getch();
//	return 0; //Your program should return 0 on normal termination.
//}