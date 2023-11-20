#include <iostream>
#include <fstream>
#include <optional>
#include <filesystem>

// // std::string readFileAsString(const std::string& readfile){
// std::string readFileAsString(const std::string& readfile, bool out_success){
//   std::ifstream read(readfile);
//   if(!read.is_open()){
//     out_success = false;
//     std::cout << "file open failed" << std::endl;
//     return std::string();
//   } else {
//     std::string result;
//     out_success = true;
//     read.close();
//     return result;
//   }
// }

std::optional<std::string> readFileAsString(const std::string& readfile){
  std::ifstream read(readfile);
    if(!read.is_open()){
    // std::cout << "file open failed" << std::endl;
    return {};
  } else {
    std::string fileContent((std::istreambuf_iterator<char>(read)), std::istreambuf_iterator<char>());
    read.close();
    return fileContent;
  }
}

int main(){
  // bool file_opened_successfully;
  // std::string data = readFileAsString("readflie.txt");
  // std::string data = readFileAsString("readflie.txt", file_opened_successfully);
  // if(data.empty())
  // auto current_path = std::filesystem::current_path();
  // // // std::cout << current_path;
  // // 相对路径
  // std::string relative_file_path = "data.txt";
  // // 绝对路径
  // std::string absolute_file_path = current_path.string() + "\\" + relative_file_path;
  // std::cout << absolute_file_path;
  
  // std::optional<std::string> data = readFileAsString(absolute_file_path);
  std::optional<std::string> data = readFileAsString("D:\\c++\\data.txt");
  std::string value = data.value_or("Not persent");
  if(data.has_value()){
    std::cout << "File read successfully!" << std::endl;
    std::string str = data.value();
    std::cout << str << "\n";
  } else {
    std::cout << "File could not be opened!\n";
    std::cout << value << "\n";
  }
}