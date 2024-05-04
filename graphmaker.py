#!/usr/bin/env python3
import os
import sys
import matplotlib.pyplot as plt
import pandas as pd


LINE_STYLES = ['-', '--', '-.', ':']  
LINE_COLORS = ['blue', 'orange', 'green', 'red', 'purple', 'brown']  

def extract_label(csv_file):
    
    parts = csv_file.split('_')
    if len(parts) < 2:
        return "Unknown Sort"

    second_word = parts[1]
    
    if second_word not in {"Introsort", "Timsort"}:
        label = f"{second_word} Sort"
    else:
        label = second_word
    return label

def generate_plots(data_type, csv_path):

    csv_files = [f for f in os.listdir(csv_path) if f.endswith(f"{data_type}.csv")]
    if not csv_files:
        print(f"No CSV files found for {data_type}.")
        return

    
    for idx, csv_file in enumerate(csv_files):
        print(f"Processing CSV file: {csv_file}")
        file_path = os.path.join(csv_path, csv_file)
        try:
            df = pd.read_csv(file_path)
            print(f"Number of rows in DataFrame: {len(df)}") 
            
            if df.empty:
                print(f"DataFrame from file {csv_file} is empty. Skipping plot.")
                continue
            
            
            df.sort_values(by='Data Size', inplace=True)
            
    
            label = extract_label(csv_file)
            
        
            plt.plot(df['Data Size'], df['Sorting Time'], label=label, linestyle=LINE_STYLES[idx % len(LINE_STYLES)], color=LINE_COLORS[idx % len(LINE_COLORS)])
        except Exception as e:
            print(f"Error processing file {file_path}: {e}")
            
    plt.xlabel('Data Size')
    plt.ylabel('Sorting Time (ms)')
    plt.title(f'Sorting Algorithms Performance - {data_type}')
    plt.legend()
    plt.grid(True)

    
    save_path = os.path.join(csv_path, f"{data_type}_plot.png")
    plt.savefig(save_path)
    print(save_path, "\n")
    print(f"Plot saved at: {save_path}")

    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python plot_generator.py <data_type> <csv_path>")
        sys.exit(1)
    
    data_type = sys.argv[1]
    csv_path = sys.argv[2]
    generate_plots(data_type, csv_path)
