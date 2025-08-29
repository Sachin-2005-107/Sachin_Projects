#ifndef logistics
#define logistics
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include "Matrix.hpp"
using namespace std;
float sigmoid(float z){
    return (1/(1+exp(-z)));
}
void sgd(Matrix x,vector<float> y){
    Matrix theta(1,1);
    float b=0;
    Matrix weight(x.col(),1);
    cout<<x.row()<<endl;
    for(int j=0;j<100;j++){
    for(int i=0;i<x.row();i++){
        Matrix temp=x.return_row(i);
        temp=temp*weight;
        float eta=0.01;
        float thet=temp.M();
        thet=sigmoid(thet+b)-y[i];
        temp=x.return_row(i).transpose();
        temp.scalarmul(thet*eta);
        weight=weight-temp;
       //b=b-(eta*thet);       
    }
}
    cout<<b<<endl;
    for(auto i:weight.return_col(0)) cout<<i<<" ";
    cout<<endl;
   
}
#endif