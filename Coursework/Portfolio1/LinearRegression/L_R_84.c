#include <stdio.h>
#include <math.h>

/******************************************************************************
 * This program takes an initial estimate of m and c and finds the associated 
 * rms error. It is then as a base to generate and evaluate 8 new estimates, 
 * which are steps in different directions in m-c space. The best estimate is 
 * then used as the base for another iteration of "generate and evaluate". This 
 * continues until none of the new estimates are better than the base. This is
 * a gradient search for a minimum in mc-space.
 * 
 * To compile:
 *   cc -o L_R_84 L_R_84.c -lm
 * 
 * To run:
 *   ./L_R_84
 * 
 * Dr Kevan Buckley, University of Wolverhampton, 2018
 *****************************************************************************/

typedef struct point_t {
  double x;
  double y;
} point_t;

int n_data = 1000;
point_t data[];

double residual_error(double x, double y, double m, double c) {
  double e = (m * x) + c - y;
  return e * e;
}

double rms_error(double m, double c) {
  int i;
  double mean;
  double error_sum = 0;
  
  for(i=0; i<n_data; i++) {
    error_sum += residual_error(data[i].x, data[i].y, m, c);  
  }
  
  mean = error_sum / n_data;
  
  return sqrt(mean);
}

int main() {
  int i;
  double bm = 1.3;
  double bc = 10;
  double be;
  double dm[8];
  double dc[8];
  double e[8];
  double step = 0.01;
  double best_error = 999999999;
  int best_error_i;
  int minimum_found = 0;
  
  double om[] = {0,1,1, 1, 0,-1,-1,-1};
  double oc[] = {1,1,0,-1,-1,-1, 0, 1};

  be = rms_error(bm, bc);

  while(!minimum_found) {
    for(i=0;i<8;i++) {
      dm[i] = bm + (om[i] * step);
      dc[i] = bc + (oc[i] * step);    
    }
      
    for(i=0;i<8;i++) {
      e[i] = rms_error(dm[i], dc[i]);
      if(e[i] < best_error) {
        best_error = e[i];
        best_error_i = i;
      }
    }

    printf("best m,c is %lf,%lf with error %lf in direction %d\n", 
      dm[best_error_i], dc[best_error_i], best_error, best_error_i);
    if(best_error < be) {
      be = best_error;
      bm = dm[best_error_i];
      bc = dc[best_error_i];
    } else {
      minimum_found = 1;
    }
  }
  printf("minimum m,c is %lf,%lf with error %lf\n", bm, bc, be);

  return 0;
}

