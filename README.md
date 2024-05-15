# Music-Analytics_C-Python
This repository hosts two descriptive analytics programs: one written in C and the other in Python. Both programs handle datasets in CSV format, sourced from [Kaggle.com](https://www.kaggle.com/datasets/paradisejoy/top-hits-spotify-from-20002019). 

### Index
* [Music Manager in Python](#Python)
* [Music Manager in C](#C)

---
### Music Manager in Python
<a name="Python"></a>

The Python-based [Music Manager](https://github.com/NeddTheRedd/Music-Analytics_C-Python/blob/main/music_manager.py) processes arguments and files from standard input (stdin). Using the Pandas library, it sorts through the provided tables based on three input criteria: Energy, Popularity, and Danceability. The program then compiles the requested display results into a CSV file and outputs it to standard output (stdout).

Example input: **music_manager.py --sortBy=energy --display=20 --files=songs_normalize.csv**

**Output:**

<img width="450" alt="Screen Shot 2024-05-14 at 10 31 34 PM" src="https://github.com/NeddTheRedd/Music-Analytics_C-Python/assets/153869055/d7e2a138-18c8-4c22-837d-591b913b5ba7">

---
### Music Manager in C
<a name="C"></a>

The C-based [Music Manager](https://github.com/NeddTheRedd/Music-Analytics_C-Python/blob/main/music_manager.c) performs a very similar function as the Python counterpart mentioned above. However, it showcases proficiency in memory allocation and dynamic data structures. Developed from a 'skeleton' starter file, this program originated as a university assignment. To assemble it, simply run the provided [makefile](https://github.com/NeddTheRedd/Music-Analytics_C-Python/blob/main/makefile) using the make command in Bash. Once assembled, you can enter commands via the command line interface.

Example input: **./music_manager --sortBy=danceability --display=35 --files=songs_normalize.csv**

---
