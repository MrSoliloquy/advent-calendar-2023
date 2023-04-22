/**
 * @author Conor Rojas
 * @date 4/21/23
 * @brief In case the Elves get hungry and need extra snacks, they need to know which Elf to ask: they'd 
 * like to know how many Calories are being carried by the Elf carrying the most Calories. In the example 
 * above, this is 24000 (carried by the fourth Elf). Find the Elf carrying the most Calories. How many total
 * Calories is that Elf carrying?
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

/**
 * @brief Read the input from a file, converts it to numbers and puts the sum of each group in a vector
 * @return vector of the of the sum of calories of each elf
*/
std::vector<int> readFile() {
  std::ifstream file("calories.txt");
  if (!file.is_open()) {
    std::cerr << "The file could not be open!" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::vector<int> sum;
  std::string line;
  int actual_sum{0};
  while (std::getline(file, line)) {
    if (line.empty()) {
      sum.push_back(actual_sum);
      actual_sum = 0;
    }
    else {
      std::stringstream ss(line);
      int num{0};
      while (ss >> num) {
        actual_sum += num;
      }
    }
  }
  // If there's an empty line at the end, an aditional zero would be added. This don't let it happen
  if (actual_sum > 0) {
    sum.push_back(actual_sum);
  }
  file.close();
  return sum;
}

/**
 * @brief Find the biggest amount of calories
 * @param sum Vector of the sum of calories of each elf
 * @return the biggest amount of calories
*/
int biggestNumber(const std::vector<int> &sum) {
  int biggest_number = sum[0];
  for (int i{1}; i < sum.size(); ++i) {
    if (sum[i] > biggest_number) {
      biggest_number = sum[i];
    }
  }
  return biggest_number;
}

/**
 * @brief Swaps the position of two given numbers
 * @param num1 first number to exchange
 * @param num2 second number to exchange
 */
void swap(int &num1, int &num2) {
  int temp = num1;
  num1 = num2;
  num2 = temp;
}

/**
 * @brief Calculate through the QuickSort algorithm the sum of the three bigger amounts of calories
 * @param sum Vector of the sum of calories of each elf
 * @param left first position of the vector 'sum'
 * @param right last position of the vector 'sum'
 * @return the sum of the three bigger amounts of calories
 */
int total_calories_podium(std::vector<int> &sum, int left, int right) {
  // base case
  if (left >= right) { 
    return sum[right];
  }
  int i{left}, j{right};
  int pivot = sum[(left + right) / 2];
  while (i <= j) {
    while (sum[i] < pivot) {
      ++i;
    }
    while (sum[j] > pivot) {
      --j;
    }
    if (i <= j) {
      swap(sum[i], sum[j]);
      ++i;
      --j;
    }
  }
  total_calories_podium(sum, left, j);
  total_calories_podium(sum, i, right);
  int highest_calories{0};
  for (int k = sum.size() - 1; k >= sum.size() - 3; --k) {
    highest_calories += sum[k];
  }
  return highest_calories;
}

int main() {
  std::vector<int> sum;
  sum = readFile();
  int biggest_number = biggestNumber(sum);
  int left = 0;
  int right = sum.size() - 1;
  std::cout << "We are looking for the biggest number...\n" << "...\n" << "...\n" << "...\n";
  std::cout << "The biggest number has been found!: " << biggest_number << std::endl;
  int three_more_caloric_amounts = total_calories_podium(sum, left, right);
  std::cout << "The sum of the 3 elves carrying the highest number of calories is: " << three_more_caloric_amounts << std::endl;
  return 0;
}