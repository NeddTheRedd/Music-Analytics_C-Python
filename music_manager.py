#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pandas as pd
from typing import List, Dict
import sys

'''
Created on Sun Jun 11 17:43:33 2023
@author: leenapthine
'''


def print_output_file(output_file: str) -> None:
    """
    Opens and reads the given file, then prints each line to the stdout.

                Parameters:
                        a) (str) output_file: The path of the output file to be printed.

                Returns:
                        None
    """
    with open(output_file, mode='r') as file:
        for line in file:
            print(line.rstrip())


def make_file(sorted_and_merged: str) -> str:
    """
    Makes the given DataFrame into a CSV file named 'output.csv'.

                Parameters:
                        a) (str) sorted_and_merged: The DataFrame to be made into a CSV file.

                Returns:
                        output_file.csv (str) file.
    """
    output_file: str = 'output.csv'
    sorted_and_merged.to_csv(output_file, index=False)

    return output_file


def merge_dataframes(dataframes: List[List[str]], display: int, sort_by: str) -> List[str]:
    """
    Merges the given list of DataFrames using the shared column ('sort_by') and performs column drops.

                Parameters:
                        a) (List[List[str]]) dataframes: The list of DataFrames to be merged.
                        b) (int) display: The number of rows to be displayed.
                        c) (str) sort_by: The shared column used for merging the DataFrames.

                Returns:
                        List[pd.DataFrame] The merged DataFrame with column drops, limited to the (display)
                        number of rows. The type hint reads str, because Python 3.8 doesnt recognize
                        pd.DataFrame as a type hint.
    """
    all_dataframes: List[str] = pd.concat(dataframes, ignore_index=True)
    sorted_dataframes: List[str] = all_dataframes.sort_values(by=[sort_by, 'song'], ascending=[False, False])

    sorted_dataframes.drop(['duration_ms', 'explicit', 'key', 'loudness', 'mode', 'speechiness',
                            'acousticness', 'instrumentalness', 'liveness', 'valence', 'tempo',
                            'genre'], inplace=True, axis=1)
    if (sort_by == 'popularity'):
        sorted_dataframes.drop(['danceability', 'energy'], inplace=True, axis=1)
    elif (sort_by == 'energy'):
        sorted_dataframes.drop(['danceability', 'popularity'], inplace=True, axis=1)
    else:
        sorted_dataframes.drop(['energy', 'popularity'], inplace=True, axis=1)

    return sorted_dataframes.head(display)


def read_files(files: List[str], sort_by: str, display: int) -> List[List[str]]:
    """
    Reads and sorts the list of CSV files, and returns a list of the top 'display' rows of DataFrames from each file.

                Parameters:
                        a) (List[str]) files: The list of CSV files to be read.
                        a) (List[str]) files: The list of CSV files to be read.
                        b) (str) sort_by: The column used for sorting the DataFrames.
                        c) (int) display: The number of rows to be included in each DataFrame.

                Returns:
                        (List[List[pd.DataFrame]]) A list of DataFrames. The type hint reads List[List[str]].
                        This is because Python 3.8 doesn't recognize the pd.DataFrame as a type.
                        The top 'display' rows from the list of CSV files are in the list.
    """
    dataframes: List[List[str]] = []
    for file in files:
        dataframe: List[str] = pd.read_csv(file)
        sorted_dataframe: List[str] = dataframe.sort_values(by=[sort_by, 'song'], ascending=[False, False])
        dataframes.append(sorted_dataframe.head(display))

    return dataframes


def parse_arguments(arguments: List[str]) -> Dict[str, str]:
    """
    Parses the command-line arguments and returns a dictionary containing the parsed arguments.

                Parameters:
                        a) (List[str]): The list of command-line arguments.

                Returns:
                        Dict[str, str]: A dictionary containing the parsed arguments.
    """
    parsed_arguments: Dict[str, str] = {}
    for argument in arguments:
        if "--" in argument and "=" in argument:
            key, value = argument.split("=")
            key = key.strip("--")
            parsed_arguments[key] = value
    return parsed_arguments


def main() -> str:
    """
    The main function is the central control and passes variables to the other functions.

                Returns:
                        str: The path of the output.csv file.
    """
    if len(sys.argv) < 4:
        print("Invalid number of arguments. Please provide --sortBy, --display, and --files arguments.")
        sys.exit(1)

    parsed_arguments: Dict[str, str] = parse_arguments(sys.argv[1:])

    sort_by: str = parsed_arguments.get("sortBy")
    display: int = int(parsed_arguments.get("display"))
    files: List[str] = parsed_arguments.get("files").split(",")

    dataframes: List[List[str]] = read_files(files, sort_by, display)
    sorted_and_merged: List[str] = merge_dataframes(dataframes, display, sort_by)
    output_file: str = make_file(sorted_and_merged)
    print_output_file(output_file)
    
    return output_file


if __name__ == '__main__':
    main()
