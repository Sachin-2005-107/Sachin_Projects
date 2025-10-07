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
            if(net[2].s=="Leaky")
            temp = net[2].a_error.scalarmul(error);
            else{
            temp.put_element(0,0,error);
            }


            net[2].del = temp;
            net[2].gradient = temp * net[1].a.transpose();
            net[2].weights= net[2].weights - net[2].gradient.scalarmul(eta);
            net[2].b = net[2].b - net[2].del.scalarmul(eta);

            //I succesfully completed the error propogation in first layer now to the next layer
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
            net.push_back(Layer(1,"Leaky"));
            data.extractor(s);
            out = data.get_col(10);
            data = data.get_features();
            data.standardize();


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
            cout<<n<<endl;

            for(int i=0;i<n;i++){
                forward(i);
                back(i);
                if (i==1) {
                    net[2].printweights();
                    net[1].printweights();
                    net[0].printweights();
                }

            }

            net[2].a.print();

            // for(auto i : net){
            //     i.a.print();
            //     i.errorprints();
            // }
        }
        //At this point I am very happy that the forward propogation was successful
        //Now to take on the biggest challenge i have ever faced till now
        void predict(string s){
            test.extractor(s);
           //
            trial = test.get_col(10);
            test = test.get_features();
            test.standardize();
            float error = 0;
           // trial.print();
             for(int i = 0; i < 100; i++){
                 forward_test(i);
                 float temp;
                 //cout<<net[2].a.get_element(0,0)<<" "<<trial.get_element(i,0)<<endl;
                 if(net[2].a.get_element(0,0) > 0.5) temp = 1;
                 else temp = 0;

                 if(trial.get_element(i,0) != temp) error++;

             }
            //cout<<net[2].a.get_element(0,0)<<endl;
             cout<<test.row()<<endl;
             cout<<error * 100 /100<<endl;
            net[2].printweights();
            net[1].printweights();
            net[0].printweights();
        }
    // void consolidation() {
    //         for
    //     }

};
