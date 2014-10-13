//************************************************
// Author: Federica Lionetto
// Created on: 07/21/2014
//************************************************

//List of useful variables.

// Header guard.
#ifndef __PARAMETERS_H_INCLUDED__
#define __PARAMETERS_H_INCLUDED__

// Number of Beetle channels.
const int N = 256;

// Only Beetle channels from 128 to 255 are wirebonded to the sensor.
const int firstChannel = 128;

const double minH = 5.0;
const double maxH = 15.0;
const double maxDH = 2.0;
const double minSizeStep = 3;


const double minSeed = 20.0;           // Min Threshold for Seed of Cluster
const double minSide = 8.0;            // Min Threshold for Side strips in cluster  
const int minSize = 1;                 // Min cluster size
const int minChannelInWindow = 50;     // No. channels within 9 ADC counts to define pathological events
const int largePulseSize     = 150;    // Large pulse size for pathological events

const int maxADC_Pass1 = 15;
const int maxADC_Pass2 = 15;

const int debug = 3;

//const float ChargeVsTDC_high=50;

#endif 
