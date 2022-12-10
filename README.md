## Traffic Simulator

<img src="data/traffic_simulation.gif"/>

This project is a traffic simulation in which vehicles are moving along streets and are crossing intersections equipped with a traffic light. 
The project was built for the Udacity C++ Nano Degree program fourth course as an application of C++ concurrent programming techniques, such as:
- Message queues
- Locks
- Mutexes
- Condition variables
- Threads and tasks

This is the project for the fourth course in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213): Concurrency. 

Throughout the Concurrency course, you have been developing a . However, with increasing traffic in the city, traffic lights are needed for road safety. Each intersection will therefore be equipped with a traffic light. In this project, you will build a suitable and thread-safe communication protocol between vehicles and intersections to complete the simulation. Use your knowledge of concurrent programming (such as mutexes, locks and message queues) to implement the traffic lights and integrate them properly in the code base.


## Dependencies (Linux)
1. Cmake and GCC:
```
    sudo apt update
    sudo apt install build-essential
    sudo apt install cmake
```

2. OpenCV >= 4.1 Library
Follow this [tutorial](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html) to install OpenCV library.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./traffic_simulation`.


