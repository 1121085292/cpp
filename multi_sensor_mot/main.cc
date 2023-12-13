#include <iostream>

#include "algorithm/kalman_filter/kalman_filter.h"
#include "interface/sensor_measurement.h"

int main(){
  size_t last_time, current_time;
  KalmanFilter kf;
  std::vector<MeasurementPackage> measurement_data;

  // P
  Eigen::MatrixXd P_in(4, 4);
  P_in << 1.0 ,0.0, 0.0, 0.0,
          0.0, 1.0, 0.0, 0.0,
          0.0, 0.0, 100.0, 0.0,
          0.0, 0.0, 0.0, 100.0;
  kf.setP(P_in);
  // Q
  Eigen::Matrix4d Q_in = Eigen::Matrix4d::Identity();
  kf.setQ(Q_in);
  // H
  Eigen::MatrixXd H_in(2, 4);
  H_in << 1.0, 0.0, 0.0, 0.0,
          0.0, 1.0, 0.0, 0.0;
  kf.setH(H_in);
  // R
  Eigen::MatrixXd R_in(2, 2);
  R_in << 0.0225, 0.0,
          0.0, 0.0225;
  kf.setR(R_in);

  if(!getLidarData(measurement_data)){
    std::cout << "measurement data load failed" << std::endl;
  }

  for(size_t i = 0; i < measurement_data.size(); ++i){
    if(!kf.isInitialized()){
      last_time = current_time;
      // 创建4维0矩阵，前2位用x,y填充
      Eigen::Vector4d x_in = Eigen::Vector4d::Zero();
      x_in.head<2>() = measurement_data[i].raw_measurements_;
      kf.initialization(x_in);
    }
    // F
    size_t delta_t = current_time - last_time;
    last_time = current_time;
    Eigen::Matrix2d tmp;
    tmp << delta_t, 0,
            0, delta_t; 
    Eigen::Matrix4d F_in = Eigen::Matrix4d::Identity();
    F_in.block<2, 2>(0, 2) = tmp;
    kf.setF(F_in);
    // predict
    kf.pridection();
    // measurement
    Eigen::VectorXd z(2, 1);
    z = measurement_data[i].raw_measurements_;
    kf.measurementUpdate(z);
    // state x
    Eigen::VectorXd x_out = kf.getX();
    std::cout << "kf output state x:" << x_out(0) << ","
            << "y: " << x_out(1) <<std::endl;
  }
}