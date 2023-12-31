#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "measurement/sensor_measurement.h"

bool getMeasurementData(std::vector<MeasurementPackage>& measurement_data){
  std::string input_file_name = "D:/c++/data/sample-laser-radar-measurement-data-2.txt";
  std::ifstream input_file(input_file_name.c_str(), std::ifstream::in);
  if(!input_file.is_open()){
    std::cout << "failed to open file: " << input_file_name << std::endl;
    return false;
  }

  std::string line;
  while(std::getline(input_file, line)){
    std::string sensor_type;
    MeasurementPackage meas_package;
    size_t timestamp;
    std::istringstream iss(line);
    // 读取当前行的第一个元素，L代表Lidar数据，R代表Radar数据
    iss >> sensor_type;
    if(sensor_type.compare("L") == 0){
      meas_package.sensor_type_ = MeasurementPackage::LASER;
      meas_package.raw_measurements_ = Eigen::VectorXd(2);
      float x, y;
      // 该行第二个元素为测量值x，第三个元素为测量值y，第四个元素为时间戳(纳秒）
      iss >> x;
      iss >> y;
      meas_package.raw_measurements_ << x, y;
      iss >> timestamp;
      meas_package.timestamp_ = timestamp;
      measurement_data.emplace_back(meas_package);
    } else if (sensor_type.compare("R") == 0) {
        meas_package.sensor_type_ = MeasurementPackage::RADAR;
        meas_package.raw_measurements_ = Eigen::VectorXd(3);
        // 该行第二个元素为距离pho，第三个元素为角度phi，第四个元素为径向速度pho_dot，第五个元素为时间戳(纳秒）
        float rho, phi, rho_dot;
        iss >> rho;
        iss >> phi;
        iss >> rho_dot;
        meas_package.raw_measurements_ << rho, phi, rho_dot;
        iss >> timestamp;
        meas_package.timestamp_ = timestamp;
        measurement_data.emplace_back(meas_package);
      }
  }
  return true;
}

bool writeCSV(const std::string &filename, std::vector<Eigen::VectorXd> &vectors)
{ 
  std::ofstream file(filename);
  if (!file.is_open())
  {
    std::cout << "file open failed" << std::endl;
    return false;
  } else {
    for(const auto& vector : vectors){
      file << vector(0) << "," << vector(1) << std::endl;
    }
  }
  file.close();
  return true;
}
