//#include <stdio.h>
//#include <conio.h>
//
//const int CoordinateMaxValue = 1000;
//const int MaxPointOfSet = 50;
//const int MaxSetOfD = 10;// Max Set of D
//const unsigned long long Mod = ((1 << 31) - 1);
//long long seed = 123456789;
//long long a = 1103515245;
//long long c = 12345;
//int K, N,M;
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
//	freopen("DATA.OUT", "w", stdout);
//	setbuf(stdout, NULL);
//	//scanf("%d", &T);
//	T = 10;
//	printf("%d\n",T);
//	for (test_case = 1; test_case <= T; ++test_case)
//	{
//		Answer = 0;
//		//Random N point of S and K set D
//		N = 1+my_random()%MaxPointOfSet;
//		K = 1+my_random()%MaxSetOfD;
//		printf("%d %d %d\n",test_case, N, K);
//
//		// N point of S
//		for (i =0;i<N;i++) {
//			//Random x, y cordinater of N point
//			printf("%d %d ", ran_coordinate(), ran_coordinate());
//		}
//		printf("\n");
//
//		//Random K set D
//		M = 1+my_random()%MaxPointOfSet;
//		for (i =0;i<K;i++) {
//			// Incase every set of D have different number point
//			//M = 1+my_random()%MaxPointOfSet;
//			printf("%d\n", M);
//			for(j =0;j<M;j++) {
//			   printf("%d %d ", ran_coordinate(), ran_coordinate());
//			}
//			printf("\n");
//		}
//
//	}
//	_getch();
//	return 0; //Your program should return 0 on normal termination.
//}