#include "/home/darth_vader/Quant/applied/Matrix.hpp"
using namespace std;

class Layer {
private:

    float leaky_relu(float x) {
        if (x > 0) return x;
        else return 0.01 * x;
    }

    float leaky_relu_der(float x) {
        if (x > 0) return 1;
        else return 0.01;
    }

    float sigmoid(float x) {
        // Inside your activation function in the Layer class
        if (x<-50)
            return 0.0;
        else
         return 1.0 / (1.0 + exp(-x));
    }

    float sigmoid_der(float x) {
        return x * (1 - x);
    }

public:
    int size;
    string s;
    Matrix l, b, a_error, del, weights, a, gradient;

    Layer(int size, string t) {

        this->size = size;
        this->s = t;
        a.resizer(this->size, 1);
        l.resizer(this->size, 1);
        b.resizer(this->size, 1);
        b.weights_init();
        a_error.resizer(this->size, 1);
        del.resizer(this->size, 1);
        weights.resizer(this->size, 1);
        gradient.resizer(this->size, 1);

    }

    void linear(Matrix a_prev) {

        if (this->weights.col() != a_prev.row()) {
            this->weights.resizer(this->size, a_prev.row());
            this->gradient.resizer(this->size, a_prev.row());
            int n = weights.row();
            int m = weights.col();
            if (this->s=="Leaky")
            weights.HE_init(m);
            else if (this -> s == "Sigmoid" )
            weights.Xavier_init(m,n);

        }

        Matrix temp = this->weights * a_prev;

        this->l = temp + this->b;

    }


    void activation() {

        for (int i = 0; i < l.row(); i++) {
            if (this->s == "Leaky")
                a.put_element(i, 0, leaky_relu(l.get_element(i, 0)));
            else if (this->s == "Sigmoid")
                a.put_element(i, 0, sigmoid(l.get_element(i, 0)));
        }
    }

    void deriver() {
        for (int i = 0; i < this->l.row(); i++) {
            if (this->s == "Leaky")
                a_error.put_element(i, 0, leaky_relu_der(l.get_element(i, 0)));
            else if (this->s == "Sigmoid")
                a_error.put_element(i, 0, sigmoid_der(a.get_element(i, 0)));


        }
    }

    void printweights() {
        weights.print();
    }

    void linearprints() {
        l.print();
    }

    void errorprints() {
        a_error.print();
    }
};
