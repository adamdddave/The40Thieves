/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QCustomPlot *customPlot2;
    QWidget *tab_2;
    QCustomPlot *customPlot;
    QWidget *tab_3;
    QCustomPlot *customPlot3;
    QWidget *tab_4;
    QTabWidget *tabWidget_2;
    QWidget *tab_5;
    QCustomPlot *customPlot4;
    QWidget *tab_6;
    QCustomPlot *customPlot5;
    QWidget *tab_7;
    QCustomPlot *customPlot6;
    QLabel *label;
    QWidget *tab_8;
    QCustomPlot *customPlot7;
    QLabel *label_2;
    QWidget *tab_9;
    QCustomPlot *customPlot8;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QMenu *menuTest_plot;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(654, 571);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(230, 480, 114, 32));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(10, 10, 631, 461));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        customPlot2 = new QCustomPlot(tab);
        customPlot2->setObjectName(QStringLiteral("customPlot2"));
        customPlot2->setGeometry(QRect(30, 20, 451, 381));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tab_2->setEnabled(true);
        customPlot = new QCustomPlot(tab_2);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(30, 20, 491, 378));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        customPlot3 = new QCustomPlot(tab_3);
        customPlot3->setObjectName(QStringLiteral("customPlot3"));
        customPlot3->setGeometry(QRect(30, 20, 501, 321));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidget_2 = new QTabWidget(tab_4);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(60, 60, 451, 341));
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        customPlot4 = new QCustomPlot(tab_5);
        customPlot4->setObjectName(QStringLiteral("customPlot4"));
        customPlot4->setGeometry(QRect(30, 20, 391, 271));
        tabWidget_2->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        customPlot5 = new QCustomPlot(tab_6);
        customPlot5->setObjectName(QStringLiteral("customPlot5"));
        customPlot5->setGeometry(QRect(30, 20, 391, 271));
        tabWidget_2->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        customPlot6 = new QCustomPlot(tab_7);
        customPlot6->setObjectName(QStringLiteral("customPlot6"));
        customPlot6->setGeometry(QRect(30, 20, 391, 271));
        tabWidget_2->addTab(tab_7, QString());
        label = new QLabel(tab_4);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 20, 231, 21));
        tabWidget->addTab(tab_4, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        customPlot7 = new QCustomPlot(tab_8);
        customPlot7->setObjectName(QStringLiteral("customPlot7"));
        customPlot7->setGeometry(QRect(20, 20, 501, 381));
        label_2 = new QLabel(tab_8);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(220, 410, 101, 16));
        tabWidget->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName(QStringLiteral("tab_9"));
        customPlot8 = new QCustomPlot(tab_9);
        customPlot8->setObjectName(QStringLiteral("customPlot8"));
        customPlot8->setGeometry(QRect(50, 20, 491, 371));
        tabWidget->addTab(tab_9, QString());
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(60, 480, 101, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 654, 19));
        menuTest_plot = new QMenu(menuBar);
        menuTest_plot->setObjectName(QStringLiteral("menuTest_plot"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuTest_plot->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Quit!", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "<ADC> vs Channel", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "ADC vs Channel", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "ClusterSize", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("MainWindow", "T<10", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QApplication::translate("MainWindow", "10<T<20", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_7), QApplication::translate("MainWindow", "20<T<30", 0));
        label->setText(QApplication::translate("MainWindow", "Cluster ADC Counts in time bins [ns]", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Cluster ADCs", 0));
        label_2->setText(QApplication::translate("MainWindow", "Beetle Channel", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QApplication::translate("MainWindow", "Beam Prof.", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_9), QApplication::translate("MainWindow", "<Cluster ADC> vs TDC", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Reset Plots", 0));
        menuTest_plot->setTitle(QApplication::translate("MainWindow", "The 40 Thieves", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
