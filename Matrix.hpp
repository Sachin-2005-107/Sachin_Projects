#pragma once
#include <complex>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<random>
#include<math.h>
#include<chrono>
#include<utility>
using namespace std;
int copy_matrix_count = 0;
double timer = 0.0 ;
class Matrix {
private:
    int n = 0, m = 0; //n is the no.of rows and m is the no.of columns
    vector<vector<float> > matrix;
    float eps = 1e-6f;
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
        uniform_real_distribution<float> u(1, 20);
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
        this->matrix.resize(n,vector<float>(m));

    }

    //From now on we can go into the matrix operations
    //This function returns the pointer to a transpose matrix
    Matrix transpose() {
        Matrix temp = Matrix(this->m, this->n);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                temp.matrix[j][i] = this->matrix[i][j];
            }
        }
        return temp;
    }
    //This function returns a matrix where each element is a product of a scalar lamda and the current matrix elements
    Matrix scalarmul(float lamda) {
        Matrix temp(this->n, this->m);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                temp.matrix[i][j] = this->matrix[i][j] * lamda;
            }
        }
        return temp;
    }
    friend Matrix scalar(float lambda , Matrix x){
        return x.scalarmul(lambda);
    }
    //"+' as an overloaded operator for addition of matrices
    friend Matrix operator+(Matrix a, Matrix b) {
        if (a.n == b.n && a.m == b.m) {
            Matrix temp(a.n, a.m, 0.0);
            for (int i = 0; i < a.n; i++) {
                for (int j = 0; j < a.m; j++) {
                    temp.matrix[i][j] = (a.matrix[i][j] + b.matrix[i][j]);
                }
            }
            return temp;
        }
        else {
            cout << "The matrices are not compatible for addition" << endl;
            return Matrix(1, 1, 0);
        }
    }
    //"-" as an overloaded operator for subtraction of matrices
    friend Matrix operator-(Matrix a, Matrix b) {
        if (a.n == b.n && a.m == b.m) {
            Matrix temp(a.n, a.m, 0.0);
            for (int i = 0; i < a.n; i++) {
                for (int j = 0; j < a.m; j++) {
                    temp.matrix[i][j] = (a.matrix[i][j] - b.matrix[i][j]);
                }
            }
            return temp;
        }
        else {
            cout << "The matrices are not compatible for subtraction" << endl;
            return Matrix(1, 1, 0);
        }
    }
    //"*" as an overloaded operator for multiplication of matrices
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
            temp.approximator();
            return temp;
        }
        else {
            cout << "The matrices are not compatible for multiplication" << endl;
            return Matrix(1, 1, 0.0);
        }
    }
    //This function eliminates any small epsilon where it should be zero
    void approximator(){
        for(int i = 0; i < this->row() ; i++){
            for(int j = 0; j<this -> col() ; j++){
                if(fabs(this->matrix[i][j])< 1e-4f){
                    this->matrix[i][j] = 0;
                }
            }
        }
    }
    //A function which returns hadamard or product wise element of matrices
    Matrix hadamard(Matrix a) {
        if (this->n == a.n && this->m == a.m) {
            Matrix temp(this->n, this->m);
            for (int i = 0; i < this->n; i++) {
                for (int j = 0; j < this->m; j++) {
                    temp.matrix[i][j] = this->matrix[i][j] * a.matrix[i][j];
                }
            }
            return temp;
        }
        else {
            cout << "Not compatible for hadamard product" << endl;
            return Matrix(1, 1, 0);
        }
    }

    //From now on we use get row functions which returns a row in the matrix as a column vector
    Matrix get_row(int j) {
        Matrix temp(this->m, 1);
        for (int i = 0; i < this->m; i++) {
            temp.matrix[i][0] = this->matrix[j][i];
        }
        return temp;
    }
    //From now on we use get col functions which returns a column in the matrix as a column vector
    Matrix get_col(int j) {
        Matrix temp(this->n, 1);
        for (int i = 0; i < this->n; i++) {
            temp.matrix[i][0] = this->matrix[i][j];
        }
        return temp;
    }
    //This function returns a matrix which removes the output column and returns multiple features of the dataset
    Matrix get_features() {
        Matrix temp(this->n, this->m - 1);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m - 1; j++) {
                temp.matrix[i][j] = this->matrix[i][j];
            }
        }
        return temp;
    }
    // This function returns an element at the given positions ith row jth column
    float get_element(int i, int j) {
        return this->matrix[i][j];
    }
    // This function inserts an element at the given positions
    void put_element(int i, int j, float lamda) {
        this->matrix[i][j] = lamda;
    }
    // This function returns the no.of rows in a matirx
    float row() { return n; }
    // This function returns the no.of columns in a matrix
    float col() { return m; }
    // This function prints all the elements in a matrix
    void print() {
        for (auto i: this->matrix) {
            for (auto j: i)
                cout << j << " ";
            cout << endl;
        }
        cout << endl;
    }
    // This function prints the dimensions as rows vs columns
    void pd() {
        cout << n << "  " << m << endl;
    }
    // This function creates a matrix with a path to the csv file which is a public
    void extractor(string s) {
        mat(s);
    }
    //This function extracts the principal diagonal elements of the matrix and returns a vector
    vector<float> diagonals(){
        vector<float> temp;
        int t = min(n,m);
        for(int i = 0; i<t ; i++){
            temp.push_back(this->matrix[i][i]);
        }
        return temp;
    }
    // This function standardizes the input dataset such that the range lies between 0 and 1
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
    // This function helps in initialising the Rectified Linear with HE initialisation
    void HE_init(int fanin) {
        random_device rd;
        mt19937 engine(rd());

        double stddev = sqrt(2.0/fanin);

        normal_distribution<double> u(0.0,stddev);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                this->matrix[i][j] = u(engine);
            }
        }
    }
    // This function initialises the weights using Xavier/Glorot Initalization for Sigmoid Activation
    void Xavier_init(int fanin, int  fanout) {
        random_device rd;
        mt19937 engine(rd());
        double stddev = sqrt(2.0/(fanin+fanout));
        normal_distribution<double> u(0.0,stddev);
        for (int i=0;i<n;i++) {
            for (int j=0;j<m;j++) {
                this->matrix[i][j] = u(engine);
            }
        }
    }
    friend float Norm(vector<float> *x)   ;
    friend float inner(vector<float> *x, vector<float> *y);
    Matrix grams();
    void append_col(Matrix temp){
        if(this->n == temp.row()){
            for(int i=0;i<this->n;i++){
                this->matrix[i].push_back(temp.get_element(i,0));
            }
            this->m++;
        }
        else
                cout<<"The matrices are not compatible for appending columns"<<endl;
        }
        friend void eigens(Matrix x);
        // void power_iter();

    };
    float Norm(Matrix x) {
        float sum = 0.0f;
        if(x.col()!=1) {
            cout<<"The input is not a vector so cannot find it's NORM"<<endl;
            return -1;
        }
        for(int i = 0;i<x.row();i++){
            sum+=(x.get_element(i,0) * x.get_element(i,0));
        }

        return sqrt(sum);
    }
    float inner(Matrix x,Matrix y) {
        float sum = 0.0f;
        if(x.col()!=1) {
            cout<<"The input is not a vector so cannot find it's Inner Product"<<endl;
            return -1;
        }
        else if (x.row() != y.row()){
            cout<<"The dimensions of inputs does not match cannot do inner Product"<<endl;
        }
        for(int i = 0;i<x.row();i++){
            sum+=(x.get_element(i,0) * y.get_element(i,0));
        }

        return sum;
    }
    //This function returns an orthonormal matrix for the given matrix using gram schmidt orthogonolization algorithm
    Matrix Matrix :: grams(){
        Matrix temp,gram;
        temp = this->get_col(0);
        for(int i = 1;i<this->m;i++){
            Matrix s,t;
            s = this->get_col(i);
            t.resizer(s.row(),1);
            for(int j=0; j < i ; j++){
                float something = inner(temp.get_col(j),s)/inner(temp.get_col(j),temp.get_col(j));
                Matrix y = temp.get_col(j);
                t =  t + scalar(something,temp.get_col(j));

            }
            temp.append_col(s-t);
        }
        for(int i = 0; i< temp.col();i++){
            float norm = Norm(temp.get_col(i));
            for(int j = 0 ; j < temp.row(); j++){
                float temps = temp.get_element(j,i);
                temp.put_element(j,i,temps/norm);
            }
        }
        return temp;
    }
    //This function returns the Eigen value Diagonal Matrix of the
    void eigens(Matrix x){
        Matrix q,r,eigenvec(x.row(),x.col());
        for(int i = 0 ; i < eigenvec.row() ; i++){
        for(int j = 0 ; j < eigenvec.col() ; j++){
            if( i == j) eigenvec.put_element(i,j,1.0);
            else eigenvec.put_element(i,j,0.0);
        }
    }
    for(int i = 0; i < 1000 ; i++){
        q = x.grams();
        eigenvec = eigenvec * q ;
        r = q.transpose() * x;
        x = r * q;
        if(i%100==0) cout<<i<<endl;
    }

   // x.print();
        cout<<endl<<endl;
        //eigenvec.print();
    }
    void eigens(Matrix x, float lambda){
        Matrix q,r,eigenvec(x.row(),x.col());
        for(int i = 0 ; i < eigenvec.row() ; i++){
            for(int j = 0 ; j < eigenvec.col() ; j++){
                if( i == j) eigenvec.put_element(i,j,1.0);
                else eigenvec.put_element(i,j,0.0);
            }
        }
        for(int i = 0; i < 100000 ; i++){
            q = x.grams();
            eigenvec = eigenvec * q ;
            r = q.transpose() * x;
            x = r * q;
            double y = x.get_element(0,0);
            // if (fabs(lambda - y)/ lambda  < 5e-6f) {
            //     lambda = y;
            //     cout<<"Converge in "<<i<<" steps with an error"<<1e-6f<<endl;
            //     break;
            // }
            if(i%10000==0) cout<<i<<endl;
        }

       // x.print();
        cout<<endl<<endl;
       // eigenvec.print();
    }

    // //This function performs a power iteration method for findig the dominant eigen value and eigen vector for the given matrix
    void power_iter(Matrix A) {
        Matrix x0(A.row(),1), temp(A.row(),1);
        x0.weights_init();
        double lambda;
        for (int i=0; i<100;i++) {
            temp = A * x0;
            lambda = temp.get_element(0,0) / x0.get_element(0,0);
            x0  = temp.scalarmul(1/Norm(temp));

        }
        x0.print();
        cout<<"The dominant eigen value is "<< lambda<<endl;
    }
    bool is_diagonal(Matrix A) {
        float sum = 0;
        for (int i = 0 ; i <A.row() ; i++) {
            for (int j = 0 ; j < A.col() ; j++) {
                if ( i == j) continue;
                else if (fabs(A.get_element(i,j)) > sum) sum = A.get_element(i,j);

            }
        }
        return fabs(sum) < 1e-6f;
    }
    float power_iter_val(Matrix A) {
        Matrix x0(A.row(),1), temp(A.row(),1);
        x0.weights_init();
        double lambda = 1.0;
        for (int i=0; i<100;i++) {
            temp = A * x0;
            double y = temp.get_element(0,0) / x0.get_element(0,0);
            x0  = temp.scalarmul(1/Norm(temp));
            lambda = y;
            // if (fabs(lambda - y)/ lambda  < 1e-6f) {
            //     lambda = y;
            //     cout<<"Converge in "<<i<<" steps with an error"<<1e-6f<<" "<<y<<endl;
            //     return lambda;
            // }
            // else {
            //      lambda = y;
            // }


        }

        return lambda;
    }
     // Matrix Identity(int m);
     Matrix Identity(int m) {
         Matrix A(m, m,0.0);
         for (int i = 0; i < m; i++) {
             A.put_element(i,i,1.0);
         }
         return A;
     }
     //This function will hopefully return the q r decomposition of the input Matrix A
     Matrix get_sub_Matrix(int a,int b,int c, int d,Matrix A);
     Matrix put_sub_Matrix(int a,int b,int c, int d,Matrix A,Matrix B);
     pair<Matrix,Matrix> Householder(Matrix x) {
         // x.print();
         int m = x.row(), n = x.col();
         //cout<<n<<endl;
         Matrix Q = Identity(m);
         //Matrix R = x;
         for (int j = 0 ; j < n ; j++){
             //cout<<j<<endl;
             Matrix H(m-j , 1); //The Householder Matrix Declaration
             for (int i = j ; i < m ; i ++) {
                 H.put_element(i-j,0,x.get_element(i,j));
             }
             float y = Norm(H);
           //  H.print();
             int s;
             if (H.get_element(0,0) > 0) s = -1;
             else if (H.get_element(0,0) < 0) s = 1;
             else s = 0;
             float  u = H.get_element(0,0) - ( s * y);
             if (u == 0) {
               //  cout<<"U is zero "<<endl;
                 continue;
             }

             H = H.scalarmul(1/(u));
             //H.print();
             u = s*u/y;
             u*=-1.0;
             H.put_element(0,0,1.0f);
             Matrix W =  H * H.transpose();
             W = W.scalarmul(u);

             Matrix I = Identity(m-j);
             Matrix temp = I - W;

             I = Identity(m);
             Matrix b = put_sub_Matrix(j,j,m,n,I, temp);
             Q = Q * b;
             //b.print();
         }
         Matrix R = Q.transpose() * x;
         //Q.print();
        // R.print();

         return make_pair(R,Q);

     }
     Matrix get_sub_Matrix(int a, int b , int c , int d,Matrix B) {//(a,b) is the starting element and (c,d) is the ending element
         //cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
         Matrix A(abs(c-a),abs(d-b));
         for (int i = a; i < c ; i++) {

             for (int j = b; j < d ; j++) {

                 A.put_element(i-a,j-b,B.get_element(i,j));
             }
         }
         //A.print();
         return A;
     }
     Matrix put_sub_Matrix(int a, int b , int c , int d,Matrix A,Matrix B) {//(a,b) is the starting element and (c,d) is the ending element


         for (int i = a; i < c ; i++) {

             for (int j = b; j < d ; j++) {

                 A.put_element(i,j,B.get_element(i-a,j-b));
             }
         }
         //A.print();
         return A;
     }
     pair<vector<float>,Matrix> eigen(Matrix x){
         Matrix q,r,eigenvec;
         eigenvec = Identity(x.col());
         float lambda = 1.0f;
         for(int i = 0; i < 5000; i++){
             pair<Matrix,Matrix> p = Householder(x);
             r= p.first;
             q= p.second;
             x = r * q;
             eigenvec = eigenvec * q;


             // if (i>100 && i%10==0 &&is_diagonal(x) ) {
             //
             //     cout<<"Converge in "<<i<<" steps "<<endl;//"with an error"<<1e-6f<<endl;

             //     break;
             // }
             // if(i%100==0) cout<<i<<endl;
         }
         vector<float> eigen = x.diagonals();
         float sum = 0.0f;
         for (auto i:eigen) sum+=i;
         for (auto &i:eigen) i/=sum;
         return make_pair(eigen,eigenvec);

     }
     //A function which performs Principal Component Analysis
     void PCA(Matrix x) {
         x.standardize();
         Matrix cov  = x.transpose() * x;
         cout<<"Covariance is found"<<endl;
         pair<vector<float> , Matrix> e = eigen(cov);
        for (auto i : e.first) cout<<i<<"  ";
         cout<<endl<<endl;
         e.second.print();
         int var_max_ind = 0;
         float sum = 0;
         for ( auto i: e.first) {
             sum += i;
             if (sum > 0.95f) {
                 var_max_ind++;
                 break;
             }
             var_max_ind++;
         }
         cout<<var_max_ind<<endl;
     }


