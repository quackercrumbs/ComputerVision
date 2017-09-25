#include "programs.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


using namespace std;

namespace Programs {
  
  void ComputeAttributes(Image *label_image, string database, Image *out_image) {
    out_image->AllocateSpaceAndSetSize(label_image->num_rows(), label_image->num_columns());
    out_image->SetNumberGrayLevels(label_image->num_gray_levels());
    
    //maps labels to a list [area, sum of x, sum of y]
    unordered_map<int, vector<size_t>> center_map;
    vector<int> label_list;

    //find the area and the sum of x's and y's 
    for( size_t row = 0; row < label_image->num_rows(); row++ ) {
      for( size_t col = 0; col < label_image->num_columns(); col++) {
        int label = label_image->GetPixel(row,col);
        if(label != 0) {
          //if key does not exist
          if(center_map.find(label) == center_map.end()){
            vector<size_t> props = {1,col,row};
            center_map[label] = props;
            //label_list.push_back(label);
          }
          else {
            center_map[label][0]++;
            center_map[label][1] += col;
            center_map[label][2] += row;
          }
        }
      }
    }
    /* show areas, sum of x's and sum of y's MAKE SURE U ADD LABEL_LIST PUSHBACK IN CODE BEFORE
    for(int i = 0; i < label_list.size(); i++) { 
      cout << "Label: " << label_list[i] << endl;
      for(int j = 0; j < 3; j++) {
        cout << center_map[label_list[i]][j] << " ";
      }
      cout << endl << "-------" <<  endl;
    }
    */

    //calculate the center
    for(auto it = center_map.begin(); it != center_map.end(); ++it) {
      center_map[it->first][1] /= center_map[it->first][0];
      center_map[it->first][2] /= center_map[it->first][0];
      cout << "Label: " << it->first << endl;
      cout << "Area: " << center_map[it->first][0] << endl;
      cout << "X: " << center_map[it->first][1] << endl;  
      cout << "Y: " << center_map[it->first][2] << endl;  
      cout << "----------------" << endl;
    }
    //maps labels to their a,b,c paramets
    unordered_map<int,vector<size_t>> parameters_map;
    for(size_t row = 0; row < label_image->num_rows(); row++){
      for(size_t col = 0; col < label_image->num_columns(); col++){
        int label = label_image->GetPixel(row,col);
        if(label != 0){
          size_t x_center = center_map[label][1];
          size_t y_center = center_map[label][2];
          size_t a = col - x_center;
          size_t c = row - y_center;
          size_t b = 2 * a * c;
          a *= a;
          b *= b;
          if(parameters_map.Find(label) == parameters_map.end()) {
            vector<size_t> params = {a, b, c};
            parameters_map[label] = params;             
          }
        }
      }
    }
    
    //calculate theta and rho
    for(auto it = parameters_map.begin(); it != parameters_map.end(); ++it) {
      cout << endl;
    }

  }
}