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
    vector<vector<float>> mat;
    
    Matrix(int m,int n): m(m),n(n){

        mat.resize(m,vector<float>(n,0));

    }

    Matrix(int m, int n , int x): m(m), n(n){

        mat.resize(m , vector<float> (n , x));

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
    Matrix(){
        this->m=0;
        this->n=0;
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
              //  cout<<"Both the Matrices are compatible for multiplication"<<endl;
                Matrix prod(mat1.m,mat2.n);
                for(int i=0;i<prod.m;i++){
                    for(int j=0;j<prod.n;j++){
                        prod.mat[i][j]=0;
                        for(int k=0;k<mat1.n;k++){
                            prod.mat[i][j]+=mat1.mat[i][k]*mat2.mat[k][j];
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

       // cout<<"The transpose has been created"<<endl;

        return trans;
    }

    void printdim(){

        cout<<m<<"  "<<n<<endl;

        return;

    }
    static Matrix Identity(int n){
    //n is the dimension of the identity square matrix
    Matrix id(n,n);

    for(int i=0;i<n;i++){

        for(int j=0;j<n;j++){

            if(i==j) id.mat[i][j]=1;

            else id.mat[i][j]=0;

        }
    }

    return id;     
    }

    static Matrix Null(int n){

        Matrix id(n,n);

        for(int i=0;i<n;i++){
        
            for(int j=0;j<n;j++){
           
                id.mat[i][j]=0;
        
            }
  
        }

    return id;

    }
    void scalarmul(float lambda){

        for(auto &i:mat){
           
            for(auto &j:i){
             
                j*=lambda;

            }

        }
    }
    void resizer(int m , int n , float lambda){

        this->mat.resize(m , vector<float>(n , lambda));

        this->n=n;
        
        this->m=m;
        
        return;
    }

    Matrix habdard(Matrix a){

        if(a.m==this->m && a.n==this->n){

            Matrix x(m,n);

            for(int i=0;i<m;i++){

                for(int j=0;j<n;j++){

                    x.mat[i][j]=this->mat[i][j] * a.mat[i][j];
                }
            }
        }
        else{
            cout<<"The matrices are not compatible for elementwise operation"<<endl;
            return Matrix(0,0);
        }

    }

    static Matrix ones(int m, int n){

        return Matrix(m,n,1);


    }

    float get_element(int i , int j){

        return mat[i][j];

    }
    Matrix get_row(int i){
        Matrix ma(1,this->n);
        for(int j=0;j<this->n;j++){

            ma.mat[0][j]=this->mat[i][j];

        }

        return ma;
    }
    Matrix get_col(int i){
        Matrix ma(1,this->m);
        for(int j=0;j<this->m;j++){

            ma.mat[0][j]=this->mat[j][i];
        }
        return ma;
    }

    int row(){
        return m;
    }
    int col(){
        return n;
    }
    Matrix features(){
        Matrix x(m,n);
        for(int i=0;i<m;i++){
            for(int j=0;j<n-1;j++){
                x.mat[i][j]=this->mat[i][j];
            }
        }
        return x;
    }

    void initialise(string s){
        fstream f;
        f.open(s);
        string x;
        stringstream ss;
        getline(f,s);
        int row=0,col=0;
        while(getline(f,s)){
            ss<<s;
            if(col==0){
                while(getline(ss,x,',')) col++;
            }
            row++;
        }
        m=row;
        n=col;
        initialise_matrix(s);
    }
};


#endif
