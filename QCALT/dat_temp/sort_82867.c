#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
using namespace std;

void sort(int run)
{
    FILE *fp;
    //char * filename = "myfile02.txt";
    const int numL = 1920;
    char filename[30];
    sprintf(filename, "Qcalt_temp%d.dat",run);
    fp = fopen(filename,"r");
    //const int numL = 1920;
    //Just testing first with my own numbers
    vector <float> ch(numL, 0);
    vector <float> temp(numL, 0);
    vector <float> ch_sort;
    vector <float> temp_sort;
    vector <float> ch_final;
    vector <float> temp_final;
    pair <float,float> apair;
    vector< pair<float,float>  > ch_temp;
    //vector< vector<pair<float,float> > > ch_temp;

    cout<<"size "<< ch.size()<<"\n";
    for(i=0;i<numL;i++)
      //if(fp>0)
      fscanf(fp,"%f %f",&ch[i],&temp[i]);
    
   
    for(int j=0;j<ch.size();j++)
      {
	if(temp[j]>0){
	  apair=make_pair(ch[j],temp[j]);
	  ch_temp.push_back(apair);
	}
      }
    
    sort(ch_temp.begin(), ch_temp.end());
   
    
    for (vector<pair<float,float> >::iterator it2 = ch_temp.begin(); it2 != ch_temp.end(); ++it2) {
      apair = *it2;
      //cout << "Before(" << apair.first << "," << apair.second << ") ; "<<"\n";
      
	ch_sort.push_back(apair.first);
	temp_sort.push_back(apair.second);
      
      //i++;
    }
   
    
  cout << "Size "<<temp_sort.size()<<"\n";
    for (int i=0;i<temp_sort.size();++i)
      cout << "Temp "<<i<<" = " << temp_sort[i] << "\n";
    cout<<"Out OK!\n";
    //for (unsigned i=0;i<ch_sort.size();++i)
      // cout << "Final Vector(" << ch_sort[i] << "," << temp_sort[i] << ") ; "<<"\n";
}

