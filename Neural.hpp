#include "Layer.hpp"
using namespace std;
class neural{
    private:
        int size;
        Matrix data,out,test,trial;
        vector<Layer> net;
        void forward(int j){
            Matrix inp = data.get_row(j);
            net[0].linear(inp);
            net[0].activation();
            net[0].deriver();
            for(int i = 1 ; i<3;i++){
                net[i].linear(net[i-1].a);
                net[i].activation();
                net[i].deriver();
            }
        }
        void forward_test(int j){
            Matrix inp = test.get_row(j);
            net[0].linear(inp);
            net[0].activation();
            net[0].deriver();
            for(int i = 1 ; i<3;i++){
                net[i].linear(net[i-1].a);
                net[i].activation();
                net[i].deriver();
            }
        }
        void back(int j){
            float eta =0.01;
            float actual = out.get_element(j,0);
            float error = net[2].a.get_element(0,0) - actual;
            Matrix temp = net[2].a_error.scalarmul(error);
            net[2].del = temp;
            net[2].gradient = temp * net[1].a.transpose();
            net[2].weights= net[2].weights - net[2].gradient.scalarmul(eta);
            net[2].b = net[2].b - net[2].del.scalarmul(eta);

            //I succesfully completed the error propogation in first layer now to the next layer
            temp = net[2].weights.transpose() * net[2].del;
            net[1].del = temp.hadamard(net[1].a_error);
            net[1].gradient = net[1].del * net[0].a.transpose();
            net[1].weights = net[1].weights - net[1].gradient.scalarmul(eta);
            net[1].b = net[1].b -net[1].del.scalarmul(eta);
            //Now to the last row
            temp = net[1].weights.transpose() * net[1].del;
            net[0].del = temp.hadamard(net[0].a_error);
            net[0].gradient = net[0].del * data.get_row(j).transpose();
            net[0].weights = net[0].weights - net[0].gradient.scalarmul(eta);
            net[0].b = net[0].b - net[0].del.scalarmul(eta);
        }
    public:
        neural(int n , string s){
            size = n; //number of layers 
            //default size is 3
            //assume that the layer is 5 3 1
            net.push_back(Layer(5));
            net.push_back(Layer(3));
            net.push_back(Layer(1));
            data.extractor(s);
            out = data.get_col(10);
            data = data.get_features();
        }
        void printer(){
           // data.print();
            //out.print();
            for(auto i:net){
                i.a.print();
                i.printweights();

            }
        }
        //Now we are going to do  propogation
        void propogation(){
            int n = data.row();
            //cout<<n<<endl;
            for(int i=0;i<n;i++){
                forward(i);
                back(i);
            }
            // for(auto i : net){
            //     i.a.print();
            //     i.errorprints();
            // }
        }
        //At this point I am very happy that the forward propogation was successful
        //Now to take on the biggest challenge i have ever faced till now
        void predict(string s){
            test.extractor(s);
            trial = test.get_col(10);
            test = test.get_features();
            float error = 0;
            //trial.print();
            for(int i = 0; i < test.row(); i++){
                forward_test(i);
                float temp;
                if(net[2].a.get_element(0,0) > 0) temp = 1;
                else temp = 0;
                
                if(trial.get_element(i,0) != temp) error++;
                
            }
            cout<<test.row()<<endl;
            cout<<error * 100 /test.row()<<endl;
        }

};