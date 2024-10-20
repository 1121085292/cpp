#include <iostream>
#include <limits>
#include <vector>

// 滑动窗口平滑函数
std::vector<double> smoothData(const std::vector<double>& data,
                               int window_size) {
  std::vector<double> smoothed_data;
  int data_size = data.size();
  for (int i = 0; i < data_size; ++i) {
    double sum = 0;
    int count = 0;
    for (int j = std::max(0, i - window_size);
         j <= std::min(data_size - 1, i + window_size); ++j) {
      sum += data[j];
      ++count;
    }
    smoothed_data.push_back(sum / count);
  }
  return smoothed_data;
}

// 提取多个最小距离区段的函数
/**
 * Finds the segments in the given distance data where the distance is below a
 * specified threshold.
 *
 * @param distances A vector of doubles representing the distance data.
 * @param threshold A double value specifying the distance threshold.
 * @return A vector of pairs, where each pair represents the start and end
 * indices of a segment where the distance is below the threshold.
 */
std::vector<std::pair<int, int>> findMinDistanceSegments(
    const std::vector<double>& distances, double threshold) {
  std::vector<std::pair<int, int>> segments;
  int start = -1, end = -1;
  for (int i = 0; i < distances.size(); ++i) {
    if (distances[i] < threshold) {
      if (start == -1) start = i;
      end = i;
    } else if (start != -1) {
      segments.push_back({start, end});
      start = -1;  // 重置开始索引，准备下一个区段
    }
  }
  if (start != -1) {
    segments.push_back({start, end});  // 最后一段如果还未结束
  }
  return segments;
}

// 提取每个区段的最小值
std::vector<double> extractMinValuesFromSegments(
    const std::vector<double>& distances,
    const std::vector<std::pair<int, int>>& segments) {
  std::vector<double> min_values;
  for (const auto& segment : segments) {
    double min_value = std::numeric_limits<double>::max();
    for (int i = segment.first; i <= segment.second; ++i) {
      if (distances[i] < min_value) {
        min_value = distances[i];
      }
    }
    min_values.push_back(min_value);
  }
  return min_values;
}

int main() {
  // 假设采样到的距离数据
  std::vector<double> distances = {3.0, 2.5, 2.0, 1.8, 1.5, 1.0, 0.9, 1.0,
                                   1.5, 2.0, 2.5, 3.0, 2.2, 2.0, 1.5, 1.2};

  // 平滑距离数据
  std::vector<double> smoothed_data = smoothData(distances, 2);

  // 定义最小距离的阈值
  double threshold = 1.2;

  // 查找所有的最小距离区段
  std::vector<std::pair<int, int>> segments =
      findMinDistanceSegments(smoothed_data, threshold);

  // 提取每个区段的最小值
  std::vector<double> min_values =
      extractMinValuesFromSegments(smoothed_data, segments);

  // 输出每个最小距离区段及其最小值
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cout << "Segment " << i + 1 << " : " << segments[i].first << " - "
              << segments[i].second;
    std::cout << "min: " << min_values[i] << std::endl;
  }

  return 0;
}