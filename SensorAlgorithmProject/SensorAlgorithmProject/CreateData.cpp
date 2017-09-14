//
//
//#include <stdio.h>
//#include <conio.h>
//
//const int CoordinateMaxValue = 1000;
//const int MaxPointOfSetP = 10;
//const int MaxSetOfD = 5;// Max Set of D
//const int MaxPointOfSetD = 10;// Max Point of every set D
//const int MaxRs= 50;// Max Rs 
//const int MaxRt= 40;// Max Rt 
//
//const unsigned long long Mod = ((1 << 31) - 1);
//long long seed = 123456789;
//long long a = 1103515245;
//long long c = 12345;
//int K,M,P,Rs,Rt;
//int my_random()
//{
//       seed = (a*seed + c) % Mod;
//       return (int)seed;
//}
//
//int ran_coordinate() {
//	return my_random()%CoordinateMaxValue;
//}
// 
//int main(void)
//{
//	int test_case;
//	int T,i,j;
//	int Answer;
//
//	//freopen("input.txt", "r", stdin);
//	freopen("DATA_02.IN", "w", stdout);
//	setbuf(stdout, NULL);
//	//scanf("%d", &T);
//	T = 10;
//	printf("%d\n",T);
//	for (test_case = 1; test_case <= T; ++test_case)
//	{
//		Answer = 0;
//		//Random P point of T taget and K set D
//		P = 1+my_random()%MaxPointOfSetP;
//		K = 1+my_random()%MaxSetOfD;
//		printf("%d %d %d\n",test_case, P, K);
//
//		// P point of Taget T
//		for (i =0;i<P;i++) {
//			//Random x, y cordinater of P point
//			printf("%d %d ", ran_coordinate(), ran_coordinate());
//		}
//		printf("\n");
//
//		//Random K set D
//		M = 1+my_random()%MaxPointOfSetD;
//		for (i =0;i<K;i++) {
//			// Incase every set of D have different number point
//			//M = 1+my_random()%MaxPointOfSetD;
//			printf("%d\n", M);
//			for(j =0;j<M;j++) {
//			   printf("%d %d ", ran_coordinate(), ran_coordinate());
//			}
//			printf("\n");
//		}
//		//Random Rs and Rt
//		Rs = 1+my_random()%MaxRs;
//		Rt = 1+my_random()%MaxRt;
//		printf("%d %d\n", Rs, Rt);
//
//	}
//	_getch();
//	return 0; //Your program should return 0 on normal termination.
//}