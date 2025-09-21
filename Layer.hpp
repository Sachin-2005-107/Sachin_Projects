#include "/home/darth_vader/Quant/applied/Matrix.hpp"
#include<math.h>
using namespace std;

class Layer{
    private:
        int size;
       
        float leaky_relu(float x){
            if (x > 0) return x;
            else return 0.01 * x;
        }
        float leaky_relu_der(float x){
            if (x > 0) return 1;
            else return 0.01;
        }
    public:
        Matrix l,b,a_error,del,weights,a,gradient;
        //Matrix a;
        Layer(int size){
            this->size = size;
            a.resizer(this->size , 1);
            l.resizer(this->size , 1);
            b.resizer(this->size , 1);
            a_error.resizer(this->size , 1);
            del.resizer(this->size , 1);
            weights.resizer(this->size , 1 );
            gradient.resizer(this->size , 1 );
          //  cout<<"The object has been constructed"<<endl;
        }
        void linear(Matrix a_prev){
            //assuming the matrix is a column vector
            if (this->weights.col() != a_prev.row()){
                this->weights.resizer(this->size , a_prev.row());
                this->gradient.resizer(this->size, a_prev.row());
                //weights.print();
                this->weights.weights_init();
                //weights.print();
            }
            Matrix temp =  this -> weights * a_prev;
          //  b.pd();
            this->l = temp + this -> b;
           // //this->l = temp; 
          //  l.pd();       
        }
        void activation(){
            //here i am assuming a leaky rhelu with a = 0.01
            for(int i = 0;i<l.row();i++){
                a.put_element(i , 0 , leaky_relu(l.get_element(i , 0))) ;
            }
            
        }
        void deriver(){
            for(int i = 0;i<this->l.row();i++){
                a_error.put_element(i,0,leaky_relu_der(l.get_element(i,0)));
            }
           //cout<<"Deriver is complete"<<endl;
        }
        void printweights(){
            weights.print();
        }
        void linearprints(){
            l.print();
        }
        void errorprints(){
            a_error.print();
        }



};
