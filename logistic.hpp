#ifndef logistics
#define logistics
#include "Matrix.hpp"
#include <math.h>
using namespace std;
class logistic{
float sigmoid(float z){
    return (1/(1+exp(-z)));
}
public:
float predict(Matrix weight,Matrix input,float b){
    input=input*weight;
    float y=sigmoid(input.M()+b);
    if(y>0.5) return 1;
    else return 0;
}
Matrix sgd(Matrix x,vector<float> y,float &b){
    Matrix theta(1,1);
    cout<<x.row()<<endl;
    Matrix weight(x.col(),1);
    for(int j=0;j<1;j++){
    for(int i=0;i<x.row();i++){
        Matrix temp=x.return_row(i);
        temp=temp*weight;
        float eta=0.01;
        float thet=temp.M();
        thet=sigmoid(thet+b)-y[i];
        temp=x.return_row(i).transpose();
        temp.scalarmul(thet*eta);
        weight=weight-temp;
        b=b-(eta*thet);       
    }
    }
    return weight;   
    }
    float tester(Matrix weights,Matrix test,vector<float> y,float b){
        float accuracy=0;
        for(int i=0;i<test.row();i++){
            if(y[i]==predict(weights,test.return_row(i),b)) accuracy++;
        }
        return (accuracy/y.size())*100;
    }
};
#endif
