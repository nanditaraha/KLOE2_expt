#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <TGraph.h>
#include <TGraphErrors.h>
using namespace std;

void gain(int channel=100)
{
  //ifstream file *fp;
  //char * filename = "myfile02.txt";
  int run1=82930, run2=84656, run3=82966, run4=84680;
  const int numL = 1920;
  double first, second, third;

  double temp_pt[3]={0};
  double gain_pt[3]={0};
  double temp_err_pt[3]={0};
  double gain_err_pt[3]={0};
  int data_pt=0;
  double *temp1 = new double[numL];
  double *gain1 = new double[numL];
  double *gain_err1 = new double[numL];
  int *ch1 = new int[numL];
  int *ch_g1 = new int[numL];
  int tot_ch1=0;
  int tot_ch_g1=0;
  
  double *temp2 = new double[numL];
  double *gain2 = new double[numL];
  double *gain_err2 = new double[numL];
  int *ch2 = new int[numL];
  int *ch_g2 = new int[numL];
  int tot_ch2=0;
  int tot_ch_g2=0;
  
  double *temp3 = new double[numL];
  double *gain3 = new double[numL];
  double *gain_err3 = new double[numL];
  int *ch3 = new int[numL];
  int *ch_g3 = new int[numL];
  int tot_ch3=0;
  int tot_ch_g3=0;
  
  double *temp4 = new double[numL];
  double *gain4 = new double[numL];
  double *gain_err4 = new double[numL];
  int *ch_g4 = new int[numL];
  int *ch4 = new int[numL];
  int tot_ch4=0;
  int tot_ch_g4=0;
  //Opening channel vs temp files
  ifstream fileQ1("Qcalt_temp"+to_string(run1)+".dat");
  ifstream fileQ2("Qcalt_temp"+to_string(run2)+".dat");
  ifstream fileQ3("Qcalt_temp"+to_string(run3)+".dat");
  //ifstream fileQ4("Qcalt_temp"+to_string(run4)+".dat");
  //Note all Qcalt files are in the same path as this file i.e. in dat_temp
  //file.open("Qcalt_temp"+to_string(run1)+".dat");

  //Opening channel vs gain files
  ifstream fileG1("../QCALT_HV_calibration_output/calib_"+to_string(run1)+".root.dat");
  ifstream fileG2("../QCALT_HV_calibration_output/calib_"+to_string(run2)+".root.dat");
  ifstream fileG3("../QCALT_HV_calibration_output/calib_"+to_string(run3)+".root.dat");
  //ifstream fileG4("../QCALT_HV_calibration_output/calib_"+to_string(run4)+".root.dat");


  //SAVING temp and channels in arrays
  
  while(!fileQ1.eof()){
    //cout<<"ok\n";
    fileQ1 >> first >> second;
    ch1[tot_ch1]=first;
    temp1[tot_ch1]=second;
      if(ch1[tot_ch1]==channel+1){
          temp_pt[0]=temp1[tot_ch1];
          break;
      }
    tot_ch1++;
  }
    cout<<"OPened temp Q1 "<<temp_pt[0]<<"\n";
    fileQ1.close();
    //int tot_ch2=0;
    tot_ch1=0;
   
    
    while(!fileQ2.eof()){
    //
    fileQ2 >> first >> second;
    ch2[tot_ch1]=first;
    temp2[tot_ch1]=second;
    if(ch2[tot_ch1]==channel+1){
        temp_pt[1]=temp2[tot_ch1];
        break;
        }
    tot_ch1++;
  }
    cout<<"OPened temp Q2 "<<temp_pt[1]<<"\n";
    tot_ch1=0;
    fileQ2.close();
    
    while(!fileQ3.eof()){
      fileQ3 >> first >> second;
      ch3[tot_ch1]=first;
      temp3[tot_ch1]=second;
      if(ch3[tot_ch1]==channel+1){
        temp_pt[2]=temp3[tot_ch1];
        break;
     }
      tot_ch1++;
    }
 cout<<"OPened temp Q3 "<<temp_pt[2]<<"\n";
 fileQ3.close();
 /*
 while(!fileQ4.eof()){
   fileQ4 >> first >> second;
   ch4[tot_ch4]=first;
   temp4[tot_ch4]=second;
   tot_ch4++;
  }
 cout<<"OPened temp Q4 "<<tot_ch4<<"\n";
 fileQ4.close();
 */
 //Saving gains
 
while(!fileG1.eof()){
  //cout<<"OPened gain file\n";
  fileG1 >> first >> second >> third;
  ch_g1[tot_ch_g1]=first;
  gain1[tot_ch_g1]=second;
  gain_err1[tot_ch_g1]=third;
    if(ch_g1[tot_ch_g1]==channel+1){
        gain_pt[0]=gain1[tot_ch_g1];
        gain_err_pt[0]=gain_err1[tot_ch_g1];
        break;
    }
  tot_ch_g1++;
  //cout<<"Channel "<<tot_ch_g1<<"="<<ch_g1[tot_ch_g1]<<"\n";
  }
 cout<<"OPened gain G1 "<<gain_pt[0]<<" "<<gain_err_pt[0]<<"\n";
 fileG1.close();
 
 while(!fileG2.eof()){
   //cout<<"Started";
   fileG2 >> first >> second >> third;
   ch_g2[tot_ch_g2]=first;
   gain2[tot_ch_g2]=second;
   gain_err2[tot_ch_g2]=third;
     
   if(ch_g2[tot_ch_g2]==channel+1){
     gain_pt[1]=gain2[tot_ch_g2];
     gain_err_pt[1]=gain_err2[tot_ch_g2];
     break;
     }
   //cout<<"Got em\n";
   tot_ch_g2++;
 }
 cout<<"OPened temp G2 "<<tot_ch_g2<<"\n";
 fileG2.close();

 while(!fileG3.eof()){
   fileG3 >> first >> second >> third;
   ch_g3[tot_ch_g3]=first;
   gain3[tot_ch_g3]=second;
   gain_err3[tot_ch_g3]=third;
   if(ch_g3[tot_ch_g3]==channel+1){
         gain_pt[2]=gain3[tot_ch_g3];
         gain_err_pt[2]=gain_err3[tot_ch_g3];
         break;
     }
   tot_ch_g3++;
  }
 cout<<"OPened temp G3 "<<tot_ch_g3<<"\n";
 fileG3.close();
 /*
 while(!fileG4.eof()){
   fileG4 >> first >> second >> third;
   ch_g4[tot_ch_g4]=first;
   gain4[tot_ch_g4]=second;
   gain_err4[tot_ch_g4]=third;
   tot_ch_g4++;
  }
 cout<<"OPened temp G1 "<<tot_ch_g4<<"\n";
 fileG4.close();
 
 for(int i=0;i<tot_ch_g1-1;i++){
   cout<<"IN the loop\n";
   cout<<"Channel "<<i<<"="<<gain1[i]<<"\n";
   cout<<"Temp "<<ch1[i]<<"="<<temp1[i]<<"\n";
   // cout<<ch_g1[i]<<", "<< gain1[i]<<", "<<gain_err1[i]<<"\n";
 }
 */
 //for(int i=0;i<numL;i++){
 //if(ch1[i]==channel && ch2[i]==channel && ch3[i]==channel && ch_g1[i]==channel && ch_g2[i]==channel && ch_g3[i]==channel){
    //for(int j=0;j<3;j++){
 //ch1=channel+1;
 //ch_g1=channel+1;
 /*
 temp_pt[0]=temp1[ch1];
 gain_pt[0]=gain1[ch_g1];
 gain_err_pt[0]=gain_err1[ch_g1];

 //ch2=channel+1;
 //ch_g2=channel+1;
 temp_pt[1]=temp2[ch2];
 gain_pt[1]=gain2[ch_g2];
 gain_err_pt[1]=gain_err2[ch_g2];

 //ch3=channel+1;
 //ch_g3=channel+1;
 temp_pt[2]=temp3[ch3];
 gain_pt[2]=gain3[ch_g3];
 gain_err_pt[2]=gain_err3[ch_g3];

 for(int j=0;j<3;j++){
   cout<<"Temp "<< temp_pt[j]<<"\n";
 }
 */
 //}
 //}
 //else cout<<"Channel not found!!\n" ;
 //}
 
 
 TGraphErrors *gr = new TGraphErrors(3,temp_pt,gain_pt,temp_err_pt,gain_err_pt);
 
   gr->SetMarkerColor(4);
   //gr->GetYaxis()->SetRangeUser(0.1,140);
   //gr->GetXaxis()->SetRangeUser(10,50);
   gr->GetXaxis()->SetTitle("Temp ^{#circ}C");
   gr->GetYaxis()->SetTitle("Gain");
   gr->SetMarkerStyle(22);
   gr->Draw("AP");
 
}
