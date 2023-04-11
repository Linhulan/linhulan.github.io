
#include <iostream>
#include <string>
using namespace std;

int main(){
  string s;
  cin >> s;
  int map[26][2] = {0};
  for ( int i=0; i<26; i++ ){
    map[i][0] = map[i][1] = 0;
  }

  int len = s.length();
  for ( int i=0; i<len; i++ ){
    int idx = s[i]-'a';
    if ( map[idx][0]++ == 0 ){
      map[idx][1] = i;
    }
    // map[idx][0]++;
  }


  // for ( int i=0; i<26; i++ ){
  //   cout << "("  << (char)(i+'a') << " "
  //        << (map[i][0]) << " " << map[i][1] << ") ";
  //   if ( !(i%4)  ) cout << endl;
  // }

  int minIdx = 27;
  for ( int i=0; i<26; i++ ){
    if ( map[i][0]==1 ){
      if ( map[minIdx][1] > map[i][1] ){
        minIdx = i;
        // cout << "minIdx = " << minIdx << endl;
      }
    }
  }

  cout << s[map[minIdx][1]] << endl;
  return 0;
}