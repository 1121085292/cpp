#include <iostream>
#include <Eigen/Dense>

int main(){
  using namespace Eigen;
  using namespace std;
  // Eigen::Matrix4d a;
  // a << 1, 2, 3, 4,
  //      5, 6, 7, 8,
  //      9, 0, 0, 0,
  //      0, 0, 0, 0;
  // Eigen::Matrix4d b = Eigen::Matrix4d::Ones();
  // // a.block<2, 3>(2, 1) = b.block(2, 1, 2, 3);                            
  // std::cout << a.col(2) << std::endl;
  MatrixXi mat(3,3); 
  mat << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;
  cout << "Here is the matrix mat:\n" << mat << endl;
  
  // This assignment shows the aliasing problem
  mat.bottomRightCorner(2,2) = mat.topLeftCorner(2,2);
  cout << "After the assignment, mat = \n" << mat << endl;
}