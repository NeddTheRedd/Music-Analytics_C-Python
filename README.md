# Music-Analytics_C-Python
Two different descriptive analytics programs -> One written in C, and one written in Python <br>
All datasets are in CSV format and come from [Kaggle.com](https://www.kaggle.com/datasets/paradisejoy/top-hits-spotify-from-20002019). 

### Index
* [Music Manager in Python](#Python)
* [Music Manager in C](#C)

---
### Music Manager in Python
<a name="Python"></a>

Takes arguments and files from the stdin, parses them, and sorts through the tables using the Pandas library, and three input criteria: Energy, Popularity, and Danceability. The program then assembles the requested display results into a CSV file, and prints the file to stdout. 
<br> 

An example of an input is: **music_manager.py --sortBy=energy --display=20 --files=songs_normalize.csv**

**Prints:** 

<img width="450" alt="Screen Shot 2024-05-14 at 10 31 34 PM" src="https://github.com/NeddTheRedd/Music-Analytics_C-Python/assets/153869055/d7e2a138-18c8-4c22-837d-591b913b5ba7">

---
### Music Manager in C
<a name="C"></a>

---
