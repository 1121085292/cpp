#include "extended_kalman_filter.h"

Eigen::MatrixXd ExtendedKalmanFilter::calculateJacobian()
{
  Eigen::MatrixXd Hj(3, 4);
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

void ExtendedKalmanFilter::predict()
{
  x_ = F_ * x_;
  P_ = F_ * P_ * F_.transpose() + Q_;
}

void ExtendedKalmanFilter::measurementUpdate(const Eigen::VectorXd& z)
{
  // y = z - h(x)
  double rho = std::sqrt(x_(0) * x_(0) + x_(1) * x_(1));
  double theta = atan2(x_(1), x_(0));
  double rho_dot = (x_(0) * x_(2) + x_(1) * x_(3)) / rho;
  Eigen::VectorXd h(3, 1);
  h << rho, theta, rho_dot;
  std::cout << "h: " << h << std::endl;

  Eigen::VectorXd y = z - h;
  // s = h * p * ht + R
  H_ = calculateJacobian();
  auto s = H_ * P_ * H_.transpose() + R_;
  // k = p * ht / s
  auto k = P_ * H_.transpose() * s.inverse();
  // x = x + k * y
  x_ = x_ + k * y;
  // p = (i - k * h) * p
  Eigen::MatrixXd I = Eigen::MatrixXd::Identity(x_.size(), x_.size());
  P_ = (I - k * H_) * P_;
}
