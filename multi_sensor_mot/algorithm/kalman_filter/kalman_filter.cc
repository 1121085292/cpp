#include "algorithm/kalman_filter/kalman_filter.h"

void fusion::KalmanFilter::predict()
{
  // x = f * x + u
  x_ = F_ * x_;
  // p = f * p * ft + q
  P_ = F_ * P_ * F_.transpose() + Q_;
}

void fusion::KalmanFilter::updateKF(const Eigen::VectorXd &z)
{
  Eigen::VectorXd y = z - H_ * x_;
  Eigen::MatrixXd s = H_ * P_ * H_.transpose() + R_;
  Eigen::MatrixXd k = P_ * H_.transpose() * s.inverse();
  x_ = x_ + k * y;
  Eigen::MatrixXd I = Eigen::MatrixXd::Identity(x_.size(), x_.size());
  P_ = ( I - k *H_) * P_;
}

void fusion::KalmanFilter::updateEKF(const Eigen::VectorXd &z)
{
  // hx
  double c1 = x_(0) * x_(0) + x_(1) * x_(1);
  double c2 = std::sqrt(c1);
  double c3 = x_(0) * x_(2) + x_(1) * x_(3);
  double rho = c2;
  double phi = std::atan2(x_(1), x_(0));
  double rho_dot = c3 / c2;
  Eigen::VectorXd hx(3, 1);
  hx << rho, phi, rho_dot;
  // y
  Eigen::VectorXd y = z - hx;

  H_ = calculateJacobian();

  Eigen::MatrixXd s = H_ * P_ * H_.transpose() + R_;
  Eigen::MatrixXd k = P_ * H_.transpose() * s.inverse();
  x_ = x_ + k * y;
  Eigen::MatrixXd I = Eigen::MatrixXd::Identity(x_.size(), x_.size());
  P_ = ( I - k *H_) * P_; 
}

Eigen::MatrixXd fusion::KalmanFilter::calculateJacobian()
{
  Eigen::MatrixXd Hj = Eigen::MatrixXd::Identity(3, 4);
  // get state parammetes
  float x = x_(0);
  float y = x_(1);
  float vx = x_(2);
  float vy = x_(3);

  float c1 = x * x + y * y;
  float c2 = std::sqrt(c1);
  float c3 = c1 * c2;
  float c4 = vx * y - vy * x;
  float c5 = vy * x - vx * y;

  if(std::fabs(c1) < 0.001){
    return Hj;
  }

  Hj << (x/c2), (y/c2), 0, 0,
       -(y/c1), (x/c1), 0, 0,
       y*c4/c3, x*c5/c3, x/c2, y/c2;
  return Hj;
  
}
