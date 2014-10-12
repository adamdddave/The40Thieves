//************************************************
// Author: Adam Davis
// Created on: 09/23/2014
//************************************************

//Fast clustering algorithm for online presentation
//Based on ComputeCMN clustering.

//To be verbose about the idea, we want to first run pedestal
//subtraction, common mode, etc, then run the clustering. 
//That's why we have all of the arguments for the constructor.
//Need to test if it is faster to modify the vector itself or to modify a new vector.

#ifndef FASTCLUSTERING_H
#define FASTCLUSTERING_H

#include <vector>


class FastClustering {
public:
  FastClustering( std::vector<unsigned short> &adc,std::vector<double> &pedestal);
  virtual ~FastClustering(){}
  void set_pedestal(std::vector<double> &ped);
  //  void set_noise(std::vector<double> noise){thenoise=noise;}
  void subtract_all(std::vector<unsigned short> adcs);
  int get_cluster_size(int clus_int){return clusterSize.at(clus_int);}//these are wrong, but need to check
  float get_cluster_charge(int clus_int){return clusterCharge.at(clus_int);}//these are wrong, but need to check
  float get_cluster_pos(int clus_int){return clusterPosY.at(clus_int);}
  int getNcluster(){return nCluster;}
  void cleanup();
 private:
  void getCMN(std::vector<unsigned short> adc);//fill cmn1 and cmn2
  std::vector<double> getSignal();

  std::vector<double>theped;
  //std::vector<double>thenoise;
  double the_common_mode_b1;
  double the_common_mode_b2;
  std::vector<double>subtr_adc;//what we get after subtraction
  bool subtracted;

  int nCluster;
  std::vector<int> clusterSize;
  std::vector<float> clusterCharge;
  std::vector<float> clusterPosY;//from original clustering.

};

#endif

