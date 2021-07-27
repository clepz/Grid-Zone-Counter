# Zone Counter Project

![](https://img.shields.io/badge/platform-Ubuntu%20Bionic-blue) ![](https://img.shields.io/badge/build-passing-green)
### Features

- Map creator GUI in python.
- Zone Counter program in c++
- Save Map as txt and use it from c++ and python.
- Create a map with MapInterface functions.
- C++ library for python wrapping

## Usage

### Test Evironment
- Ubuntu 18.04
- g++ v7.5.0
- C++ standard: 17
- Build tool: Cmake

### Run
Main code includes two examples:
1. Map from txt file created with python gui, then count of zone from this map
2. Creating map  with c++ api, then count of zone from this map.
If you want to provide another map text file created with python gui use: `./zonecounter --filepath <path>`

```bash
mkdir build
cd build
cmake ..
make -j4
cd ../bin
./zonecounter
```

### Custom Map
1. Use python gui for map creating
	- Save map as txt
	- Run zonecounter with filepath argument
2. C++ code
	- change codes inside `createMap` function in `main.cpp`
	
### ****NOTE**
Create a map inside `createMap` function in main.cpp:
```c++
map.SetSize(5,5);
map.SetBorder(3,1);
map.SetBorder(3,2);
map.SetBorder(3,3);
map.SetBorder(3,4);
map.SetBorder(3,5);
```
Result is:

![](images/map5x5.png)

x,y index starts 1,1

## Solve Algorithm

- Once a map is created, create function adds border edges for all side. Like the picture below, in python gui section.
- Solve function initialize a zonePointMap which has all nonborder points. 
- Solve function calls LookNeighbor function witth a zonePoint
- LookNeighbor searches all neighbor cells recursively until remain no neighbor zone points in the map.
- ZoneCounter variable is increased after LookNeighbor returned true
- These processes continue until zonePointMap is empty.

## Python GUI

![](images/python_gui.png)

Python GUI is developed for test purposes and also It provides map visuality, map creation speed, variety.

### Requirements for python
- Python3.6
- PyQt5

### Run
`python map_creator.py`


## Test Video

Open video/bites_vid.mp4

## Known Bugs
--

## Improvements Can Be Made

- MapImpl class creates border edges and stores them. This process needs to be in ZoneCounterImpl class.



