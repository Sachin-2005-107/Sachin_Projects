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
            Matrix temp(1,1);

            temp.put_element(0,0,error);

            net[2].del = temp;
            net[2].gradient = net[2].del * net[1].a.transpose();
            net[2].weights= net[2].weights - net[2].gradient.scalarmul(eta);
            net[2].b = net[2].b - net[2].del.scalarmul(eta);

            for(int i=size-2;i>0;i--){
            temp = net[i+1].weights.transpose() * net[i+1].del;
            net[i].del = temp.hadamard(net[i].a_error);
            net[i].gradient = net[i].del * net[i-1].a.transpose();
            net[i].weights = net[i].weights - net[i].gradient.scalarmul(eta);
            net[i].b = net[i].b -net[i].del.scalarmul(eta);

            }
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
            net.push_back(Layer(5,"Leaky"));
            net.push_back(Layer(3,"Leaky"));
            net.push_back(Layer(1,"Sigmoid"));
            data.extractor(s);
            out = data.get_col(29);
            data = data.get_features();
            data.standardize();


        }
        void printer(){
           
            for(auto i:net){
                i.a.print();
                i.printweights();

            }
        }
        
        void propogation() {
            int n = data.row();
            cout<<n<<endl;

            for(int i=0;i<n;i++){
                forward(i);
                back(i);
                if (isnan(net[2].weights.get_element(0,0) )) {
                    cout<<i<<"A not a number has been encountered"<<endl;
                    break;
                }

            }
        }
        
        void predict(string s){
            test.extractor(s);
           
            trial = test.get_col(29);
            test = test.get_features();
            test.standardize();
            float error = 0;
           
             for(int i = 0; i < test.row(); i++){
                 forward_test(i);
                 float temp;
                 
                 if(net[2].a.get_element(0,0) > 0.5) temp = 1;
                 else temp = 0;

                 if(trial.get_element(i,0) != temp) error++;

             }
             cout<<net[2].a.get_element(0,0)<<endl;
             cout<<test.row()<<endl;
             cout<<error * 100 /test.row()<<endl;

        }


};
