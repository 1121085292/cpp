#pragma once

#include <Eigen/Dense>

class KalmanFilter {
  public:
    KalmanFilter() : is_initialized_(false) {}
    ~KalmanFilter();
    Eigen::VectorXd getX() const {
      return x_;
    }
    bool isInitialized(){
      return is_initialized_;
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
    void pridection(){
      x_ = F_ * x_;
      auto Ft = F_.transpose();
      P_ = F_ * P_ * Ft + Q_;
    }
    void measurementUpdate(const Eigen::VectorXd& z){
      Eigen::VectorXd y = z - H_ * x_;
      Eigen::MatrixXd S = H_ * P_ * H_.transpose() + R_;
      Eigen::MatrixXd K = P_ * H_.transpose() * S.inverse();
      x_ = x_ + K * y;
      Eigen::MatrixXd I = Eigen::MatrixXd::Identity(x_.size(), x_.size());
      P_ = (I - K * H_) *P_;
    }
  private:
  // flag of initialization
  bool is_initialized_;
  // state vector
  Eigen::VectorXd x_;
  // state transistion matrix
  Eigen::MatrixXd F_;
  // state convariance matrix
  Eigen::MatrixXd P_;
  // process convariance matrix
  Eigen::MatrixXd Q_;
  // measurement matrix
  Eigen::MatrixXd H_;
  // measurement convariance matrix
  Eigen::MatrixXd R_;
};