#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>


void solve5();
void solve6();

int main()
{

    solve5();
    solve6();
}

void solve5() {
    Eigen::MatrixXd mat{Eigen::MatrixXd::Random(10, 10)};

    auto topLeftCorner = mat.block<3,3>(0,0);

    topLeftCorner = Eigen::Matrix3d::Identity();

    std::cout << topLeftCorner << std::endl << std::endl;
}

void solve6() {
    Eigen::Matrix4d A;
    A << 2,-1,-1,1,          
         1,1,-2,1,          
         4,-6,2,-2,          
         3,6,-9,7;
    Eigen::Vector4d B(2, 4, 4, 9);
    Eigen::Vector4d x1 = A.colPivHouseholderQr().solve(B);
    Eigen::Vector4d x2 = A.llt().solve(B);
    Eigen::Vector4d x3 = A.ldlt().solve(B);
    // Eigen::Vector4d x4 = A.lu().solve(B);
    // Eigen::Vector4d x5 = A.bdcSvd().solve(B);
    std::cout << "The solution is \n" << 
        x1 << std::endl << std::endl <<
        x2 << std::endl << std::endl <<
        x3 << std::endl ;
}