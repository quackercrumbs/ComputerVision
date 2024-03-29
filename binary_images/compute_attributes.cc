#include "programs.h"
#include "image.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <math.h>

using namespace std;

namespace Programs {
 
  vector<vector<double>> ComputeAttributes(Image *label_image, string database, Image *out_image) {
    if(out_image != nullptr) {
      out_image->AllocateSpaceAndSetSize(label_image->num_rows(), label_image->num_columns()); 
      out_image->SetNumberGrayLevels(label_image->num_gray_levels());
      for(size_t i = 0; i < label_image->num_rows(); i++) {
        for(size_t j = 0; j < label_image->num_columns(); j++) {
          out_image->SetPixel(i,j,label_image->GetPixel(i,j));
        }
      }
    }
    //maps labels to a list [area, sum of x, sum of y]
    unordered_map<int, vector<double>> center_map;

    //find the area and the sum of x's and y's 
    for( size_t row = 0; row < label_image->num_rows(); row++ ) {
      for( size_t col = 0; col < label_image->num_columns(); col++) {
        int label = label_image->GetPixel(row,col);
        if(label != 0) {
          //if key does not exist
          if(center_map.find(label) == center_map.end()){
            vector<double> props = {1,double(col),double(row)};
            center_map[label] = props;
          }
          else {
            center_map[label][0]++;
            center_map[label][1] += col;
            center_map[label][2] += row;
          }
        }
      }
    }
   
    //calculate the center
    for(auto it = center_map.begin(); it != center_map.end(); ++it) {
      center_map[it->first][1] /= center_map[it->first][0];
      center_map[it->first][2] /= center_map[it->first][0];
    }
    //maps labels to their a,b,c paramets
    //[a,b,c,theta,roundness]
    unordered_map<int,vector<double>> parameters_map;
    for(size_t row = 0; row < label_image->num_rows(); row++){
      for(size_t col = 0; col < label_image->num_columns(); col++){
        int label = label_image->GetPixel(row,col);
        if(label != 0){
          if(parameters_map.find(label) == parameters_map.end()) {
            vector<double> params = {0,0,0,0,0,0};
            parameters_map[label] = params;
          }
          double x_center = center_map[label][1];
          double y_center = center_map[label][2];
          double x_prime = col - x_center;
          double y_prime = row - y_center;
          double a = pow(x_prime,2); //x'^2
          double c = pow(y_prime,2); //y`^2
          double b = 2 * x_prime * y_prime; //2 * x` * y`
          parameters_map[label][0] += a;
          parameters_map[label][1] += b;
          parameters_map[label][2] += c;
        }
      }
    }
    
    //calculate theta, rho, inertia, and roundness. Also draw line
    for(auto it = parameters_map.begin(); it != parameters_map.end(); ++it) {
      int label = it->first;
      double x_center = center_map[label][1];
      double y_center = center_map[label][2];
      double a = parameters_map[label][0];
      double b = parameters_map[label][1];
      double c = parameters_map[label][2];
      double tan_theta = atan2(b,a-c)/2;
      double x = tan_theta-(3.14159/2);
      double max_theta = tan_theta + (3.141592/2);
      double rho = -1*((x_center*sin(tan_theta))-(y_center*cos(tan_theta)));

      //double cos_theta = acos(b,a-c)/2;
      //double sin_theta = asin(b,a-c)/2;
      
      double inertia = (a*pow(sin(tan_theta),2)) - (b*sin(tan_theta)*cos(tan_theta)) + (c*pow(cos(tan_theta),2));

      double max_inertia = (a*pow(sin(max_theta),2)) - (b*sin(max_theta)*cos(max_theta)) + (c*pow(cos(max_theta),2));

      double roundness = inertia/max_inertia;

      parameters_map[label][3] = rho;
      parameters_map[label][4] = inertia;
      if(tan_theta < 0)
        parameters_map[label][5] = (-1*tan_theta) - (3.14159/2);
      else
        parameters_map[label][5] = (3.14159/2)-tan_theta;
      parameters_map[label][6] = roundness;
      double x1 = x_center+100;
      double y1 = ((x1*sin(tan_theta))+rho)/cos(tan_theta);
      //double x1 = x_center + (200*sin(tan_theta));
      //double y1 = y_center + (200*cos(tan_theta));
      if(out_image != nullptr) {
        DrawLine(size_t(y_center),size_t(x_center),size_t(y1),size_t(x1),100,out_image);
        out_image->SetPixel(y_center, x_center, 255);
        for(int i = -1; i <= 1; i++) {
          for(int j = -1; j <= 1; j++) {
            out_image->SetPixel(y_center+i,x_center+j,255);
          }
        }
      }
    }
    //build vector to return
    vector<vector<double>> object_matrix;

    //write information into text file
    FILE *output = fopen(database.c_str(), "w");
    if(output == 0 && database.compare("") != 0) {
      cout << "Can't read file" << endl;
      //return object_matrix;
    }
    string header = "label | x center | y center | rho | inertia | orientation | roundness\n";
    if(output != 0)
      fprintf(output, header.c_str());
    for(auto it = parameters_map.begin(); it != parameters_map.end(); it++) {
      string output_data = "";
      int label = it->first;
      int x_center = center_map[label][1];
      int y_center = center_map[label][2];
      double rho = parameters_map[label][3];
      double inertia = parameters_map[label][4];
      double theta = parameters_map[label][5];
      double roundness = parameters_map[label][6];
      output_data = to_string(label) + " " + to_string(x_center) + " " + to_string(y_center) + " " + to_string(rho) + " ";
      output_data += to_string(inertia) + " " + to_string(theta) + " " + to_string(roundness) + "\n";
      if(output != 0)
        fprintf(output, output_data.c_str());
      vector<double> data = {double(label), double(x_center), double(y_center), rho, inertia, theta, roundness};
      object_matrix.push_back(data);
    }
    if(output!= 0) fclose(output);
    return object_matrix;
  }
}
