//header
#include "ExtraGuiQtLib.h"
//c++
#include <iostream>
#include <sstream>
#include <thread>
#include <ctime>
//alibava
#include <Plugin.h>
#include "newPoint.h"
//root
#include <TProfile.h>
#include <TH2.h>
#include <TCanvas.h>
//Qt
#include "mainwindow.h"
#include <QApplication>
//Clustering
#include "FastClustering.h"

using namespace std;

void ExtraGuiQtLib::new_file(string &rc){
    rc = "NewFile";
    cout<<"Starting the plugin for the new gui"<<endl;
}

int ExtraGuiQtLib::start_of_run(int runtype, int nevents, int sample_size){
    run_type = runtype;
    HistoToFill->Reset();
    HistoToDisplay->Reset();
    ClusterSize->Reset();
    ClusterChargelt10->Reset();
    ClusterCharge10_20->Reset();
    ClusterCharge20_30->Reset();
    cout<<"Start of run"<<endl;
    cout<<"Initializing Histograms"<<endl;
    //reset the plots automatically
    win->ClearForNewRun();
    if(sample_size > handler.value()){
        handler.value(sample_size);
        nevt_per_point = sample_size;
    }
    handler.reset();
    //update plots with a timer now.
    cout<<"setting time ref"<<endl;
    timeRef = chrono::steady_clock::now();

    return nevents;//fix for Paolo's problem with plugin resetting the run length
}

void ExtraGuiQtLib::end_of_run(string &rc){
    rc="end_of_run";
    HistoToDisplay = HistoToFill->ProfileX();
    UpdatePlots();
    ok_to_do_clustering=false;//reset the clustering flag.
    //save shit if you want...
/*
    TCanvas * cc = new TCanvas();
    HistoToFill->Draw("colz");
    cc->SaveAs("~/Documents/ExtraGuiQtLib/temp2d.png");
    cc->Clear();
    HistoToDisplay->Draw();
    cc->SaveAs("~/Documents/ExtraGuiQtLib/temp.png");
    delete cc;*/
    std::cout<<"finishing run"<<std::endl;

}

bool ExtraGuiQtLib::new_event(int ievt){
    //std::cout<<"new event"<<std::endl;
    current_event=ievt;
    return false;
}

void ExtraGuiQtLib::new_point(string &rc){
    ostringstream ostr;
    ostr<< "new point: " << current_event<<endl;
    cout<<ostr.str();
    rc = ostr.str();
}

//int ExtraGuiQtLib::filter_event(const EventData *data, string &S){
int ExtraGuiQtLib::filter_event(const AlibavaData *data, string &S){
    std::vector<unsigned short> adcs_local(256);adcs_local.reserve(256);
    //check the firmware verision first.
    //std::cout<<"Firmware = "<< data->firmware()<<std::endl;
    double time2comp;
    if(data->firmware()==3){time2comp=data->time();}
    else{time2comp = decode_datablock_time(data->time());}//decode the time into ns
    //std::cout<<"time2comp="<<time2comp<<std::endl;
      for(int j_chip=0; j_chip<2;++j_chip){
        for(int i_channel=0; i_channel<128;++i_channel){
          if(data->get_block()->chip[j_chip].signal[i_channel]<min_adc)continue;
          if(time2comp<time_min || time2comp>time_max)continue;
          HistoToFill->Fill(128*j_chip+i_channel,data->get_block()->chip[j_chip].signal[i_channel]);
          adcs_local[128*j_chip+i_channel]=data->get_block()->chip[j_chip].signal[i_channel];
        }
      }

    if(ok_to_do_clustering){
        //int elem=(int)(*std::max_element(adcs_local.begin(),adcs_local.end()));
        if(time2comp>=time_min &&time2comp<=time_max && adcs_local[0]>0.){

            //last case senario. if we don't have pedestals locally, make them ourselves
            if(local_pedestals[0]==0){
                HistoToDisplay = HistoToFill->ProfileX();
                for(int i=0;i<256;++i){
                    local_pedestals[i]=HistoToDisplay->GetBinContent(i+1);
                }
            }
            FastClustering a(adcs_local,local_pedestals);
            //std::cout<<"Checking cluster. ncluster="<<a.getNcluster()<<std::endl;
            if(!a.getNcluster()==0){
                for(int nclus=0; nclus<a.getNcluster();++nclus){
                    ClusterSize->Fill(a.get_cluster_size(nclus));
                    if(time2comp<10)ClusterChargelt10->Fill(a.get_cluster_charge(nclus));
                    if(time2comp>=10 && time2comp<20)ClusterCharge10_20->Fill(a.get_cluster_charge(nclus));
                    if(time2comp>=20 && time2comp<30)ClusterCharge20_30->Fill(a.get_cluster_charge(nclus));
                }

            }
        }
    }



        adcs_local.clear();
      //update plots every 5 seconds
      //set a timer
      timeNow = chrono::steady_clock::now();
      //cout<<"difference between ref and now = "<<chrono::duration_cast<chrono::seconds>(timeNow-timeRef).count()<<endl;
      if(5.<=chrono::duration_cast<chrono::seconds>(timeNow-timeRef).count()){
        //cout<<"greater than 5 seconds, resetting!"<<endl;
        UpdatePlots();
        win->get_pedestals(local_pedestals);
       // std::cout<<"local_pedestals[0] ="<<local_pedestals[0]<<std::endl;
        timeRef = chrono::steady_clock::now();
        if(!ok_to_do_clustering){
            ok_to_do_clustering=true;
            std::cout<<"ok to do clustering now"<<std::endl;
        }

        //take steve's idea and wait till after the first iteration to do the
        // clustering.
      }

      return 0;
}


void ExtraGuiQtLib::CallExternalGui(){
    int dummy_argc = 1;
    char** dummy_argv=NULL;
    a = new QApplication(dummy_argc,dummy_argv);//must call QApplication first
    if(HistoToFill){
      //ClusterHistos[0]=ClusterSize;
      win = new MainWindow(HistoToFill);
    }
    else{
      win = new MainWindow;
    }
    win->show();
}

void ExtraGuiQtLib::UpdatePlots(){
    std::cout<<"Updating Plots"<<std::endl;
    //win->test_signal(1);
    win->UpdatePlots(HistoToFill);
    if(ok_to_do_clustering){
        ClusterHistos[0]=ClusterSize;
        ClusterHistos[1]=ClusterChargelt10;
        ClusterHistos[2]=ClusterCharge10_20;
        ClusterHistos[3]=ClusterCharge20_30;
        win->UpdateCluster(ClusterHistos);
    }
}
double ExtraGuiQtLib::decode_datablock_time(unsigned int time){
    //from Asciiroot and alibava gui, decode the time into ns
    unsigned short fpart= time & 0xffff;
    short ipart=(time & 0xffff0000)>>16;
    if(ipart<0) fpart*=-1;
    double ret=100.*(ipart+(fpart/65335.));
    return ret;
}

/*
 * This is the factory function or "hook" in terms of the
 * Plugin dialog box where the instance of you Plugin
 * implementation is created.
 */
extern "C"
{
  Plugin *create_plugin()
  {
    ExtraGuiQtLib *plugin = new ExtraGuiQtLib();
    plugin->CallExternalGui();
    return plugin;
  }
}
