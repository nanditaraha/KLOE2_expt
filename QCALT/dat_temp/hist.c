
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

void hist(int run){
  
  FILE *fp, *fp1;
  const int numL = 1920;
  float ch1[numL];
  float gain1[numL];
  float gain_err1[numL];
  float ch2[numL];
  float gain[numL];
  float gain_err[numL];
  
  TH2F *hGain_temp;
  
  vector <int> ch(numL, 0);
  vector <float> temp(numL, 0);
  vector <int> ch_sort;
  vector <float> temp_sort;
  float temp_err[numL]={0};
  pair <int,float> apair;
  vector< pair<int,float>  > ch_temp;
  char filename1[30];
  char filename[50];
  
  int index = 0;
  sprintf(filename, "calib_%d.root.dat",run);
  fp1 = fopen(filename,"r");  
  for(int i=0;i<numL;i++){ 
    fscanf(fp1,"%f %f %f",&ch1[i],&gain1[i],&gain_err1[i]);
  }
 
  sprintf(filename1, "Qcalt_temp%d.dat",run);
  fp = fopen(filename1,"r");

  for(int i=0;i<numL;i++)
    fscanf(fp,"%d %f",&ch[i],&temp[i]);
  
  for(int j=0;j<ch.size();j++)
    {
      //printf("hkfhkfhkf\n");
      if(temp[j]>0){
	apair=make_pair(ch[j],temp[j]);
	ch_temp.push_back(apair);
	}
    }
  
  sort(ch_temp.begin(), ch_temp.end());  
  
  for (vector<pair<int,float> >::iterator it2 = ch_temp.begin(); it2 != ch_temp.end(); ++it2) {
    apair = *it2;
    //cout << "Before(" << apair.first << "," << apair.second << ") ; "<<"\n";
    
    ch_sort.push_back(apair.first);
    temp_sort.push_back(apair.second);
    //cout << "After(" << ch_sort[6] << "," << temp_sort[6] << ") ; "<<"\n";
  }


  
  //for(unsigned i=0;i<ch_sort.size();i++)
  for(int i=0;i<ch_sort.size();i++)
    {//cout<<"ch1[i] "<< ch1[i]<< " ch_sort[i] " <<ch_sort[i]<<"\n";
      for(int j=0;j<ch_sort.size();j++)
      if(ch1[i]==ch_sort[j]) {
	//printf("IFFF: hkfhkfhkf\n");
	gain[index] = gain1[ch_sort[i]];
	gain_err[index] = gain_err1[ch_sort[i]];
	ch2[index] = ch_sort[j];
	index++;
	//cout<<"ch1[i] "<< ch1[i]<< " ch_sort[i] " <<ch_sort[i]<<"\n";
      }
     
    }
  
  //for(int i=0;i<ch_sort.size();i++)
  //cout<<"ch2[i] "<< ch2[i]<< " ch_sort[i] " <<ch_sort[i]<<" gain "<<gain[i]<<"\n";
  
  
  
  //for(unsigned i=0;i<index;i++)
  //cout << "Gain i " <<i<<"=" <<gain[i] << " Ch "<< ch_sort[i]<<" Temp " << temp_sort[i]<<"\n";
  
  
 
  //cout << "Size "<<ch_sort.size()<<"\n";
  //for (int i=0;i<ch_sort.size();++i)
    //cout << "Ch "<<i<<" = " << ch_sort[i] << "\n";
  
  
  
  TGraphErrors *gr = new TGraphErrors(temp_sort.size(), &temp_sort[0], gain, temp_err, gain_err);
  
  gr->SetMarkerColor(4);
  gr->GetYaxis()->SetRangeUser(0.1,140);
  gr->GetXaxis()->SetRangeUser(10,50);
  gr->GetXaxis()->SetTitle("Temp ^{#circ}C");
  gr->GetYaxis()->SetTitle("Gain");
  gr->SetMarkerStyle(22);

  
  
  gr->Draw("AP");
 
}

