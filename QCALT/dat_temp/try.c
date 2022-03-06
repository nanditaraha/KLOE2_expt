#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
 
using namespace std;
 
void trial(){
    
  pair<int,int> apair;
  vector<pair<int,int> > v_temp;
  vector< vector<pair<int,int> > > pair2dvector;
 
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      apair.first = i;
      apair.second = j;
      v_temp.push_back(apair);
    }
    pair2dvector.push_back(v_temp);
    v_temp.clear();
  }
 
  for (vector< vector<pair<int,int> > >::iterator it = pair2dvector.begin(); it != pair2dvector.end(); ++it) {
    v_temp = *it;
    for (vector<pair<int,int> >::iterator it2 = v_temp.begin(); it2 != v_temp.end(); ++it2) {
      apair = *it2;
      cout << "(" << apair.first << "," << apair.second << ") ; ";
    }
    cout << '\n';
  }
 
  //return 0;
}
