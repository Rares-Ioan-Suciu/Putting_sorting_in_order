#!/usr/bin/env python3
import os
import sys
import matplotlib.pyplot as plt
import pandas as pd

# Define distinct line styles and colors for each dataset
LINE_STYLES = ['-', '--', '-.', ':']  # Customize as needed
LINE_COLORS = ['blue', 'orange', 'green', 'red', 'purple', 'brown']  # Customize as needed

def extract_label(csv_file):
    # Extract the second word from the CSV file name
    parts = csv_file.split('_')
    if len(parts) < 2:
        return "Unknown Sort"
    # Extract the second word
    second_word = parts[1]
    # Construct the custom legend label
    if second_word not in {"Introsort", "Timsort"}:
        label = f"{second_word} Sort"
    else:
        label = second_word
    return label

def generate_plots(data_type, csv_path):
    # Find all CSV files for the specified data type
    csv_files = [f for f in os.listdir(csv_path) if f.endswith(f"{data_type}.csv")]
    if not csv_files:
        print(f"No CSV files found for {data_type}.")
        return

    # Plot each CSV file with a distinct line style and color
    for idx, csv_file in enumerate(csv_files):
        print(f"Processing CSV file: {csv_file}")
        file_path = os.path.join(csv_path, csv_file)
        try:
            # Read data from the CSV file
            df = pd.read_csv(file_path)
            print(f"Number of rows in DataFrame: {len(df)}")  # Print the number of rows in the DataFrame
            # Check if the DataFrame is empty
            if df.empty:
                print(f"DataFrame from file {csv_file} is empty. Skipping plot.")
                continue
            
            # Sort DataFrame by 'Data Size'
            df.sort_values(by='Data Size', inplace=True)
            
            # Extract custom legend label
            label = extract_label(csv_file)
            
            # Plot the data with a distinct line style and color, and custom legend label
            plt.plot(df['Data Size'], df['Sorting Time'], label=label, linestyle=LINE_STYLES[idx % len(LINE_STYLES)], color=LINE_COLORS[idx % len(LINE_COLORS)])
        except Exception as e:
            print(f"Error processing file {file_path}: {e}")

    # Configure plot
    plt.xlabel('Data Size')
    plt.ylabel('Sorting Time (ms)')
    plt.title(f'Sorting Algorithms Performance - {data_type}')
    plt.legend()
    plt.grid(True)

    # Save the plot
    save_path = os.path.join(csv_path, f"{data_type}_plot.png")
    plt.savefig(save_path)
    print(save_path, "\n")
    print(f"Plot saved at: {save_path}")

    # Display the plot interactively
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python plot_generator.py <data_type> <csv_path>")
        sys.exit(1)
    
    data_type = sys.argv[1]
    csv_path = sys.argv[2]
    generate_plots(data_type, csv_path)
