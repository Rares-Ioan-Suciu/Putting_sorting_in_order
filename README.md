# Sorting Algorithm Analyzer

## Overview
The Sorting Algorithm Analyzer is a tool designed to analyze the performance of various sorting algorithms across different types of data distributions. Its primary goal is to assist users in making informed decisions when selecting a sorting algorithm for their specific use case.

This project was developed as a part of a research project during my Methods and Practices in Computer Science course in the first year of my Bachelor's Degree. The requirement of the project was to study sorting algorithms' behavior and performance.

The project is composed of three parts:  
   -The tester (in C++) - which handles the menu, selecting algorithms and data distributions, calling the analyzer and the python script resposible with generating plots. 
   -The analyzer (in C++) - which is responsible with generating data, that keeps increasing until a maximum value given by the user and using a simple value, and running sorting algorithms recording their runtime into a specific csv file.  
   -The graph_maker - a python script that is used to transform the csv files into beautfiul plots.  

## Usage
To use the Sorting Algorithm Analyzer, follow these steps:

1. **Installation**:
   - Clone the repository to your local machine:

     ```
     git clone https://github.com/your-username/sorting-algorithm-analyzer.git
     ```

2. **Running the Program**:
   - Navigate to the directory where the analyzer program is stored.
   - Run the program in the terminal, providing the following arguments:
     - Directory where the analyzer program is stored.
     - Directory where the CSV file will be stored.
     - Directory where the Python program is stored.

     Example:
     ```
       ./tester_sorting /home/rares655/analysis_program/cmake-build-debug /home/rares655/tester_sorting/cmake-build-debug /home/rares655/Desktop/Sem_2/MPI/python_creator
     ```

3. **Selecting Sorting Algorithms**:
   - Choose from 12 sorting algorithms categorized as follows:
     - O(n^2): Bubble Sort, Selection Sort, Insertion Sort, Shell Sort.
     - O(nlogn): Quick Sort, Merge Sort, Heap Sort.
     - Non-comparison algorithms: Counting Sort, Radix Sort, Bucket Sort.
     - Hybrid algorithms: Introsort, Timsort.

4. **Selecting Data Distributions**:
   - Choose from seven types of data distribution:  
     -Sorted - the integers are sorted,  
     -Reverse - same as above, but the data is sorted in reverse order,   
     -Unique - the integers are randomly ordered and there are no duplicates,  
     -Non-unique - same as above, but there can exist duplicates,  
     -Negative - the numbers are al negative,  
     -Almost sorted - the integers are put in order, but there is some disorder  
     -Sparse - 70% of the integers genrated have the value 0.



## Examples
Here are some examples of how to use the Sorting Algorithm Analyzer:

- Analyzing the performance of Quick Sort on sorted data:
- Analyzing the performance of Merge Sort on reverse data:  
Most importantly:
- Analyze and compare the performance of up to 12 sorting algorithms

## Output
After running the Sorting Algorithm Analyzer, users can expect the following output:

- **Performance Comparison Plot**: The program generates a plot illustrating the performance of the selected sorting algorithms on a specific type of data distribution. The plot allows users to visualize the efficiency of each algorithm in terms of time consumption.
- CSV tables, that can be analyzed by the user, but if a lot of tests are ran, become close to useless

### Installation Dependencies:

Before running the Sorting Algorithm Analyzer, ensure you have the following dependencies installed on your system:

#### For C++ Tester and Analyzer:
- **C++ Compiler**: The C++ components of the analyzer require a C++ compiler to compile and run. Ensure you have a compatible C++ compiler installed on your system, such as GCC or Clang.

#### For Python Graph Maker:
- **Python**: The Python graph maker component requires Python to be installed on your system. Make sure you have Python version 3.x installed. You can download Python from the official website: [https://www.python.org/downloads/](https://www.python.org/downloads/).

- **Python Libraries**: The Python script for generating plots may rely on third-party libraries such as Matplotlib or Pandas for data visualization. Install the required libraries using pip:

  ```bash
  pip install matplotlib pandas
