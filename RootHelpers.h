#ifndef ROOTHELPERS_H
#define ROOTHELPERS_H


//Helper class to convert ROOT objects into QT plots for display
#include <TH2.h>
#include <TH1.h>
#include <TProfile.h>
#include "qcustomplot.h"
namespace RootHelpers{
//class RootHelpers{
// public:
  //constructor
  //inline virtual RootHelpers();
  //destructor
  //inline virtual ~RootHelpers();
  //Converters
  //  QCPColorMap* ConvertTH2(TH2* plot);
  QCPColorMap*ConvertTH2(TH2* plot,QCPAxis *xAxis, QCPAxis *yAxis);
  void ConvertProfile(TProfile* prof, QCPGraph &graph);
  std::vector< QVector<double>> DataFromProf(TProfile* prof);
  QCPBars* ConvertTH1(TH1* hist,QCPAxis *xAxis, QCPAxis *yAxis);
  //std::vector< QVector<double>> DataFromTH1(TH1* hist);
//};
};

#endif//ROOTHELPERS
