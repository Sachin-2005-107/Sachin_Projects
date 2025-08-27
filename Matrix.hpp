#ifndef matrix
#define matrix

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Matrix {
    int m, n; // m = rows, n = columns
    vector<vector<float>> mat;
    void print_matrix() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }
    void initialise_matrix(string s) {
        ifstream f(s);
        string t, v;
        getline(f, t); // skip header row

        for (int i = 0; i < m; i++) {
            if (getline(f, t)) {
                stringstream ss(t);
                for (int j = 0; j < n; j++) {
                    if (getline(ss, v, ',')) {
                        mat[i][j] = static_cast<float>(stof(v));
                    }
                }
            }
        }
        cout << "The matrix has been initialised." << endl;
    }

public:
    void print_matrix_5rows(){
        for(int i=0;i<5;i++){
            for(int j=0;j<mat[0].size();j++){
                cout<<mat[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    Matrix(int m,int n): m(m),n(n){
        mat.resize(m,vector<float>(n));
    }
    Matrix(string s) {
        ifstream f(s);
        if (!f.is_open()) {
            cerr << "Error opening file." << endl;
            return;
        }

        string t, v;
        int cols = 0, rows = 0;

        if (getline(f, t)) { // header
            stringstream ss(t);
            while (getline(ss, v, ',')) cols++;
        }

        while (getline(f, t)) rows++;

        m = rows;
        n = cols;
        mat.resize(m, vector<float>(n, 0));

        cout << m << " rows, " << n << " columns" << endl;

        f.close();
        initialise_matrix(s);
    }
    friend Matrix operator +(Matrix mat1 ,Matrix mat2){
         if(mat1.m==mat2.m && mat1.n==mat2.n) {
         cout<<"They are compatible for addition"<<endl;
            Matrix m(mat1.m,mat1.n);
        for(int i=0;i<mat1.mat.size();i++){
            for(int j=0;j<mat1.mat[0].size();j++){
                m.mat[i][j]=mat1.mat[i][j]+mat2.mat[i][j];
            }
        }
        return m;
        }
        else {
        cout<<"The matrices are not compatible for subtraction"<<endl;
        return Matrix(0,0);
        }
    }
      friend Matrix operator -(Matrix mat1 ,Matrix mat2){
         if(mat1.m==mat2.m && mat1.n==mat2.n) {
         cout<<"They are compatible for addition"<<endl;
            Matrix m(mat1.m,mat1.n);
        for(int i=0;i<mat1.mat.size();i++){
            for(int j=0;j<mat1.mat[0].size();j++){
                m.mat[i][j]=mat1.mat[i][j]- mat2.mat[i][j];
            }
        }
        return m;
        }
        else {
        cout<<"The matrices are not compatible for subtraction"<<endl;
        return Matrix(0,0);
        }
    }
      friend Matrix operator *(Matrix mat1,Matrix mat2){
            if(mat1.n==mat2.m){
                cout<<"Both the Matrices are compatible for multiplication"<<endl;
                Matrix prod(mat1.m,mat2.n);
                for(int i=0;i<prod.m;i++){
                    for(int j=0;j<prod.n;j++){
                        prod.mat[i][j]=0;
                        for(int k=0;k<mat1.n;k++){
                            prod.mat[i][j]+=mat1.mat[i][k]+mat2.mat[k][j];
                        }
                    }
                }
                return prod;
            }
            else{
                cout<<"The matrices are not compatible for multiplication"<<endl;
                return Matrix(0,0);
            }
      }
    Matrix transpose(){
        Matrix trans(this->n,this->m);
        for(int i=0;i<this->m;i++){
            for(int j=0;j<this->n;j++){
                trans.mat[j][i]=this->mat[i][j];
            }
        }
        cout<<"The transpose has been created"<<endl;
        return trans;
    }
    void printdim(){
        cout<<m<<"  "<<n<<endl;
        return;
    }
};

#endif
