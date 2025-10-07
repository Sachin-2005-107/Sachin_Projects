#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<random>
using namespace std;

class Matrix {
private:
    int n = 0, m = 0; //n is the no.of rows and m is the no.of columns
    vector<vector<float> > matrix;
    //This function reads the csv file and converts it into a matrix
    void mat(string s) {
        fstream f;
        f.open(s);
        getline(f, s); //reads and ignores the header files
        while (getline(f, s)) {
            this->n++;
            stringstream ss(s);
            string t;
            vector<float> temp;
            if (this->m == 0) {
                while (getline(ss, t, ',')) {
                    this->m++;
                    temp.push_back(stof(t));
                }
                matrix.push_back(temp);
            } else {
                while (getline(ss, t, ',')) {
                    temp.push_back(stof(t));
                }
                this->matrix.push_back(temp);
            }
        }
        f.close();
    }

public:
    //All the constructors 
    //This constructor takes in two integers as input
    Matrix(int n, int m) {
        this->n = n;
        this->m = m;
        this->matrix.resize(n, vector<float>(m, 0.0));
    }

    //This constructor takes in the dimensions of the matrix and the default value
    Matrix(int n, int m, float lamda) {
        this->n = n;
        this->m = m;
        this->matrix.resize(n, vector<float>(m, lamda));
    }

    //This constructor takes the path to a csv file as input and processes it into a matrix
    Matrix(string s) {
        mat(s);
    }

    Matrix() {
        //cout<<"Empty constructor"<<endl;
    }

    //This function creates a random variable filled weights matrix
    void weights_init() {
        random_device rd;
        mt19937 engine(rd());
        uniform_real_distribution<double> u(-0.01, .01);
        //  cout<<n<<" "<<matrix.size()<<endl;
        // cout<<m<<" "<<matrix[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                this->matrix[i][j] = u(engine);
            }
        }
    }

    //This functions helps us to resize the existing matrix to the given input dimensions
    void resizer(int n, int m) {
        this->matrix.clear();
        this->n = n;
        this->m = m;
        for (int i = 0; i < n; i++)
            matrix.push_back(vector<float>(m, 0));
        // cout<<n<<" "<<matrix.size()<<endl;
        // cout<<m<<" "<<matrix[0].size()<<endl;
    }

    //From now on we can go into the matrix operations
    Matrix transpose() {
        Matrix temp(this->m, this->n);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                temp.matrix[j][i] = this->matrix[i][j];
            }
        }
        return temp;
    }

    Matrix scalarmul(float lamda) {
        Matrix temp(this->n, this->m);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                temp.matrix[i][j] = this->matrix[i][j] * lamda;
            }
        }
        return temp;
    }

    friend Matrix operator+(Matrix a, Matrix b) {
        if (a.n == b.n && a.m == b.m) {
            Matrix temp(a.n, a.m, 0.0);
            for (int i = 0; i < a.n; i++) {
                for (int j = 0; j < a.m; j++) {
                    temp.matrix[i][j] = (a.matrix[i][j] + b.matrix[i][j]);
                }
            }
            return temp;
        } else {
            cout << "The matrices are not compatible for addition" << endl;
            return Matrix(1, 1, 0);
        }
    }

    friend Matrix operator-(Matrix a, Matrix b) {
        if (a.n == b.n && a.m == b.m) {
            Matrix temp(a.n, a.m, 0.0);
            for (int i = 0; i < a.n; i++) {
                for (int j = 0; j < a.m; j++) {
                    temp.matrix[i][j] = (a.matrix[i][j] - b.matrix[i][j]);
                }
            }
            return temp;
        } else {
            cout << "The matrices are not compatible for subtraction" << endl;
            return Matrix(1, 1, 0);
        }
    }

    friend Matrix operator*(Matrix a, Matrix b) {
        if (a.m == b.n) {
            Matrix temp(a.n, b.m);
            for (int i = 0; i < a.n; i++) {
                for (int j = 0; j < b.m; j++) {
                    for (int k = 0; k < b.n; k++) {
                        temp.matrix[i][j] += (a.matrix[i][k] * b.matrix[k][j]);
                    }
                }
            }
            return temp;
        } else {
            cout << "The matrices are not compatible for multiplication" << endl;
            return Matrix(1, 1, 0.0);
        }
    }

    Matrix hadamard(Matrix a) {
        if (this->n == a.n && this->m == a.m) {
            Matrix temp(this->n, this->m);
            for (int i = 0; i < this->n; i++) {
                for (int j = 0; j < this->m; j++) {
                    temp.matrix[i][j] = this->matrix[i][j] * a.matrix[i][j];
                }
            }
            return temp;
        } else {
            cout << "Not compatible for hadamard product" << endl;
            return Matrix(1, 1, 0);
        }
    }

    //From now on we use get functions which returns everything as a column vector
    Matrix get_row(int j) {
        Matrix temp(this->m, 1);
        for (int i = 0; i < this->m; i++) {
            temp.matrix[i][0] = this->matrix[j][i];
        }
        return temp;
    }

    Matrix get_col(int j) {
        Matrix temp(this->n, 1);
        for (int i = 0; i < this->n; i++) {
            temp.matrix[i][0] = this->matrix[i][j];
        }
        return temp;
    }

    Matrix get_features() {
        Matrix temp(this->n, this->m - 1);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m - 1; j++) {
                temp.matrix[i][j] = this->matrix[i][j];
            }
        }
        return temp;
    }

    float get_element(int i, int j) {
        return this->matrix[i][j];
    }

    void put_element(int i, int j, float lamda) {
        this->matrix[i][j] = lamda;
    }

    float row() { return n; }
    float col() { return m; }

    void print() {
        for (auto i: this->matrix) {
            for (auto j: i)
                cout << j << " ";
            cout << endl;
        }
        cout << endl;
    }

    void pd() {
        cout << n << "  " << m << endl;
    }

    void extractor(string s) {
        mat(s);
    }
    void standardize() {


        vector<float> means(this->m, 0.0f);
        vector<float> std_devs(this->m, 0.0f);


        for (int i = 0; i < this->m; i++) {
            float sum = 0.0f;
            for (int j = 0; j < this->n; j++) {
                sum += this->matrix[j][i];
            }
            means[i] = sum / this->n;
        }


        for (int i = 0; i < this->m; i++) {
            float squared_diff_sum = 0.0f;
            for (int j = 0; j < this->n; j++) {
                squared_diff_sum += (this->matrix[j][i] - means[i]) * (this->matrix[j][i] - means[i]);
            }
            float variance = squared_diff_sum / (this->n - 1); // Use n-1 for sample standard deviation
            std_devs[i] = sqrt(variance);
        }


        for (int i = 0; i < this->m; i++) {

            if (std_devs[i] > 0) {
                for (int j = 0; j < this->n; j++) {
                    this->matrix[j][i] = (this->matrix[j][i] - means[i]) / std_devs[i];
                }
            }
        }
    }
void HE_init(int fanin) {
        random_device rd;
        mt19937 engine(rd());
        cout<<"Fanin"<<fanin<<endl;
        double stddev = sqrt(2.0/fanin);
        cout<<"StdDev"<<stddev<<endl;
        normal_distribution<double> u(0.0,stddev);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                this->matrix[i][j] = u(engine);
            }
        }
    }

};
