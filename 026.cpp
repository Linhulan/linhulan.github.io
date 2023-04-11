// #include <iostream>
// #include <cstdio>

// using namespace std;
// int M, N, X;
// bool supplySp(int* sp);
// bool fight(int* sp);

// int main(void){
//   cin >> M >> N >> X;
//   int sp = 0;
//   while ( supplySp(&sp) ){
//     if ( !fight(&sp) ) {
//       break;
//     }
//   }
//   cout << N << endl;
//   return 0;
// }

// bool supplySp(int* sp){
//   while ( (*sp)<M && X>0 ){
//     *sp += N;
//     X--;
//   }
//   if ( (*sp)>=M && X>=0) {
//     *sp = M;
//     return true;
//   }
//   return false;
// }

// bool fight(int* sp){
//   if ( ~ M/N ){
//     N += M/N;
//     *(sp) = 0;
//     return true;
//   }
//   return false;
// }


// #include <iostream>
// #include <cstdlib>
// #include <algorithm>
// using namespace std;
// int area[105][2] = {0};

// int main()
// {
//   int L=0, M=0;
//   cin >> L >> M;
//   for (int i = 0; i < M; i++)
//   {
//     cin>>area[i][0]>>area[i][1];
//   }
//   // cout << "--------cin end-------" << endl;
 
//   // sort 
//   int i=0, j=0;
//   for (j=0; j<M-1; j++){
//     int minIdx = j;
//     for (i=j+1; i<M; i++) {
//       if ( area[i][0] < area[minIdx][0] ) {
//         minIdx = i;
//       }
//     }
//     int tmp0 = area[j][0];
//     int tmp1 = area[j][1];
//     area[j][0] = area[minIdx][0];
//     area[j][1] = area[minIdx][1];
//     area[minIdx][0] = tmp0;
//     area[minIdx][1] = tmp1;
//   }
    

//   // for(int i=0; i<M; i++){
// 	//   cout << area[i][0] << " " << area[i][1] << " " << endl;
//   // }
//   // cout << endl;

//   // 端点0处也有树
//   int count = area[0][1] - area[0][0] + 1;    // 记录减少了多少树
// 	L -= area[0][1] - area[0][0] + 1;
//   // printf("L = %d  d=%d\n", L, area[0][1] - area[0][0] + 1);

//   int start = area[0][0], end = area[0][1];
// 	for(int i=1; i<M; i++){
// 		// |----|  [----]   区间不相交
//     if ( area[i][0] > end ){
//       start = area[i][0];
// 	    end = area[i][1];
//       L -= (end - start + 1);
//       count += (end - start + 1);
//     }
// 	  else {
//       // |-[---]|   //完全包含在上一个区间内
//       if ( end >= area[i][1] ){
//         continue;
//       }

//       // |---[-|---]   部分包含，且左端点已经减掉了
//       start = end;    // 起点等于上一次的终点
// 		  end = area[i][1]; 
//       L -= (end - start);
//       count += (end - start);
// 	  }
//     // printf("------------No.%d-------------\n", i);
//     // printf("start = %d   end = %d  L=%d  count=%d\n", start, end, L, count);
//   }
//   cout << L+1 << endl;
// }


/*
1000 5
0 100
101 200
900 1000
207 400
401 899
6

10000 10
123 134
890 1231
1321 3123
3333 4444
9999 10000
8888 9988
4555 4666
5000 6000
8007 8887
6777 8000

2411
*/

// #include <iostream>
// using namespace std;

// /*
// dp[i] = 2*dp[i-1]+dp[i-2]

// dp[1] = 1;
// dp[2] = 2;
// */

// int main(){

//   int n = 0;
//   cin >> n;
//   int dp[2] = {1, 2};
//   int k = 0;
//   while ( n-- ){
//     dp[0] = 1;
//     dp[1] = 2;
//     cin >> k;
//     for ( int i=2; i<k; ++i){
//       int tmp = dp[1];
//       dp[1] = (2*dp[1] + dp[0])%32767;
//       dp[0] = tmp;
//     }
//     if ( k<2 ) {
//       cout << dp[k-1] << endl;
//     } else {
//       cout << dp[1] << endl;
//     }
//   }
//   return 0;
// }

// 36
// #include <iostream>
// using namespace std;

// void printBit(int n){
//   printf("%d = ", n);
//   for ( int i=31; i>=0; --i){
//     printf("%u", n&(1<<i)?1:0);
//   }
//   printf("\n------------------------------\n\n");
// }

