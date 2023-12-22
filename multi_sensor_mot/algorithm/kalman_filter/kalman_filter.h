#pragma once
#include <iostream>
#include <Eigen/Dense>

namespace fusion{

class KalmanFilter {
  public:
    bool isInitialization(){
      return is_initialized_;
    }

    Eigen::VectorXd getX() const {
      return x_;
    }
    
    void initialization(Eigen::VectorXd x_in){
      x_ = x_in;
      is_initialized_ = true;
    }

    void setF(Eigen::MatrixXd F_in){
      F_ = F_in;
    }

    void setP(Eigen::MatrixXd P_in){
      P_ = P_in;
    }

    void setQ(Eigen::MatrixXd Q_in){
      Q_ = Q_in;
    }   

    void setH(Eigen::MatrixXd H_in){
      H_ = H_in;
    }    
   
    void setR(Eigen::MatrixXd R_in){
      R_ = R_in;
    }    
    
    void predict();
    void updateKF(const Eigen::VectorXd& z);
    void updateEKF(const Eigen::VectorXd& z);
    
  private:

    Eigen::MatrixXd calculateJacobian();

    bool is_initialized_;
    Eigen::VectorXd x_;
    Eigen::MatrixXd F_;
    Eigen::MatrixXd P_;
    Eigen::MatrixXd Q_;
    Eigen::MatrixXd H_;
    Eigen::MatrixXd R_;
};

} // fusion