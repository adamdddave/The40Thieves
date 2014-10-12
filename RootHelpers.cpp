//Helper class to convert ROOT objects into QT plots for display
//Adam Davis
//header
#include "RootHelpers.h"
//root includes
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
//qcustomplot
#include "qcustomplot.h"


namespace RootHelpers{
//all the stuff we actually want
QCPColorMap* ConvertTH2(TH2* plot,QCPAxis *xAxis, QCPAxis *yAxis){
  //this is how we get the 2d histogram in Qt
  QCPColorMap* ret = new QCPColorMap(xAxis,yAxis);
  //get the external info we need from the plot
  int NBinsX = plot->GetNbinsX();
  int NBinsY = plot->GetNbinsY();
  double xmin = plot->GetXaxis()->GetXmin();
  double xmax = plot->GetXaxis()->GetXmax();
  double ymin = plot->GetYaxis()->GetXmin();//terrible method, but this should work
  double ymax = plot->GetYaxis()->GetXmax();//terrible
  
  ret->data()->setSize(NBinsX,NBinsY);
  ret->data()->setRange(QCPRange(xmin,xmax),QCPRange(ymin,ymax));
  double z;
  //loop over the data;
  for (int xIndex=0; xIndex<NBinsX; ++xIndex){
      for (int yIndex=0; yIndex<NBinsY; ++yIndex){
    //ret->data()->cellToCoord(xIndex, yIndex, &x, &y);
	z = plot->GetBinContent(xIndex+1,yIndex+1);
	ret->data()->setCell(xIndex, yIndex, z);
      }
  }
  //should be done then. One minor detail. Root draws the bins from [low edge,high edge)
  //qcp draws from the bin center, so it's offset.
  //now the rest is just formatting
  return ret;
  
}

void ConvertProfile(TProfile* prof, QCPGraph &graph){
  //how we put the profile histogram in Qt.
  //passing the graph to alter is just easier :)
  QVector<double> xvals,yvals,xerrs, yerrs;
  int nbins = prof->GetNbinsX();
  //get the values
  for(int i=0; i<nbins;++i){
    xvals.push_back(prof->GetBinCenter(i+1));
    yvals.push_back(prof->GetBinContent(i+1));
    xerrs.push_back(prof->GetBinWidth(i+1)/2.);
    yerrs.push_back(prof->GetBinError(i+1));
  }
  
  graph.setData(xvals, yvals);
  graph.setDataValueError(xvals, yvals, yerrs);//symmetric errors, only in y.
  graph.setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
  graph.setPen(QPen(QColor(120, 120, 120), 2));
  graph.setLineStyle(QCPGraph::LineStyle::lsNone);
  return;
}


std::vector< QVector<double>> DataFromProf(TProfile* prof){
    std::vector<QVector<double>> ret;
    QVector<double> xvals,yvals,xerrs, yerrs;
    int nbins = prof->GetNbinsX();
    //get the values
    for(int i=0; i<nbins;++i){
      xvals.push_back(prof->GetBinCenter(i+1));
      yvals.push_back(prof->GetBinContent(i+1));
      xerrs.push_back(prof->GetBinWidth(i+1)/2.);
      yerrs.push_back(prof->GetBinError(i+1));
    }
    ret.push_back(xvals);
    ret.push_back(xerrs);
    ret.push_back(yvals);
    ret.push_back(yerrs);
    return ret;
}

QCPBars *ConvertTH1(TH1 *hist,QCPAxis *xAxis, QCPAxis *yAxis){
    QVector<double> xvals,yvals;
    int nbins=hist->GetNbinsX();
    for(int i=0; i<nbins;++i){
        xvals.push_back(hist->GetBinCenter(i+1));
        yvals.push_back(hist->GetBinContent(i+1));
    }

    QCPBars* ret=new QCPBars(xAxis,yAxis);
    ret->setWidth(0.9*(double)hist->GetBinWidth(1));//leave some room between the bars
    ret->setData(xvals,yvals);
    yAxis->setRange(0,1.2*hist->GetBinContent(hist->GetMaximum()));
    //now do some fancy formatting.
    ret->setPen(Qt::NoPen);
    ret->setBrush(QColor(Qt::darkRed));
    xvals.clear();
    yvals.clear();
    return ret;
}
/*
std::vector< QVector<double>> DataFromTH1(TH1* hist){
    std::vector< QVector<double>> ret;
    QVector<double> xvals,yvals;
    int nbins = hist->GetNbinsX();
    //get the values
    for(int i=0; i<nbins;++i){
      xvals.push_back(hist->GetBinCenter(i+1));
      yvals.push_back(hist->GetBinContent(i+1));
    }
    ret.push_back(xvals);
    ret.push_back(yvals);
    return ret;
}*/
};
