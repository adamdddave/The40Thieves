#include "FastClustering.h"
#include <vector>
#include <iostream>//debugging. comment out when we are done.
#include <cmath>
//#include "TH1.h"
//#include "TCanvas.h"
#include "Parameters.h"

FastClustering::FastClustering( std::vector<unsigned short> &adc,std::vector<double> & pedestal){
    //std::cout<<"testing fast cluster, adc.at(0)="<< adc.at(0)<<std::endl;
    theped.reserve(256);
  subtr_adc.reserve(256);
  nCluster=0;
  set_pedestal(pedestal);
  /*std::cout<<"pedestal[0]="<<pedestal[0]<<std::endl;
  std::cout<<"theped[0]="<<theped[0]<<std::endl;
  std::cout<<"theped.size() = "<<theped.size()<<std::endl;
  std::cout<<theped.empty()<<std::endl;*/
  //if(ped.size()>0){set_pedestal(ped);}
  //std::cout<<"theped[0]="<<theped[0]<<std::endl;

  the_common_mode_b1 = 0;the_common_mode_b2=0;

  getCMN(adc);
  //  std::cout<<"testing after getCMN, the_common_mode_b1="<<the_common_mode_b1<<", the_common_mode_b2 = "<<the_common_mode_b2<<std::endl;
  subtracted=false;
  subtract_all(adc);
  //std::cout<<"subtr_adc[1]  = "<<subtr_adc[1]<<std::endl;
  //std::cout<<"subtr_adc[200]= "<<subtr_adc[200]<<std::endl;
  /*  TH1D* test2 = new TH1D("test2","test_after_subtraction",256,-0.5,255.5);
  test2->GetYaxis()->SetRangeUser(-1,70);
  for(int i=0; i<256;++i){test2->SetBinContent(i+1,subtr_adc[i]);}
  TCanvas*cc = new TCanvas();
  test2->Draw();
  cc->SaveAs("temp2.png");*/

  getSignal();
  //std::cout<<"after get signal, nCluster = "<<nCluster<<std::endl;
}

void FastClustering::set_pedestal(std::vector<double> &ped){
    theped.reserve(256);
    for(int i=0; i<256;++i){
        theped[i]=ped[i];
    }
    return;
}
void FastClustering::subtract_all(std::vector<unsigned short> adc){
  //  std::cout<<"subtracted = "<<subtracted<<std::endl;
  if(subtracted){return;}

  //std::cout<<"now subtracting"<<std::endl;
  //for each adc, subtract the pedestal, noise and common mode;
  for(int i=0; i<128;++i){//beetle 1
    //std::cout<<"the answer ["<<i<<"] =  "<<adc[i]<<" - "<< theped[i]<<" - "<<the_common_mode_b1<<"="
    //     <<adc[i]-theped[i]-the_common_mode_b1<<std::endl;
    subtr_adc[i]=(double)(adc[i]-theped[i]-the_common_mode_b1);
  }
  for(int i=128;i<256;++i){//beetle 2
  //  std::cout<<"the answer ["<<i<<"] =  "<<adc[i]<<" - "<< theped[i]<<" - "<<the_common_mode_b2<<"="
  //       <<adc[i]-theped[i]-the_common_mode_b2<<std::endl;
    subtr_adc[i]=(double)(adc[i]-theped[i]-the_common_mode_b2);
  }
  subtracted=true;
  return;
}


void FastClustering::cleanup(){
  theped.clear();
  //thenoise.clear();
  subtr_adc.clear();
  subtracted=false;
  the_common_mode_b1=0;
  the_common_mode_b2=0;
  clusterSize.clear();
  clusterCharge.clear();
  clusterPosY.clear();
}


