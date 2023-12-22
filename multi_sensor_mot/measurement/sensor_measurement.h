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
bool getMeasurementData(std::vector<MeasurementPackage>& measurement_data);

bool writeCSV(const std::string& filename, std::vector<Eigen::VectorXd>& vec);