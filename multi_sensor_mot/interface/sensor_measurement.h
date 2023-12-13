#pragma once
#include <Eigen/Dense>

class MeasurementPackage {
public:
  size_t timestamp_;

  enum SensorType{
    LASER,
    RADAR
  } sensor_type_;

  Eigen::VectorXd raw_measurements_;
};


/// @brief 
/// @param measurement_data 
/// @return 
bool getLidarData(std::vector<MeasurementPackage>& measurement_data);