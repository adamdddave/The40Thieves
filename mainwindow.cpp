#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <qcustomplot.h>
#include <iostream>
#include <TH2.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TFormula.h>
#include <cmath>
//helpers
#include "RootHelpers.h"

MainWindow::MainWindow(TH2D* plot_to_hack, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    local_peds.reserve(256);
    std::cout<<"local_peds.size()="<<local_peds.size()<<std::endl;
    if(plot_to_hack){
        AdamHacksetupColorMap(ui, plot_to_hack);
    }
    else{
        AdamHacksetupColorMap(ui);
    }

    //connect(&dataTimer,SIGNAL(timeout()), this, SLOT(UpdateViewerSlot(TH2D*)));

    connect( this, SIGNAL(UpdatePlots(TH2D*)), this, SLOT(UpdateViewerSlot(TH2D*)));
    connect( this,SIGNAL(test_signal(int)),this,SLOT(test_slot(int)) );
    connect( this, SIGNAL(UpdateCluster(TH1F**,TH2F*)), this, SLOT(UpdateClusterSlot(TH1F**,TH2F*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AdamHacksetupColorMap(Ui::MainWindow* ui, TH2D* plot_to_hack){
    QCustomPlot* customPlot = ui->customPlot;//adc vs channel
    QCustomPlot *customPlot2 = ui->customPlot2;//<adc> vs channel
    customPlot2->setNoAntialiasingOnDrag(true);//added response
    QString demoName = "Adam's hack of Color Map Demo";
  if(plot_to_hack == 0){
    //fake some data
    TFormula * eq = new TFormula("eq","TMath::Abs(cos(x)+sin(y))");
    plot_to_hack = Fake2dHisto(eq);
  }
  
  TProfile *prof = plot_to_hack->ProfileX("prof");
  //these are the pedestals, push them back!
  for(unsigned int i=0;i<256;++i){
      local_peds[i]=prof->GetBinContent(i+1);
  }
  // TCanvas *can = new TCanvas();
  // prof->Draw();
  // can->SaveAs("temp.png");
  // can->Clear();
  // plot_to_hack->Draw("colz");
  // can->SaveAs("temp2.png");
  //double check that we get the right shiz
  //we have the tprofile, now we make the graph
  //this is for the th2
  customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
  customPlot->axisRect()->setupFullAxesBox(true);
  customPlot->xAxis->setLabel(plot_to_hack->GetXaxis()->GetTitle());
  customPlot->yAxis->setLabel(plot_to_hack->GetYaxis()->GetTitle());
  // set up the QCPColorMap:
  //let's try the root helpers

  QCPColorMap* colorMap = /*RootHelpers::*/RootHelpers::ConvertTH2(plot_to_hack,customPlot->xAxis,customPlot->yAxis);
  customPlot->addPlottable(colorMap);
  //make it a binned plot as opposed to an interpolated one
  colorMap->setInterpolate(false);

  // add a color scale:
  QCPColorScale *colorScale = new QCPColorScale(customPlot);
  if(!customPlot->plotLayout()->hasElement(0,1)){
    customPlot->plotLayout()->addElement(0, 1, colorScale);
  } // add it to the right of the main axis rect
  colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
  colorMap->setColorScale(colorScale); // associate the color map with the color scale
  /*colorScale->axis()->setLabel(plot_to_hack->GetTitle());
  colorScale->axis()->setScaleLogBase(100);
  colorScale->axis()->setNumberFormat("eb");
  colorScale->axis()->setNumberPrecision(0);
  colorScale->axis()->setRange(1e-2,1e4);*/
  // set the color gradient of the color map to one of the presets:
  colorMap->setGradient(QCPColorGradient::gpPolar);

  // we could have also created a QCPColorGradient instance and added own colors to
  // the gradient, see the documentation of QCPColorGradient for what's possible.
  
  // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
  colorMap->rescaleDataRange();
  colorScale->rescaleDataRange(true);
  // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
  QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
  customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
  colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

  // rescale the key (x) and value (y) axes so the whole color map is visible:

  customPlot->axisRect()->setupFullAxesBox();
  customPlot->rescaleAxes();

  //2d plot is drawn, now let's get the profile
  QCPGraph *graph1 = customPlot2->addGraph();

  RootHelpers::ConvertProfile(prof, *graph1);
  customPlot2->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
  customPlot2->axisRect()->setupFullAxesBox();
  customPlot2->graph()->setScatterStyle(QCPScatterStyle::ssCross);

  graph1->setPen(QPen(QColor(120, 120, 120), 2));
  customPlot2->rescaleAxes();


  //now that we have the first two plots set, we can use the profile as the pedestal per channel.
  //In order to keep the GUI fast, keep computation to a minimum, hence pass only plots here.


}

void MainWindow::on_pushButton_clicked()
{
    close();
}


TH2D *MainWindow::Fake2dHisto(TFormula* eq){
  QString demoName = "Adam's hack of Color Map Demo";
  TH2D* plot_to_hack = new TH2D("plot_to_hack","plot_to_hack;Xhack;Yhack",200,-4,4,200,-4,4);
  //double x, y, z;
  double bin_width = 200;
  for(int iloop=0;iloop<200;++iloop){
    for(int jloop=0;jloop<200;++jloop){
      //set up my own function. Exponential on the y axis, sin on the x
      Double_t x_pos = -4+(8./bin_width*iloop);
      Double_t y_pos = -4+(8./bin_width*jloop);
      double z_hack = eq->Eval(x_pos,y_pos);
      //double z_hack = fabs(cos(x_pos)+sin(y_pos));
      plot_to_hack->SetBinContent(iloop,jloop,z_hack);
    }
  }

  return plot_to_hack;
}

void MainWindow::UpdateViewerSlot(TH2D* plot){
    //std::cout<<"called slot"<<std::endl;
    QCPColorMap* cm_dum = RootHelpers::ConvertTH2(plot,ui->customPlot->xAxis,ui->customPlot->yAxis);
    //remove plottable
    ui->customPlot->removePlottable(0);
    //add new plottable
    ui->customPlot->addPlottable(cm_dum);
    //profile histo
    TProfile * dum = (TProfile*)plot->ProfileX("dum");
    //update pedestals
    for(int i=0; i<256;++i){
        local_peds[i]=dum->GetBinContent(i+1);
        //std::cout<<"local_peds[i] ="<<local_peds[i]<<std::endl;
    }

    std::vector<QVector<double>> vals = RootHelpers::DataFromProf(dum);
    ui->customPlot2->graph(0)->setData(vals[0],vals[2]);
    ui->customPlot2->rescaleAxes();
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
    ui->customPlot2->replot();
    vals.clear();
    //return;
}


void MainWindow::test_slot(int i){
    std::cout<<"changing i! changed to"<<i<<std::endl;
}

void MainWindow::on_pushButton_2_clicked()
{
    //clear all the plots.
    ui->customPlot->removePlottable(0);
    ui->customPlot2->removeGraph(0);
    TH2D* dum = new TH2D("StripNumberDummy","ADC By StripNumber; StripNumber; ADC count",256,0,256,100,0,2000);
    AdamHacksetupColorMap(/*(ui->customPlot,ui->customPlot2,*/ ui,dum);
    ui->customPlot3->removePlottable(0);
    ui->customPlot4->removePlottable(0);
    ui->customPlot5->removePlottable(0);
    ui->customPlot6->removePlottable(0);
    ui->customPlot7->removePlottable(0);
    ui->customPlot8->removePlottable(0);
    ui->customPlot->replot();
    ui->customPlot2->replot();
    ui->customPlot3->replot();
    ui->customPlot4->replot();
    ui->customPlot5->replot();
    ui->customPlot6->replot();
    ui->customPlot7->replot();
    ui->customPlot8->replot();
    delete dum;
}

void MainWindow::ClearForNewRun(){
  this->on_pushButton_2_clicked();
}

void MainWindow::get_pedestals(std::vector<double>& ret){
    //std::cout<<"getting pedestals from the main window"<<std::endl;
    for(int i=0;i<256;++i){
        ret[i]=local_peds[i];
    }
    return;
}

void MainWindow::AdamHackClusterPlots(Ui::MainWindow *ui, TH1F** plots,TH2F* plot2){
    //code to hack all the cluster plots from an array of TH1Fs
    //array is
    if(!plots){return;}
    QCustomPlot *clusSize = ui->customPlot3;//cluster size
    QCustomPlot *clusChargelt10 = ui->customPlot4;//cluster charge, t<10
    QCustomPlot *clusCharge10_20 = ui->customPlot5;//cluster charge, 10<t<20
    QCustomPlot *clusCharge20_30 = ui->customPlot6;//cluster charge, 20<t<30
    QCustomPlot *clusBeamProf = ui->customPlot7;//Beam profile histogram
    QCPBars* ClusterSize=RootHelpers::ConvertTH1(plots[0],clusSize->xAxis,clusSize->yAxis);

    QCPBars* chargelt10=RootHelpers::ConvertTH1(plots[1],clusChargelt10->xAxis,clusChargelt10->yAxis);
    QCPBars* charge1020=RootHelpers::ConvertTH1(plots[2],clusCharge10_20->xAxis,clusCharge10_20->yAxis);
    QCPBars* charge2030=RootHelpers::ConvertTH1(plots[3],clusCharge20_30->xAxis,clusCharge20_30->yAxis);
    QCPBars* profBeam = RootHelpers::ConvertTH1(plots[4],clusBeamProf->xAxis,clusBeamProf->yAxis);

    TProfile* prof_clus=plot2->ProfileX("prof_clus");
    QCPGraph *graph8 = ui->customPlot8->addGraph();

    RootHelpers::ConvertProfile(prof_clus, *graph8);
    ui->customPlot8->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->customPlot8->axisRect()->setupFullAxesBox();
    ui->customPlot8->graph()->setScatterStyle(QCPScatterStyle::ssCross);

    graph8->setPen(QPen(QColor(120, 120, 120), 2));
    ui->customPlot8->rescaleAxes();

    clusSize->addPlottable(ClusterSize);
    clusSize->rescaleAxes();

    clusChargelt10->addPlottable(chargelt10);
    clusChargelt10->rescaleAxes();

    clusCharge10_20->addPlottable(charge1020);
    clusCharge10_20->rescaleAxes();

    clusCharge20_30->addPlottable(charge2030);
    clusCharge20_30->rescaleAxes();

    clusBeamProf->addPlottable(profBeam);
    clusBeamProf->rescaleAxes();

    return;
}

void MainWindow::UpdateClusterSlot(TH1F** plots, TH2F* plot2){
    if(!ui->customPlot3->plottable()){
        //initialize for the first time
        AdamHackClusterPlots(ui,plots,plot2);
    }
    else{
     //std::vector<QVector<double>> vals = RootHelpers::DataFromTH1(plots[0]);
     QCPBars* clus_temp=RootHelpers::ConvertTH1(plots[0],ui->customPlot3->xAxis,ui->customPlot3->yAxis);
     ui->customPlot3->removePlottable(0);
     ui->customPlot3->addPlottable(clus_temp);
     ui->customPlot3->rescaleAxes();
     ui->customPlot3->replot();

     QCPBars* chrg_lt10_temp=RootHelpers::ConvertTH1(plots[1],ui->customPlot4->xAxis,ui->customPlot4->yAxis);
     ui->customPlot4->removePlottable(0);
     ui->customPlot4->addPlottable(chrg_lt10_temp);
     ui->customPlot4->rescaleAxes();
     ui->customPlot4->replot();

     QCPBars* chrg_1020_temp=RootHelpers::ConvertTH1(plots[2],ui->customPlot5->xAxis,ui->customPlot5->yAxis);
     ui->customPlot5->removePlottable(0);
     ui->customPlot5->addPlottable(chrg_1020_temp);
     ui->customPlot5->rescaleAxes();
     ui->customPlot5->replot();

     QCPBars* chrg_2030_temp=RootHelpers::ConvertTH1(plots[3],ui->customPlot6->xAxis,ui->customPlot6->yAxis);
     ui->customPlot6->removePlottable(0);
     ui->customPlot6->addPlottable(chrg_2030_temp);
     ui->customPlot6->rescaleAxes();
     ui->customPlot6->replot();

     QCPBars* profb = RootHelpers::ConvertTH1(plots[4],ui->customPlot7->xAxis,ui->customPlot7->yAxis);
     ui->customPlot7->removePlottable(0);
     ui->customPlot7->addPlottable(profb);
     ui->customPlot7->rescaleAxes();
     ui->customPlot7->replot();

     //other profile
     TProfile * dum2 = (TProfile*)plot2->ProfileX("dum2");
     std::vector<QVector<double>> vals2 = RootHelpers::DataFromProf(dum2);
     ui->customPlot8->graph(0)->setData(vals2[0],vals2[2]);
     ui->customPlot8->rescaleAxes();
     ui->customPlot8->replot();
     vals2.clear();
     delete dum2;
    }
    return;
}
