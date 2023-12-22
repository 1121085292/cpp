#pragma once

#include "algorithm/kalman_filter/kalman_filter.h"
#include "measurement/sensor_measurement.h"

namespace fusion{

class MotionFusion {
  public:
    MotionFusion();

    void motionFusion();

    void initialization(Eigen::VectorXd X_in) {
      kf_.initialization(X_in);
      is_initialzed_ = true;
    };

    inline bool isInitialization() const {
      return is_initialzed_;
    }
  private:
    bool is_initialzed_;
    std::vector<MeasurementPackage> measurement_data_;
    KalmanFilter kf_;
    Eigen::MatrixXd lidar_R_;
    Eigen::MatrixXd radar_R_;
    Eigen::MatrixXd H_in_;
    std::vector<Eigen::VectorXd> x_state_;

}; 

} // fusion