std::vector<double> FastClustering::getSignal(){
  //stolen from Compute CMN. Updated a bit to be faster, though \smiley
  /*  double signal0[256];
  double signal1[256];
  double signal2[256];
  double finalSignal[256];*/
  std::vector<double> signal0;signal0.reserve(256);
  std::vector<double> signal1;signal1.reserve(256);
  std::vector<double> signal2;signal2.reserve(256);
  std::vector<double> finalSignal;finalSignal.reserve(256);
  float nchan[2] = {0, 0};
  std::vector<double> ret; // This is the return vector.
  // Copy ADC values to local array
  //std::cout<<"in getSignal"<<std::endl;
  for (int jChannel=0; jChannel<256; ++jChannel){
    //std::cout<<"jChannel = "<<jChannel<<std::endl;
    double val = subtr_adc[jChannel];
    //std::cout<<"val = "<<val<<std::endl;
    signal0[jChannel] = val;
  }
  //is this necessary?
  double ave[2] = {0.0, 0.0};
  //-------------------------------------------------------------------
  // First iteration - account for a baseline shift across entire chip
  //-------------------------------------------------------------------
  for( int kChannel=0; kChannel<256; kChannel++ ){
    if(kChannel<firstChannel && fabs(signal0[kChannel])<60) { 
      ave[0] = ave[0] + signal0[kChannel];//average for first 128 channels
      nchan[0]++;
    }    
    if(kChannel>=firstChannel  && fabs(signal0[kChannel])<60) {
      ave[1] = ave[1] + signal0[kChannel];//average for second 128 channels
      nchan[1]++;
    }
  } 
  ave[0] = ave[0]/nchan[0];
  ave[1] = ave[1]/nchan[1];
  
  for(int kChannel=0;kChannel<256;kChannel++){
    if( kChannel<firstChannel  )  signal0[kChannel] = signal0[kChannel] - ave[0];
    if( kChannel>=firstChannel )  signal0[kChannel] = signal0[kChannel] - ave[1];
  }
  //----------------------------------------
  // Second iteration - cleaning of outliers
  //----------------------------------------
  ave[0]=0; ave[1]=0; nchan[0] = 0; nchan[1] = 0;
  for( int kChannel=0; kChannel<256; kChannel++ ){
    if( kChannel<firstChannel && fabs(signal0[kChannel] ) < maxADC_Pass1) {
      ave[0] = ave[0] + signal0[kChannel];
      nchan[0]++;
    }
    if( kChannel>=firstChannel  && fabs(signal0[kChannel]) < maxADC_Pass1 ){
      ave[1] = ave[1] + signal0[kChannel];
      nchan[1]++;
    } 
  }
  ave[0] = ave[0] / nchan[0];
  ave[1] = ave[1] / nchan[1];
  for(int kChannel=0;kChannel<256;kChannel++){
    if( kChannel <  firstChannel )  signal1[kChannel] = signal0[kChannel] - ave[0];
    if( kChannel >= firstChannel )  signal1[kChannel] =signal0[kChannel] - ave[1];
  }
  //-------------------------------
  // Remove steps (coherent noise)
  //-------------------------------
  // Look for "steps"
  int kmin;
  int kmax;
  int k = 0;
  while ( k<256 ){
    kmin = k;
    kmax = k+1;
    int nbreak = 0;
    int nbreak2 = 0;
    int nbreakTot = 0;
    float sum = signal1[k];
    if( signal1[k]>minH && signal1[k]<maxH ){
      int maxStrip = kmin + 15;
      if( maxStrip>256 ) maxStrip = 256;
      for( int j = kmin+1;j<maxStrip;j++ ){
        if( (signal1[j]>minH && signal1[j]<maxH) || fabs(signal1[j]-signal1[k])<maxDH ) {        
          sum = sum + signal1[j];
          kmax = j + 1;
          //nbreak = 0;
        }else if(signal1[j]>maxH){
          // posibly a signal here, allow for 2 strips above 20 ADC, but don't count them
          nbreak2++;          
          if(nbreak2>2) break;
          nbreakTot++;          
        }else{
          nbreak++;
          if(nbreak>1) break;
          nbreakTot++;          
          //sum = sum + signal1[j];
          //kmax = j;
        }   
      } 
    }
    int clusSize = kmax - kmin - nbreakTot + 1;
    sum = sum/clusSize;
    if( clusSize >= minSizeStep ){
      //std::cout << "Found step: " << kmin << "  " << kmax << "  " << sum << std::endl;
      for( int j = kmin; j<=kmax; j++ ){signal1[j] = signal1[j] - sum;}      
    }  
    k = kmax;
  }
  //-----------------
  // Second iteration
  //-----------------
  ave[0]=0; ave[1]=0; nchan[0] = 0; nchan[1] = 0;
  for( int k=0; k<256; k++){
    if( k<128 && fabs(signal1[k])<maxADC_Pass2 ) {
      ave[0] = ave[0] + signal1[k];
      nchan[0]++;
    }
    if( k>=128  && fabs(signal1[k])<maxADC_Pass2 ){
      ave[1] = ave[1] + signal1[k];
      nchan[1]++;
    } 
  }
  ave[0] = ave[0]/nchan[0];
  ave[1] = ave[1]/nchan[1];
  for( int k=0; k<256; k++ ){
    if( k <  firstChannel )  signal2[k] = signal1[k] - ave[0];
    if( k >= firstChannel )  signal2[k] = signal1[k] - ave[1];
  }
  // Finish pass
  if(debug>3){
    std::cout << "---------------------------------------------" << std::endl;  
    std::cout << "Final Average = " << ave[0] << "   " << ave[1] << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
  }
  // -----------------
  // -  Final result -
  // -----------------
  //  adc.clear();
  //--------------------------------------------------------------------------------------------
  // Special treatment of pathological events, generally a super-high #counts over a few channels
  //--------------------------------------------------------------------------------------------
  nchan[0] = 0; nchan[1] = 0;
  for( int k=0; k<256; k++ ){
    if( fabs(signal2[k] )<9 && k<firstChannel  ) nchan[0]++;
    if( fabs(signal2[k] )<9 && k>=firstChannel ) nchan[1]++;
  }
  if(nchan[0]<minChannelInWindow){
    ave[1]=0; nchan[1] = 0;
    std::cout << "Yikes, Chip 1 has pathological behavior, will try and correct it" << std::endl;
    for( int k=0; k<128; k++ ){
      if( signal2[k]>largePulseSize ) continue;
      ave[0] = ave[0] + signal2[k];
      nchan[0]++;
    }
    ave[0] = ave[0] / nchan[0];
    for( int k=0; k<128; k++ ){signal2[k] = signal2[k] - ave[0];}
  }
  if(nchan[1]<minChannelInWindow){
    ave[1]=0; nchan[1] = 0;
    std::cout << "Yikes, Chip 2 has pathological behavior, will try and correct it" << std::endl;
    for( int k=firstChannel; k<256; k++ ){
      if( signal2[k]>largePulseSize ) continue;
      ave[1] = ave[1] + signal2[k];
      nchan[1]++;
    }
    ave[1] = ave[1] / nchan[1];
    for( int k=firstChannel; k<256; k++ ){signal2[k] = signal2[k] - ave[1];}
  }
  
  for( int k=0; k<256; k++ ){
    ret.push_back( signal2[k] );
    finalSignal[k] = signal2[k];
  }
  //-------------------------
  // Look for signal clusters
  //-------------------------
  //int nCluster = 0;
  int kMIN;
  int kMAX;
  int ik = 0;
  while (ik < 256){
    if(finalSignal[ik] < minSeed-0.5){
      ik++;
      continue;
    }
    // Have a seed strip, look for neighbors
    float sum = 0;
    int minStrip = ik;
    int maxStrip = ik + 2;
    if(maxStrip>256) maxStrip = 256;
    if(minStrip<0) minStrip = 0;
    kMIN = 0;
    kMAX = ik;
    for(int j = minStrip;j<=maxStrip;j++){
      if(finalSignal[j] < minSide) break;
      sum = sum + finalSignal[j];
      kMAX = j;
      if(kMIN == 0) kMIN = j;
    }    
    minStrip = ik - 2;
    maxStrip = ik - 1 ;
    if(maxStrip>256) maxStrip = 256;    
    if(minStrip<0) minStrip = 0;
    for(int j = maxStrip;j>=minStrip;j--)
    {      
      if(finalSignal[j] < minSide) break;
      sum = sum + finalSignal[j];
      if(kMIN == 0 || j<kMIN) kMIN = j;
    }

    float num = 0, den = 0;
    for(int kk=kMIN; kk<=kMAX; kk++)
    {
      float rkk = kk;
      num = num + rkk*finalSignal[kk];
      den = den + finalSignal[kk];
    }
    float pos = num/den;
    int clusSize = kMAX - kMIN + 1;
    clusterSize.push_back(clusSize);
    clusterCharge.push_back(sum);
    clusterPosY.push_back(pos);
    //clusterCharge[nCluster] = sum;
    //seedChannel[nCluster] = pos;//(kMIN+kMAX)/2.0;
    //clusterSize[nCluster] = clusSize;
    nCluster++;
    //std::cout<<"check in fast clustering, nCluster ="<<nCluster<<std::endl;
    if(debug > 5){
    for(int k=0;k<nCluster;k++){
      std::cout << "  Cluster " << k << " Charge = " 
		<< sum << " Pos = "<< pos 
		<< " Size = " << clusSize << std::endl;
    }
    }
    if( kMAX+3 >= 256) break;
    ik = kMAX + 3; // Move 3 strips away from peak
  }
  
  if(nCluster>0 && debug>5) std::cout << "Found " << nCluster << " clusters" << std::endl;
  return ret;
}

void FastClustering::getCMN(std::vector<unsigned short> adc){
  //From Federica:CMN is the mean (over channels) 
  //of the pedestal subtracted ADC counts and is calculated event by event.
  for(unsigned int i=0;i<adc.size();++i){//loop over channels
    if(i<firstChannel){the_common_mode_b1+=(adc[i]-theped[i]);}
    else{the_common_mode_b2+=(adc[i]-theped[i]);}
  }
  the_common_mode_b1/=(adc.size()/2.);
  the_common_mode_b2/=(adc.size()/2.);
  return;
}