point_t data[] = {
  {71.81,133.75},{85.89,133.55},{82.39,150.79},{67.30,111.91},
  {72.43,119.97},{65.93,108.62},{82.77,155.40},{65.23,109.17},
  {78.50,123.83},{82.84,131.75},{65.34,120.82},{73.67,130.20},
  {78.94,120.51},{34.42,62.04},{ 8.73,15.55},{23.45,55.17},
  {31.72,58.36},{65.08,113.47},{71.81,128.61},{75.72,121.32},
  {10.85,42.15},{49.29,87.56},{69.32,107.59},{23.18,60.57},
  {57.50,104.58},{51.22,95.42},{ 1.87,34.88},{ 0.25,33.58},
  {92.31,161.96},{90.44,165.21},{51.17,117.82},{70.31,114.64},
  {59.11,100.04},{17.46,59.44},{78.86,122.45},{74.48,144.72},
  {97.05,153.21},{53.79,90.54},{80.87,143.61},{42.49,86.11},
  {69.93,125.88},{71.86,141.65},{ 4.82,30.58},{45.61,65.66},
  {84.52,134.78},{97.06,154.56},{21.32,56.30},{44.18,64.58},
  { 2.66,23.04},{51.37,76.64},{21.43,59.05},{19.79,52.99},
  {81.06,137.68},{44.78,82.78},{50.11,76.99},{77.74,130.65},
  {85.48,153.88},{74.76,126.04},{87.23,132.37},{37.96,70.32},
  {92.10,148.88},{35.49,60.54},{98.95,158.99},{ 9.66,37.03},
  {21.07,56.81},{75.75,104.60},{42.63,80.73},{19.18,73.68},
  {69.42,124.30},{79.12,137.33},{11.06,39.94},{13.98,41.17},
  {15.48,39.69},{ 0.35,19.09},{79.17,148.87},{93.33,143.52},
  {39.32,61.76},{20.18,60.38},{11.79,32.52},{16.51,50.62},
  {71.53,104.03},{16.04,34.95},{51.37,105.66},{47.44,65.97},
  {79.12,141.21},{ 4.00,16.20},{97.62,153.70},{65.44,130.26},
  {50.20,121.77},{99.79,170.26},{76.36,135.83},{82.17,147.58},
  {12.23,34.62},{31.39,80.38},{63.59,110.08},{79.87,112.29},
  {91.99,148.73},{95.57,163.30},{36.91,68.25},{35.42,100.44},
  {88.93,165.23},{54.48,101.08},{42.25,81.06},{63.79,109.19},
  {69.30,125.01},{22.12,44.31},{ 4.31,37.11},{50.40,102.16},
  {44.11,64.66},{15.53,37.62},{11.52,30.78},{37.50,88.62},
  {84.92,145.18},{14.65,45.40},{44.26,88.55},{64.47,109.85},
  {20.17,62.08},{75.44,118.67},{56.76,102.67},{97.74,157.14},
  {90.10,130.66},{23.82,60.15},{95.21,154.21},{63.42,116.59},
  {47.35,86.90},{21.22,36.64},{47.07,76.04},{93.51,161.37},
  {90.74,135.61},{ 1.89,42.37},{99.41,153.91},{79.58,142.84},
  {47.90,83.54},{30.89,73.61},{ 2.05,37.83},{89.51,157.44},
  { 8.02,30.93},{50.97,78.93},{43.22,86.36},{32.69,64.67},
  {94.74,130.84},{27.82,53.54},{85.05,151.88},{82.34,127.32},
  {49.14,98.33},{ 6.85,10.92},{32.17,72.66},{44.61,92.76},
  {22.51,78.78},{18.37,41.97},{62.72,102.57},{44.41,107.65},
  {46.40,88.98},{43.14,93.46},{67.92,105.60},{23.84,40.69},
  { 4.03,34.92},{ 5.64,34.23},{79.83,129.40},{82.70,144.49},
  {83.02,124.05},{64.88,124.17},{20.12,55.01},{49.36,86.36},
  {77.62,117.64},{18.52,45.33},{52.21,109.18},{15.02,39.89},
  {79.26,136.34},{54.53,95.15},{28.56,77.08},{ 7.83,16.21},
  {26.24,55.37},{37.16,70.27},{19.93,39.84},{87.64,120.18},
  {88.19,129.91},{15.68,56.99},{55.77,104.48},{57.24,106.34},
  {69.18,125.86},{50.75,91.00},{54.75,96.92},{88.10,153.26},
  {97.23,161.42},{55.52,128.90},{42.43,79.44},{43.30,71.53},
  {17.73,40.42},{93.22,172.37},{86.72,137.77},{51.68,125.48},
  { 6.20,53.74},{36.62,79.91},{95.96,156.68},{19.80,45.74},
  { 7.95,33.30},{19.11,65.48},{73.86,156.39},{13.35,58.42},
  {15.98,58.41},{27.63,75.79},{39.36,100.90},{23.30,49.78},
  {91.02,174.92},{58.76,113.32},{56.86,89.12},{74.60,124.47},
  {87.95,145.95},{ 5.65,26.01},{44.38,84.85},{61.21,111.78},
  {96.07,168.07},{64.95,119.02},{39.36,61.92},{ 6.43,37.54},
  {32.17,68.34},{30.40,73.48},{15.41,40.03},{49.93,85.61},
  {72.84,121.47},{79.49,135.27},{12.54,51.85},{96.52,163.46},
  {66.51,98.57},{48.32,96.21},{90.47,139.35},{49.45,90.23},
  {97.31,153.19},{ 6.99,33.04},{79.27,155.01},{28.09,59.98},
  {29.65,46.80},{ 6.41,26.53},{89.09,155.66},{83.66,135.40},
  {87.21,128.39},{39.34,75.70},{ 5.29,18.70},{75.91,128.16},
  {36.17,73.07},{ 2.95,25.49},{70.12,119.10},{76.57,121.06},
  {37.18,81.73},{26.54,71.98},{ 1.86,22.98},{63.22,130.78},
  { 9.44,52.14},{22.05,59.05},{33.75,77.73},{17.22,41.22},
  {97.39,159.14},{83.45,133.76},{53.44,80.57},{68.93,97.49},
  {30.97,46.79},{60.63,115.57},{80.33,131.34},{21.99,50.93},
  {55.51,114.58},{55.53,96.06},{63.02,107.21},{97.16,161.85},
  {22.71,59.05},{53.90,93.15},{79.03,135.50},{24.98,58.91},
  {53.35,77.77},{62.54,111.55},{ 8.14,30.34},{21.20,57.84},
  {80.80,131.03},{82.97,147.94},{13.34,45.07},{36.39,79.55},
  {49.26,97.81},{39.35,85.87},{17.81,57.99},{10.79,50.78},
  {86.11,143.90},{75.31,132.09},{89.64,140.60},{92.60,137.96},
  {55.41,93.53},{12.59,48.40},{15.58,59.60},{34.90,86.37},
  {99.68,154.75},{88.60,136.03},{82.50,126.48},{88.50,134.98},
  { 1.07,28.75},{99.30,167.43},{ 8.11,14.26},{86.82,145.36},
  { 4.77,19.71},{32.49,68.46},{35.63,75.41},{80.60,141.36},
  {53.62,102.19},{26.15,63.08},{67.67,115.13},{61.72,126.25},
  {50.58,91.97},{71.46,123.77},{61.42,98.61},{89.04,147.12},
  {38.41,71.83},{21.14,51.38},{59.04,108.78},{29.09,57.48},
  {11.38,50.98},{10.28,35.84},{45.56,86.89},{95.39,145.33},
  {51.24,96.97},{97.41,163.34},{31.73,77.61},{ 9.73,36.27},
  {41.55,73.15},{92.88,158.72},{60.16,99.18},{48.55,94.55},
  {82.19,147.90},{60.01,104.26},{93.66,150.29},{13.82,37.15},
  {51.11,85.26},{65.26,105.78},{19.26,32.52},{38.43,77.91},
  {51.47,85.84},{96.97,153.73},{59.30,107.67},{ 0.07,26.65},
  {80.56,135.72},{76.04,137.06},{88.61,142.04},{65.39,113.36},
  {59.77,101.26},{68.59,132.36},{66.76,114.37},{54.10,95.76},
  {73.43,114.04},{25.25,49.82},{40.70,76.08},{67.14,123.21},
  {58.08,107.35},{25.91,67.67},{70.24,125.48},{ 4.39,35.71},
  {28.12,63.20},{57.87,93.54},{14.98,54.26},{73.40,129.67},
  {11.65,43.23},{ 6.48, 7.79},{ 4.34,23.19},{57.96,117.91},
  {40.59,64.13},{59.70,102.44},{69.77,123.84},{81.09,140.18},
  {24.78,31.31},{ 9.11,18.71},{52.35,95.53},{41.51,75.96},
  {14.25,42.30},{95.18,161.64},{82.80,147.19},{37.69,85.89},
  {50.22,86.58},{ 9.61,34.74},{85.43,133.04},{30.83,55.35},
  {28.01,59.72},{17.65,69.10},{22.88,49.17},{92.61,145.34},
  {48.89,99.29},{ 3.27,27.70},{63.87,101.75},{74.76,122.07},
  {13.74,37.53},{ 5.66,32.70},{72.30,123.40},{ 0.51,27.51},
  {14.73,26.65},{99.81,165.29},{55.72,101.54},{76.73,121.37},
  {84.59,156.55},{63.89,113.13},{72.47,104.87},{19.83,50.51},
  { 8.05,32.87},{60.34,115.79},{23.94,52.20},{42.28,82.34},
  {26.31,58.45},{21.64,52.47},{23.67,53.46},{56.81,92.74},
  {75.74,118.51},{20.25,44.91},{83.80,152.05},{45.21,109.99},
  {53.40,94.95},{48.01,79.89},{86.15,126.70},{31.76,65.23},
  {37.00,71.39},{97.00,150.49},{74.45,158.08},{56.43,95.25},
  {15.26,50.28},{72.99,134.83},{25.73,50.39},{66.12,103.53},
  {84.47,142.16},{34.60,60.59},{39.31,83.77},{ 5.83, 7.76},
  {58.47,115.10},{13.25,34.10},{15.05,57.12},{21.60,48.62},
  {86.43,158.68},{93.70,157.58},{21.89,49.21},{36.54,90.96},
  {11.65,44.60},{69.47,126.67},{15.50,72.13},{32.62,77.71},
  {88.46,147.60},{57.82,105.16},{ 3.04,24.52},{73.18,114.88},
  { 1.89,17.39},{47.48,80.24},{94.69,166.52},{86.61,162.53},
  {93.68,169.74},{20.15,49.66},{89.47,150.21},{27.20,73.32},
  {54.12,97.33},{48.92,96.41},{81.94,152.06},{77.89,132.22},
  {96.42,164.13},{79.34,130.28},{51.37,102.16},{55.97,89.64},
  {43.23,78.79},{77.07,139.29},{75.65,138.43},{18.77,43.38},
  {90.52,144.64},{19.17,49.23},{34.35,70.96},{70.52,121.88},
  {30.72,61.05},{53.35,94.84},{86.15,147.31},{20.81,60.94},
  {27.15,53.45},{17.63,35.98},{99.82,158.99},{66.97,110.36},
  {65.87,123.68},{78.08,129.36},{99.91,175.45},{72.93,125.14},
  {35.08,70.94},{28.46,49.01},{80.54,147.46},{77.18,122.58},
  {77.71,156.43},{91.31,146.54},{20.92,51.17},{50.87,97.76},
  {99.08,167.07},{62.57,121.71},{81.74,145.81},{30.88,71.61},
  {81.94,146.49},{ 1.36,21.86},{13.60,27.68},{13.72,31.35},
  {25.24,41.75},{60.65,114.39},{ 5.10,16.14},{96.04,163.74},
  {30.16,69.39},{ 5.21,21.80},{13.26,47.80},{34.04,61.40},
  {41.31,84.48},{13.87,42.78},{80.57,155.45},{73.85,117.81},
  {44.09,85.04},{67.97,110.42},{66.05,144.78},{76.72,136.42},
  {31.80,68.47},{21.76,40.62},{19.65,57.37},{47.05,92.14},
  {72.80,140.18},{28.75,67.93},{81.58,153.50},{ 3.91,31.01},
  {93.56,155.20},{45.11,111.36},{95.57,150.14},{31.63,80.29},
  {81.56,130.14},{69.79,136.07},{30.14,44.97},{56.51,119.88},
  {91.57,144.92},{73.90,127.37},{86.56,130.40},{33.26,57.53},
  {72.16,124.71},{ 4.90,31.13},{26.34,68.73},{18.22,43.77},
  { 5.42,28.57},{75.23,141.83},{13.72,44.69},{98.92,154.34},
  {94.30,157.85},{97.47,160.05},{49.57,97.75},{99.09,161.98},
  {51.01,87.85},{29.22,69.17},{87.34,146.82},{26.04,49.38},
  {44.11,89.25},{ 8.74,34.33},{24.41,70.14},{57.84,105.52},
  {46.64,89.59},{61.47,115.25},{87.64,138.31},{10.52,34.23},
  {90.60,151.93},{63.39,110.69},{ 0.97,33.88},{13.54,42.86},
  {87.02,163.01},{48.04,67.13},{84.91,153.18},{17.13,50.11},
  {98.46,159.86},{24.74,40.26},{36.78,76.12},{93.00,169.21},
  {96.16,154.92},{88.44,165.84},{54.06,91.19},{38.91,71.38},
  { 4.61,27.77},{82.45,127.85},{47.04,81.41},{54.53,104.53},
  { 1.99,13.20},{48.19,84.44},{83.25,148.38},{ 3.93,24.18},
  {86.70,149.70},{58.11,111.23},{81.87,134.40},{ 4.81,35.75},
  {43.63,83.58},{ 4.86,37.40},{ 2.93,16.55},{40.61,76.67},
  {18.91,47.84},{74.21,129.32},{33.67,82.38},{41.75,88.69},
  {93.55,146.01},{32.84,54.09},{36.18,71.94},{30.59,68.87},
  {27.18,69.28},{17.02,59.72},{89.56,159.21},{76.28,131.23},
  {55.97,98.43},{65.93,131.28},{34.72,68.34},{10.65,42.12},
  { 9.01,38.63},{ 9.35,52.74},{13.36,44.38},{ 5.36,47.57},
  {49.10,80.75},{35.50,81.38},{85.86,143.17},{57.65,89.93},
  {65.35,102.37},{99.12,168.40},{49.52,94.52},{18.03,53.14},
  {78.95,135.86},{22.47,54.44},{51.75,103.26},{ 0.48,17.73},
  {82.00,159.36},{ 5.63,32.73},{95.25,155.74},{51.55,90.42},
  {98.90,154.14},{25.95,64.50},{79.12,140.50},{20.59,52.04},
  {54.86,113.02},{22.06,55.16},{77.06,136.48},{65.61,122.37},
  {31.20,76.49},{82.60,148.76},{19.53,54.99},{81.21,140.19},
  {81.87,150.51},{69.68,136.12},{40.20,75.56},{27.08,66.95},
  {20.48,54.12},{72.17,125.66},{52.48,101.11},{30.77,81.74},
  {99.74,154.30},{29.30,71.54},{ 2.32,26.03},{51.04,91.71},
  {37.30,75.39},{14.81,41.92},{19.85,57.62},{37.60,64.73},
  {77.39,136.96},{65.69,118.79},{ 5.57,20.49},{60.47,104.70},
  {12.32,49.43},{71.33,133.27},{22.04,62.24},{49.04,98.96},
  {28.51,77.93},{35.03,75.84},{79.22,118.50},{26.65,80.44},
  {69.35,108.29},{56.03,102.40},{26.20,62.66},{66.56,131.81},
  {44.51,94.10},{34.08,62.61},{17.47,52.36},{51.22,108.60},
  {93.35,157.84},{69.55,114.79},{18.68,50.77},{41.56,91.26},
  {65.19,127.38},{88.77,148.88},{ 9.99,30.10},{49.67,77.20},
  {90.28,165.16},{26.69,53.43},{ 7.95,39.17},{75.34,127.81},
  { 0.12, 7.67},{95.35,170.18},{63.57,116.43},{54.73,97.98},
  {95.11,149.50},{65.12,108.21},{65.62,118.79},{55.24,103.25},
  {45.00,86.45},{89.93,170.27},{63.15,104.46},{98.62,150.57},
  {54.04,101.18},{38.92,97.39},{65.66,112.45},{94.08,145.09},
  { 8.02,52.57},{90.39,149.90},{49.97,104.95},{69.39,144.12},
  {56.28,104.01},{30.13,42.35},{83.41,135.62},{25.42,59.47},
  { 8.60,47.93},{ 7.96,26.67},{84.46,135.72},{96.40,173.29},
  {47.38,91.27},{90.73,145.91},{70.02,129.57},{37.86,68.46},
  {38.18,87.29},{28.46,66.31},{29.23,49.56},{ 2.83,25.34},
  {55.92,103.82},{80.53,145.86},{55.34,97.42},{91.58,119.46},
  {76.04,143.07},{60.28,117.98},{ 0.54, 5.00},{ 9.50,44.08},
  {59.81,107.20},{ 4.35,31.95},{48.87,86.27},{93.95,146.06},
  {99.07,150.56},{26.88,55.92},{12.98,45.95},{16.74,39.38},
  {35.39,72.22},{84.23,144.44},{90.69,141.06},{65.69,127.54},
  {26.91,56.78},{15.06,46.26},{32.40,64.69},{44.46,91.33},
  {76.51,145.64},{94.09,151.96},{57.45,92.66},{15.97,42.98},
  {81.54,132.18},{58.37,113.71},{29.14,53.90},{61.15,101.46},
  {17.28,45.91},{40.12,93.12},{ 0.36,10.11},{17.99,61.07},
  {35.90,82.30},{22.60,65.99},{32.75,78.46},{23.83,73.75},
  {94.73,154.62},{ 4.38,23.01},{78.50,118.27},{64.21,97.91},
  {92.39,159.66},{38.28,83.70},{79.26,136.65},{17.66,36.98},
  {32.52,67.86},{77.98,145.93},{79.98,144.76},{20.69,45.94},
  {98.63,172.79},{58.09,117.55},{82.28,142.01},{60.87,104.83},
  {44.91,92.45},{97.89,168.22},{20.75,62.93},{10.51,48.50},
  {53.90,101.25},{58.42,101.98},{72.74,123.84},{46.59,90.86},
  {29.87,56.12},{62.39,122.94},{57.68,92.27},{33.30,76.22},
  { 3.56,28.54},{46.08,106.41},{97.39,151.31},{35.45,66.84},
  {34.63,87.83},{87.79,144.36},{28.20,53.50},{78.44,140.84},
  {11.40,49.61},{85.04,142.50},{85.04,158.15},{68.40,94.57},
  {17.19,53.83},{82.41,146.61},{23.63,39.81},{29.03,54.35},
  {83.65,138.45},{48.46,97.27},{18.77,50.92},{44.94,97.79},
  {67.65,105.01},{45.70,54.12},{ 9.58,43.90},{99.27,150.15},
  {12.73,36.30},{98.01,174.70},{85.29,145.34},{ 7.32,47.81},
  {87.71,165.09},{46.50,92.73},{33.04,76.52},{40.94,78.03},
  {12.53,29.91},{50.90,92.49},{51.52,104.94},{99.07,151.71},
  {80.84,138.04},{14.73,24.97},{61.84,96.48},{96.23,140.28},
  {14.95,47.46},{39.87,70.43},{61.79,120.74},{78.53,123.10},
  {30.06,63.50},{57.80,109.88},{18.02,55.74},{66.63,96.24},
  {71.62,121.35},{50.25,98.35},{ 9.15,30.45},{38.30,59.16},
  {12.10,48.06},{68.87,123.37},{74.45,133.33},{95.47,158.56},
  {67.57,122.32},{62.27,97.67},{33.02,68.44},{78.82,135.53},
  {89.73,160.49},{16.73,45.84},{86.27,130.72},{16.96,34.50},
  { 7.70,17.39},{89.55,147.99},{28.07,73.54},{28.11,75.97},
  {39.00,78.29},{47.87,96.73},{88.54,133.29},{71.47,130.74},
  {63.14,114.27},{20.93,54.58},{74.15,138.21},{66.42,116.12},
  { 2.90,46.27},{71.33,115.60},{40.72,96.90},{45.43,76.82},
  {63.10,113.57},{10.91,45.11},{94.11,157.71},{ 2.02,46.92},
  {83.43,150.57},{18.49,38.88},{70.62,123.24},{36.43,81.80},
  {61.06,110.80},{41.93,69.91},{78.62,144.55},{ 3.05,17.87},
  {40.72,96.97},{28.88,73.84},{50.41,90.62},{59.30,96.67},
  { 6.13,45.55},{70.11,134.27},{74.61,127.51},{56.90,123.42},
  {94.13,144.09},{28.26,72.79},{14.47,58.59},{95.53,151.16},
  {51.96,102.88},{69.25,129.38},{27.16,51.62},{97.88,180.78},
  {94.78,168.77},{80.56,155.02},{27.92,64.69},{ 4.77,31.18},
  {31.24,71.23},{27.42,78.61},{29.42,67.70},{76.86,134.28},
  {31.36,54.76},{50.42,94.73},{80.73,121.10},{ 1.99,20.51},
  {21.56,57.13},{21.75,66.02},{13.85,59.84},{13.48,52.82},
  {59.32,103.64},{94.53,158.77},{18.54,35.66},{64.88,103.79},
  {46.65,98.03},{ 5.95,33.17},{ 6.57,17.17},{76.32,133.82},
  {94.11,154.07},{62.67,108.53},{30.27,58.27},{98.45,158.59},
  {81.31,152.48},{23.06,65.35},{82.91,129.73},{96.03,150.73},
  { 2.11, 6.42},{27.24,69.29},{75.21,135.75},{ 5.44,34.12},
  {80.93,128.91},{79.60,108.46},{99.99,162.20},{62.44,115.75},
  {13.28,33.20},{43.22,86.14},{26.50,58.88},{34.72,85.01},
  {54.56,105.50},{12.27,18.15},{13.66,70.53},{ 7.74,35.72},
  {84.51,134.88},{30.75,39.17},{57.14,90.09},{ 1.40,10.91},
  {67.44,110.82},{53.03,96.34},{35.39,65.18},{65.29,102.95},
  {59.35,102.78},{54.80,101.59},{16.56,57.37},{92.71,170.67},
  {68.68,125.65},{77.44,129.75},{23.68,51.06},{85.89,142.67},
  {94.91,153.05},{56.30,104.40},{58.30,107.14},{45.98,91.75},
  {90.18,150.31},{97.63,150.23},{55.62,114.59},{50.83,111.00},
  {37.56,86.33},{ 9.99,42.83},{71.14,122.30},{42.92,63.75},
  {98.82,166.58},{65.32,119.34},{12.09,46.70},{88.17,134.52},
  {68.55,137.66},{93.42,143.64},{57.99,112.75},{29.60,47.62},
  {23.24,67.34},{60.36,121.02},{79.82,135.52},{72.66,122.07},
  {24.54,69.68},{43.34,81.69},{70.53,129.80},{65.37,126.24},
  {31.11,57.14},{ 1.22,25.79},{19.20,63.95},{68.51,105.34},
  {46.51,87.43},{60.17,109.16},{ 3.50,31.20},{76.58,127.58},
  { 1.75,11.07},{85.08,132.82},{12.42,46.23},{23.30,48.69},
  { 9.16,27.43},{55.45,118.52},{87.40,162.78},{72.97,122.98}
};
