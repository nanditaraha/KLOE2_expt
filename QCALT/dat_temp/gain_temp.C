#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <TGraph.h>
#include <TGraphErrors.h>

using namespace std;

int HV_files(int HV, int *run);
void plot(int start, int end, int HV);
bool gain_temp(int HV=30,int channel=100)
{
  const int all_files=10;
  
  //int run1=82930, run2=84656, run3=82966, run4=84680;//30V
  //int run1=82931, run2=84651, run3=82967, run4=84679;//34V

  int run[all_files]={0};
  int no_files=HV_files(HV,run);
  cout<<no_files<<"\n";
  //int run1=run[0], run2=run[1], run3=run[2], run4=run[3];
  const int numL = 1920;
  double first, second, third;
  bool drawGraph = false;
  
  double temp_pt[all_files]={0};
  double gain_pt[all_files]={0};
  double temp_err_pt[all_files]={0};
  double gain_err_pt[all_files]={0};
  int data_pt=0;
  
  double temp[all_files][numL]={0};
  double gain[all_files][numL]={0};
  double gain_err[all_files][numL]={0};
  int ch[all_files][numL]={0};
  int ch_g[all_files][numL]={0};
  int tot_ch1=0;
  int tot_ch_g1=0;

  for(int i=0;i<no_files; i++){
   cout<< run[i]<<"\n";
  }
  
  for(int i=0;i<no_files; i++){
    ifstream fileQ("Qcalt_temp"+to_string(run[i])+".dat");
    ifstream fileG("../QCALT_HV_calibration_output/calib_"+to_string(run[i])+".root.dat");
    cerr<<"File not found \n";
    while(!fileQ.eof()){
      //cout<<"ok\n";
      fileQ >> first >> second;
      ch[i][tot_ch1]=first;
      temp[i][tot_ch1]=second;
      
      if(ch[i][tot_ch1]==channel+1 && temp[i][tot_ch1]>0){
	temp_pt[i]=temp[i][tot_ch1];
	break;
      }
      tot_ch1++;
    }
    
    while(!fileG.eof()){
      fileG >> first >> second >> third;
      ch_g[i][tot_ch_g1]=first;
      gain[i][tot_ch_g1]=second;
      gain_err[i][tot_ch_g1]=third;
      
      if(ch_g[i][tot_ch_g1]==channel+1  && gain[i][tot_ch_g1]>0){
	gain_pt[i]=gain[i][tot_ch_g1];
	gain_err_pt[i]=gain_err[i][tot_ch_g1];
	break;
     }
      
      tot_ch_g1++;
    }
    
 }
  /*
  if(HV==34){
    for(int i=0;i<no_files-1;i++){
      //NOTE: no_files-1 is wrong but I have all zero entries for my last file so its a way to ignore last file for 34 V
    if(gain_pt[i]>0) drawGraph=true;
    
    }
    }*/
  //else {
    for(int i=0;i<no_files;i++){
      if(gain_pt[i]>0) drawGraph=true;
    
    }
    //}
  
  
  for(int i=0;i<no_files;i++){
    cout<<"OPened temp Q "<<temp_pt[i]<<"\n";
    cout<<"OPened gain G "<<gain_pt[i]<<" "<<gain_err_pt[i]<<"\n";
  }
  
  TGraphErrors *gr = new TGraphErrors(no_files,temp_pt,gain_pt,temp_err_pt,gain_err_pt);
  
  gr->SetMarkerColor(4);
  //gr->GetYaxis()->SetRangeUser(0.1,140);
  //gr->GetXaxis()->SetRangeUser(10,50);
  gr->GetXaxis()->SetTitle("Temp ^{#circ}C");
  gr->GetYaxis()->SetRange(30,60);
  gr->GetYaxis()->SetTitle("Gain");
  gr->SetMarkerStyle(22);
  if(drawGraph)
    gr->Draw("AP");
  else cout<<"Invalid gain values!!!\n";
  return drawGraph;
  

}


int HV_files(int HV, int *run){
    double first, second;
    const int files=10;
    ifstream fileHV("HV.dat");
    //int *run_no = new int[files];
    int *hv = new int[files];
    int no = 0;
    while(!fileHV.eof()){
        fileHV >> first >> second;
        //run_no[no]=first;
	//hv[no]=second;
        if(second==HV){
	  run[no]=first;
	  hv[no]=second;
	  no++;
	  
	}
    }
    
    for(int i=0;i<no;i++) cout<<run[i]<<" , "<<hv[i]<<"\n";
    return no;
}

void plot(int start=81, int end=1841, int HV=34)
{
 TCanvas *c1= new TCanvas("c1","Plots of Temp Vs. gain",1000,1000);
 //c1->Divide(10,10);

 c1->Print("g1.pdf[");
 for(int i=start;i<end;i++)
   {
     //c1->cd(i+1);
     gain_temp(HV,i);
     gPad->SetGridy();
     if(gain_temp(HV,i))
       c1->Print("g1.pdf");
   }
 c1->Print("g1.pdf]"); 
 
}
