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
      if(measurement_data_[i].sensor_type_ == MeasurementPackage::LASER){
        last_time = measurement_data_[i].timestamp_;
        double x =  measurement_data_[i].raw_measurements_(0);
        double y =  measurement_data_[i].raw_measurements_(1);
        Eigen::Vector4d X_in = Eigen::Vector4d(x, y, 0, 0);
        initialization(X_in);
        x_state_.push_back(X_in);
        continue;
      } else {
        last_time = measurement_data_[i].timestamp_;
        double rho = measurement_data_[i].raw_measurements_(0);
        double phi = measurement_data_[i].raw_measurements_(1);
        double rho_dot = measurement_data_[i].raw_measurements_(2);
        // 
        Eigen::VectorXd X_in(4, 1);
        X_in << rho * cos(phi), rho * sin(phi), rho_dot * cos(phi), rho_dot * sin(phi);
        initialization(X_in);
        x_state_.push_back(X_in);
        continue;
      }
    } else {
      current_time = measurement_data_[i].timestamp_;
      size_t delta_t = current_time - last_time;
      last_time = current_time;
      // F
      Eigen::MatrixXd F_in(4, 4);
      F_in << 1, 0, delta_t, 0,
              0, 1, 0, delta_t,
              0, 0, 1, 0,
              0, 0, 0, 1;
      kf_.setF(F_in);
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
      // predict
      kf_.predict();
      // update
      if(measurement_data_[i].sensor_type_ == MeasurementPackage::LASER){
        H_in_ = Eigen::MatrixXd(2, 4);
        H_in_ << 1, 0, 0, 0,
                 0, 1, 0, 0;
        kf_.setH(H_in_);

        lidar_R_ = Eigen::MatrixXd(2, 2);
        lidar_R_ << 0.0225, 0.0,
                    0.0, 0.0225;
        kf_.setR(lidar_R_);
        kf_.updateKF(measurement_data_[i].raw_measurements_);
      } else {
        radar_R_ = Eigen::MatrixXd(3, 3);
        radar_R_ << 0.09, 0, 0,
                    0, 0.0009, 0,
                    0, 0, 0.09;
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
