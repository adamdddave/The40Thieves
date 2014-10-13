#ifndef EXTRAGUIQTLIB_H
#define EXTRAGUIQTLIB_H

#include "extraguiqtlib_global.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <thread>
#include <chrono>
//#include <thread>//for running the QApplication in a different thread.
//alibava
#include <Plugin.h>
#include "newPoint.h"
//root
#include <TProfile.h>
#include<TH1.h>
#include <TH2.h>
#include <TCanvas.h>
//Qt
#include <QApplication>
#include "mainwindow.h"
//params
#include "Parameters.h"
using namespace std;
//MainWindow* win;
class EXTRAGUIQTLIBSHARED_EXPORT ExtraGuiQtLib : public Plugin
{
private:
    int npoints;
    int nevt_per_point;
    int run_type;
    int current_event;
    EventCntr handler;
    //my shiz
    double time_min;
    double time_max;
    double min_adc;
    TH2D* HistoToFill;//ADC vs channel
    TProfile* HistoToDisplay;//<adc> vs channel
    TH1F* ClusterHistos[6];//5 cluster monitoring plots, which follow
    TH1F* ClusterSize;
    TH1F* ClusterChargelt10;
    TH1F* ClusterCharge10_20;
    TH1F* ClusterCharge20_30;
    TH1F* ClusterBeamProf;
    TH2F* ClusterChargeVsTDC;
    bool ok_to_do_clustering;
    QApplication *a;
    MainWindow  *win;
    chrono::steady_clock::time_point timeNow, timeRef;//these are reference times for updating the plots
    std::vector<double> local_pedestals;
public:


    //constructor with default vals
    ExtraGuiQtLib() :
        run_type(-1),
        npoints(5),nevt_per_point(1),
        handler(nevt_per_point),
        current_event(0)
    {

        cout<<"Enter a minimum time to display: ";
        cin>>time_min;
        cout<<"Enter a maximum time to display: ";
        cin>>time_max;
        cout<<"Enter a minimum ADC value: ";
        cin>>min_adc;
        cout<<"Entered Time Window:["<<time_min<<","<<time_max<<"], with ADC above "<<min_adc<<" counts."<<endl;

        HistoToFill = new TH2D("StripNumber","ADC By StripNumber; StripNumber; ADC count",256,0,256,100,min_adc,2000);
        HistoToDisplay = (TProfile*)HistoToFill->ProfileX();
        ClusterSize=new TH1F("ClusterSize","ClusterSize;N Clusters;Entries",7,0,7);
        ClusterChargelt10 = new TH1F("ClusterChargelt10","Cluster Charge,t<10",200,0,200);
        ClusterCharge10_20=new TH1F("ClusterCharge10_20","Cluster Charge, 10<t<20",200,0,200);
        ClusterCharge20_30=new TH1F("ClusterCharge20_30","Cluster Charge, 20<t<30",200,0,200);
        ClusterBeamProf = new TH1F("ClusterBeamProf","Cluster Beam Profile",256,0,256);
        ClusterChargeVsTDC = new TH2F("ClusterChargeVsTDC","Cluster Charge vs TDC",200,0,50,100,min_adc,250);//defined in parameters
        local_pedestals.reserve(256);
    }

    ~ExtraGuiQtLib(){
      local_pedestals.clear();
      delete HistoToFill;
      delete HistoToDisplay;
      delete ClusterHistos;
      delete ClusterSize;
      delete ClusterChargelt10;
      delete ClusterCharge10_20;
      delete ClusterCharge20_30;
      delete ClusterBeamProf;
      delete ClusterChargeVsTDC;
      delete win;
      delete a;

    }
    //methods for plugin
    void new_file(string &S);
    int start_of_run(int run_type, int nevents, int sample_size);
    void end_of_run(string &S);
    bool new_event(int evt);
    void new_point(string &S);
    //int filter_event(const EventData *data, string &S);
    int filter_event(const AlibavaData *data, string &S);
    //additional methods for multithreading
    void CallExternalGui();
    void UpdatePlots();
    TH2D* the_plot(){return HistoToFill;};
    double decode_datablock_time(unsigned int time);
};

#endif // EXTRAGUIQTLIB_H
