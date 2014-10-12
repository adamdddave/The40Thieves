#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QTimer>
#include "qcustomplot.h"
#include <TH2.h>
#include <TFormula.h>
#include <vector>
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
      
public:
    explicit MainWindow(TH2D* plot_to_hack = 0,QWidget *parent = 0);
    ~MainWindow();
    void AdamHacksetupColorMap(/*QCustomPlot *customPlot,QCustomPlot* customPlot2,*/Ui::MainWindow* ui, TH2D* plot_to_hack = 0);
    //change to the main window instead of passing plots by hand to have the ability to add more.
    TH2D *Fake2dHisto(TFormula *eq); 
    //void UpdateViewer(TH2D* PlotToUpdate);
    void ClearForNewRun();
    void AdamHackClusterPlots(Ui::MainWindow* ui,TH1F** plots=0,TH2F* plot2=0);
    void get_pedestals(std::vector<double>& ret);
private slots:
    void on_pushButton_clicked();
    void test_slot(int i);
    void UpdateViewerSlot(TH2D* plot);
    void on_pushButton_2_clicked();
    void UpdateClusterSlot(TH1F** plots, TH2F* plot2);

private:
    Ui::MainWindow *ui;
    std::vector<double>local_peds;
signals:
    void test_signal(int i);
    void UpdatePlots(TH2D* plot);
    void UpdateCluster(TH1F** clusterPlots, TH2F* clusADC);
};

#endif // MAINWINDOW_H
