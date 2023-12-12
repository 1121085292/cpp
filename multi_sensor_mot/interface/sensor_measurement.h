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

bool getLidarData(double x, double y, size_t ts);