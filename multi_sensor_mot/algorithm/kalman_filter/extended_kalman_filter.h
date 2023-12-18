#pragma once
#include <iostream>
#include <Eigen/Dense>

class ExtendedKalmanFilter {
  public:
    ExtendedKalmanFilter() : is_initialized_(false) {}

    ~ExtendedKalmanFilter() {}

    Eigen::VectorXd getX() const {
        return x_;
    }

    void initialization(Eigen::VectorXd x_in){
      x_ = x_in;
      is_initialized_ = true;
    }

    inline bool isInitialization() {
      return is_initialized_;
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

    void setR(Eigen::MatrixXd R_in){
      R_ = R_in;
    }

    Eigen::MatrixXd calculateJacobian();
    void predict();
    void measurementUpdate(const Eigen::VectorXd& z);

  private:
    bool is_initialized_;
    // state vector
    Eigen::VectorXd x_;
    // state transistion matrix
    Eigen::MatrixXd F_;
    // state convariance matrix
    Eigen::MatrixXd P_;
    // process convariance matrix
    Eigen::MatrixXd Q_;
    // jacobian convariaance matrix
    Eigen::MatrixXd H_;
    // measurement convariance matrix
    Eigen::MatrixXd R_;
};