#include "Matrix.hpp"
#include<math.h>
class layer{
    void relu(){
        for(int i=0;i<l.row();i++){
            a.mat[i][0]= l.mat[i][0] >0 ? l.mat[i][0]:0;
        }
    }
    void sigmoid(){
        for(int i=0;i<l.row();i++){
            a.mat[i][0]= 1/(1+exp(-l.mat[i][0]));
        }
    }
    void relu_der(){
        for(int i=0;i<l.row();i++){
            a_error.mat[i][0]= l.mat[i][0] >0 ? 1:0;
        }
    }
    void sigmoid_der(){
        for(int i=0;i<l.row();i++){
            a_error.mat[i][0]= a.mat[i][0]*(1-a.mat[i][0]);
        }
    }
    public:
        Matrix a,l,w,a_error,del,b;
        int n;
        string s;
        layer(int n,string s){
            this->n=n;
            this->s=s;
            a.resizer(n,1,0);
            b.resizer(n,1,0);
            l.resizer(n,1,0);
            a_error.resizer(1,n,0);
            
        }
        void activation(){
            if(s=="relu") 
            {relu();}
            else if(s=="sigmoid") {sigmoid();}
            return;
        }
        void linear(Matrix a_prev) {
        if(w.row() != a_prev.row()) {
            w.resizer(n, a_prev.row(), 0.1);  // deterministic init
        }
        l = ( w*a_prev) + b;
    }
};
class neural{
    vector<layer> nn;
    Matrix data;
    public:
    neural(string s){
        data(s);
    }
};