// // 第i位 = m的第i位
// int bitManipulation1(int n, int m, int i) {
// // 在此处补充你的代码
//   return ( n&~(n&(1<<i)) | m&(1<<i) );
// }

// int main() {
// 	int n, m, i, t;
// 	cin >> t;
// 	while (t--) { 
// 		cin >> n >> m >> i;
// 		cout << bitManipulation1(n, m, i) << endl << endl;
// 	}
// 	return 0;
// }


// #include <iostream>
// using namespace std;

// int bitManipulation3(int n, int i) {
// // 在此处补充你的代码
//   return (n^(-1)<<(32-i));
// }

// int main() {
// 	int t, n, i;
// 	cin >> t;
// 	while (t--) {
// 		cin >> n >> i;
// 		cout << bitManipulation3(n, i) << endl;
// 	}
// 	return 0;
// }


// #include <iostream>
// #include <cstring>

// int main(){
//   // string s;
//   char s[100002];
//   scanf("%s", s);
//   int map[26][2] = {0};
//   int i=0;
//   int len = strlen(s);
//   for (i=0; i<len; i++ ){
//     int idx = s[i]-'a';
//     if ( map[idx][0] > 2 ){
//       continue ;
//     } else if ( map[idx][0]++ == 0 ){
//       map[idx][1] = i;
//     }
//   }

//   // for ( int i=0; i<26; i++ ){
//   //   cout << "("  << (char)(i+'a') << " "
//   //        << (map[i][0]) << " " << map[i][1] << ") ";
//   //   if ( !(i%4)  ) cout << endl;
//   // }

//   int minIdx = 100001;
//   for (i=0; i<26; i++ ){
//     if ( map[i][0]==1 ){
//       if ( minIdx > map[i][1] ){
//         minIdx = map[i][1];
//         // cout << "minIdx = " << minIdx << endl;
//       }
//     }
//   }
//   if ( minIdx == 100001 ) printf("no");
//   else {
//     printf("%c", s[minIdx]);
//   }
  
//   return 0;
// }




#include <iostream>
#include <algorithm>
#include <string.h>
#include <cmath>
using namespace std;

template<typename T>
void Print(T* arr, int size){
  for ( int i=0; i<size; ++i){
    cout << arr[i] << endl;
  }
  cout << endl;
}

typedef struct member {
  int id;
  int forceVal;
} Member;

ostream& operator<<(ostream& os, const Member& mem) {
    os << "id: " << mem.id << ", forceVal: " << mem.forceVal;
    return os;
}

struct increaseForce {
  bool operator() ( const Member &a1, const Member&a2 ) const {
    return a1.forceVal < a2.forceVal;
  }
};

Member binarySearch(Member *arr , int val, int size){
  int lo = 0, hi = size;
  while ( lo<hi ){
    int mid = (lo + hi)/2;
    if ( arr[mid].forceVal == val ){
      hi = mid;
    } else if ( arr[mid].forceVal > val ){
      hi = mid;
    } else if ( arr[mid].forceVal < val ){
      lo = mid+1;
    }
  }
  if ( lo>0 ){
    int diff_hi = abs(arr[lo].forceVal - val);
    int diff_lo = abs(arr[lo-1].forceVal - val);
    return diff_hi > diff_lo ? arr[lo-1] : arr[lo];
  }
  return arr[lo];
}

int main() {
  Member facer = {1, 1000000000};
  int n;
  cin >> n;
  int len = n;
  Member* newMem = new Member[len];
  Member* oldMem = new Member[len+1];
  oldMem[0] = facer;
  int i = 0;
  int old_i = 1;
  Member rival;
  while ( n-- ){
    // printf("==========No.%d==========\n", i);
    cin >> newMem[i].id >> newMem[i].forceVal;
    if ( newMem[i].forceVal != rival.forceVal ){
      rival = binarySearch(oldMem, newMem[i].forceVal, old_i);
    }

    // printf("new Member id:%d --VS-- ", newMem[i].id);
    // cout << rival << endl;
    // // cout << "===============================================" << endl;
    cout << newMem[i].id << " " << rival.id << endl;

    oldMem[old_i] = newMem[i];
    if ( oldMem[old_i].forceVal < oldMem[old_i-1].forceVal ){
      sort(oldMem, oldMem+old_i, increaseForce());
    }

    old_i ++;
    i++;
    // printf("oldMembers: \n");
    // Print(oldMem, old_i);
    // cout << endl;
  }

  // cout << newMem[0];
  // Print(newMem, len);
  // sort(newMem, newMem+len, increaseForce());
  // Print(newMem, len);
  delete[] newMem;
  delete[] oldMem;

  return 0;
}


