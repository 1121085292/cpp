/*
  lidar & radar sensor fusion
  for(data){
    if(first frame){
      if(lidar){
        lidar init
      } else if(radar){
        radar init
      }
    } else {
      predict
      if(lidar){
        kf
      } else {
        ekf
      }
    }
  }
*/
#include "fusion_system/motion_fusion/motion_fusion.h"

namespace fusion{

MotionFusion::MotionFusion()
{
  is_initialzed_ = false;

  lidra_H_ = Eigen::MatrixXd(2, 4);
  lidra_H_ << 1, 0, 0, 0,
              0, 1, 0, 0;
  
  lidar_R_ = Eigen::MatrixXd(2, 2);
  lidar_R_ << 0.0225, 0.0,
              0.0, 0.0225;

  radar_R_ = Eigen::MatrixXd(3, 3);
  radar_R_ << 0.09, 0, 0,
              0, 0.0009, 0,
              0, 0, 0.09;
}

void MotionFusion::motionFusion()
{
  // get measurement
  if(!getMeasurementData(measurement_data_)){
    std::cout << "get measurement data failed" << std::endl;
    return;
  }
  size_t last_time, current_time;
  // kf fusion
  for(int i = 0; i < measurement_data_.size(); ++i){
    // init
    if(!isInitialization()){
      Eigen::Vector4d X_in;
      if(measurement_data_[i].sensor_type_ == MeasurementPackage::LASER){
        double x =  measurement_data_[i].raw_measurements_(0);
        double y =  measurement_data_[i].raw_measurements_(1);
        X_in = Eigen::Vector4d(x, y, 0, 0);
        x_state_.push_back(X_in);
      } else {
        double rho = measurement_data_[i].raw_measurements_(0);
        double phi = measurement_data_[i].raw_measurements_(1);
        double rho_dot = measurement_data_[i].raw_measurements_(2);
        
        X_in << rho * cos(phi), rho * sin(phi), rho_dot * cos(phi), rho_dot * sin(phi);
        x_state_.push_back(X_in);
      }
      
      // 避免运算时0被做除数
      X_in(0) = X_in(0) < 0.001 ? 0.001 : X_in(0);
      X_in(1) = X_in(1) < 0.001 ? 0.001 : X_in(1);

      // P
      Eigen::MatrixXd P_in(4, 4);
      P_in << 1.0 ,0.0, 0.0, 0.0,
              0.0, 1.0, 0.0, 0.0,
              0.0, 0.0, 100.0, 0.0,
              0.0, 0.0, 0.0, 100.0;
      kf_.setP(P_in);
      // Q
      Eigen::Matrix4d Q_in = Eigen::Matrix4d::Identity();
      kf_.setQ(Q_in);

      last_time = measurement_data_[i].timestamp_;
      initialization(X_in);
      continue;
    } else {
      // 微秒转换为秒
      size_t delta_t = (current_time - last_time) / 1000000;
      last_time = current_time;
      // F
      Eigen::MatrixXd F_in(4, 4);
      F_in << 1, 0, delta_t, 0,
              0, 1, 0, delta_t,
              0, 0, 1, 0,
              0, 0, 0, 1;
      kf_.setF(F_in);
      // predict
      kf_.predict();
      // update
      if(measurement_data_[i].sensor_type_ == MeasurementPackage::LASER){
        kf_.setH(lidra_H_);
        kf_.setR(lidar_R_);
        kf_.updateKF(measurement_data_[i].raw_measurements_);
      } else {
        kf_.setR(radar_R_);
        kf_.updateEKF(measurement_data_[i].raw_measurements_);
      }
      x_state_.push_back(kf_.getX());
    }
  }
  if(writeCSV("kf_fusion.csv", x_state_)){
    std::cout << "Write OK" << std::endl;
  }
}

} // fusion
