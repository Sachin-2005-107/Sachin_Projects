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
            w.resizer(n,1,0);
            del.resizer(1,1,0);
        }
        void activation(){
            if(s=="relu") 
            {relu();}
            else if(s=="sigmoid") {sigmoid();}
            return;
        }
        void linear(Matrix a_prev) {
        if(w.col() != a_prev.row()) {
            w.resizer(n, a_prev.row(), 0.1); 
            
        }
        l = ( w*a_prev) + b;
        this->w.printdim();
    }
};
class neural{
    
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
    vector<layer> nn;
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
            cin>>x;
            getline(cin,s);
            nn.push_back(layer(x,s));
        }
        cout<<"The neural network architecture is successfully created"<<endl;
    }
    void forward(int x){
        for(int i = n-1 ; i>=0 ; i-- ){ //going from the last layer to the first layer
            if(i==n-1){
                cout<<i<<endl;
              
                nn[i].linear(data.get_row(x).transpose());
                nn[i].activation();
               // nn[i].l.printdim();
            }
            else{
                cout<<i<<endl;
               
                nn[i].linear(nn[i+1].a);
                nn[i].activation();
                //nn[i].l.printdim();
            }
        }
        cout<<"The forward propagation was successfully \n";
    }
    void backward( int j ){
       float x=0.1;
       cout<<"OK0"<<endl;
       
        float error=LCE(j);
        nn[0].del=nn[0].a_error;
        nn[0].del.scalarmul(error);
        nn[0].del.printdim();
         cout<<"OK"<<endl;
     for(int i=1;i<10;i++){
        cout<<i<<endl;
        cout<<"OK1"<<endl;
        nn[i].del.printdim();
        nn[i-1].w.printdim();
        nn[i].a_error.printdim();
        nn[i].del=nn[i-1].w.transpose()*nn[i-1].del;
        nn[i].del=nn[i].del.habdard(nn[i].a_error);        
            if(i==n-1){
                cout<<"OK2"<<endl;
                Matrix temp=nn[i].del * data.get_row(j);
                temp.scalarmul(x);
                nn[i].w = nn[i].w - temp;
                temp=nn[i].del;
                temp.scalarmul(x);
                nn[i].b = nn[i].b - temp;
            }
            else{
                cout<<"OK3"<<endl;
                nn[i].del.printdim();
                nn[i-1].a.printdim();
                Matrix temp=nn[i].del * nn[i-1].a.transpose();
                cout<<"OK4"<<endl;
                temp.scalarmul(x);
                temp.printdim();
                nn[i].w = nn[i].w - temp;
                temp=nn[i].del;
                temp.scalarmul(x);
                nn[i].b = nn[i].b - temp;
            }
        }
       
       //cout<<"Backward was successfull"<<endl;
    } 
};
