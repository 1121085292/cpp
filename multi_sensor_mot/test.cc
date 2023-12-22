/*  test
    lidar: kf 
    radar: ekf
*/

#include <iostream>
#include <fstream>

#include "algorithm/kalman_filter/KF.h"
#include "algorithm/kalman_filter/EKF.h"
#include "measurement/sensor_measurement.h"

void testKF(){
  // measurement data
  size_t last_time, current_time;
  KalmanFilter kf;
  std::vector<MeasurementPackage> measurement_data;
  // output state
  std::vector<Eigen::VectorXd> x_state;
 
  if(!getMeasurementData(measurement_data)){
    std::cout << "measurement data load failed" << std::endl;
  }

  for(size_t i = 0; i < measurement_data.size(); ++i){
    if(measurement_data[i].sensor_type_ == MeasurementPackage::LASER){
      if(!kf.isInitialized()){
        last_time = measurement_data[i].timestamp_;
        // 创建4维0矩阵，前2位用x,y填充
        Eigen::Vector4d x_in = Eigen::Vector4d::Zero();
        x_in.head<2>() = measurement_data[i].raw_measurements_;
        kf.initialization(x_in);
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
        continue;
      }
      // F
      current_time = measurement_data[i].timestamp_;
      size_t delta_t = current_time - last_time;
      last_time = current_time;
      // set F
      Eigen::Matrix2d tmp;
      tmp << delta_t, 0,
              0, delta_t; 
      Eigen::Matrix4d F_in = Eigen::Matrix4d::Identity();
      F_in.block<2, 2>(0, 2) = tmp;
      // std::cout << F_in << std::endl;
      kf.setF(F_in);
      // predict
      kf.pridection();
      // measurement
      Eigen::VectorXd z(2, 1);
      z = measurement_data[i].raw_measurements_;
      kf.measurementUpdate(z);
      // state x
      Eigen::VectorXd x_out = kf.getX();
      // std::cout << "kf output state x:" << x_out(0) << ","
      //           << "y: " << x_out(1) <<std::endl;
      x_state.push_back(x_out);
    }
  }
  if(writeCSV("kf_out.csv", x_state)){
    std::cout << "Write OK" << std::endl;
  }
}

void testEKF(){
  // get measurement_data:timestamp, rho, phi, rho_dot
  size_t last_time, current_time;
  std::vector<MeasurementPackage> measurement_data;
  // output
  std::vector<Eigen::VectorXd> out_state;
  if(!getMeasurementData(measurement_data)){
    std::cout << "get measurement data failed" << std::endl;
  }
  // initialize EKF
  ExtendedKalmanFilter ekf;
  for(int i = 0; i < measurement_data.size(); ++i){
    if(measurement_data[i].sensor_type_ == MeasurementPackage::RADAR){
      if(!ekf.isInitialization()){
        last_time  = measurement_data[i].timestamp_;
        // init ekf: state
        Eigen::VectorXd state(4, 1);
        double rho = measurement_data[i].raw_measurements_(0);
        double phi = measurement_data[i].raw_measurements_(1);
        double rho_dot = measurement_data[i].raw_measurements_(2);
        double x = rho * cos(phi);
        double y = rho * sin(phi);
        double vx = rho_dot * cos(phi);
        double vy = rho_dot * sin(phi);
        // 避免除数为0
        x = x < 0.0001 ? 0.0001 : x;
        y = y < 0.0001 ? 0.0001 : y;
        vx = vx < 0.0001 ? 0.0001 : vx;
        vy = vy < 0.0001 ? 0.0001 : vy;

        state << x, y, vx, vy;
        ekf.initialization(state);
        // set P, Q, R
        Eigen::Matrix4d P_in = Eigen::Matrix4d::Identity();
        Eigen::Matrix2d tmp;
        tmp << 10, 0,
              0, 10;
        P_in.block<2, 2>(2, 2) = tmp;   // 1, 0, 0, 0,
                                        // 0, 1, 0, 0,
                                        // 0, 0, 10, 0,
                                        // 0, 0, 0, 10;
        ekf.setP(P_in);

        Eigen::Matrix4d Q_in = Eigen::Matrix4d::Identity();
        ekf.setQ(Q_in);

        Eigen::Matrix3d R_in;
        R_in << 0.09, 0, 0,
                0, 0.0009, 0,
                0, 0, 0.09;
        ekf.setR(R_in);
        continue;
      }

      // set F
      current_time = measurement_data[i].timestamp_;
      size_t delta_t = current_time - last_time;
      last_time = current_time;
      Eigen::Matrix2d tmp;
      tmp << delta_t, 0,
            0, delta_t;
      Eigen::Matrix4d F_in = Eigen::Matrix4d::Identity();
      F_in.block<2, 2>(0, 2) = tmp;     // 1, 0, delta_t, 0,
                                        // 0, 1, 0, delta_t,
                                        // 0, 0, 1, 0,
                                        // 0, 0, 0, 1;
      // std::cout << F_in << std::endl;
      ekf.setF(F_in);
      // perdict x = f * x;
      ekf.predict();

      // update
      Eigen::Vector3d z;
      z << measurement_data[i].raw_measurements_;
      ekf.measurementUpdate(z);
      auto x = ekf.getX();
      out_state.push_back(x);
      // std::cout << "H_: " << ekf.calculateJacobian() << std::endl;
      // std::cout << "ekf output state x:" << x(0) << ","
      //           << "y: " << x(1) <<std::endl;
    }
  }
  if(writeCSV("ekf_out.csv", out_state)){
    std::cout << "Write OK" << std::endl;
  }
}