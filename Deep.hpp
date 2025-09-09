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
    Matrix data,out;
    int n; //number of layers in the neural network
    float LCE(int i){
        float y=out.get_element(i,0);
        float p=nn[0].a.get_element(0,0);
        return (-y/p)+((1-y)/(1-p));
    }
    float MSE(int i){
        float y=out.get_element(i,0);
        float p=nn[0].a.get_element(0,0);
        return p-y;
    }
    public:
    neural(int n , string s){
        data.initialise(s);
        this->n = n;
        out=data.get_col(data.col()-1);
        data=data.features();
    }
    void nn_init(){
        
        for(int i=0;i<n;i++){
            string s;
            int x;
            cout<<"Enter the number of neurons in the "<<i<<"th layer and the activation function of each layer assuming the 0th layer is the output layer"<<endl;
            cin>>x;
            getline(cin,s);
            nn.push_back(layer(x,s));
        }
        cout<<"The neural network architecture is successfully created"<<endl;
    }
    void forward(int x){
        for(int i=n-1;i>0;i--){ //going from the last layer to the first layer
            if(i==n-1){
                nn[i].linear(data.get_row(x).transpose());
                nn[i].activation();
            }
            else{
                nn[i].linear(nn[i+1].a);
                nn[i].activation();
            }
        }
        cout<<"The forward propagation was successfully \n";
    }
    void backward(){
        if(nn[0].s=="relu");
         //does something with mse
        else if(nn[0].s=="sigmoid");
         //does something with lce
    } 
};
