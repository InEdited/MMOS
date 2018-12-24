# MMOS 
This is a simple C++ program that compares the efficiency of widely known page replacement algorithms. It takes the length of the page reference string and the number of page frames in the system as arguments. It then randomly generates the reference string with page numbers (0-99) and applies the algorithms to that string. The algorithms included are: First-In-First-Out(FIFO), Least Recently Used(LRU), Least Frequently Used(LFU), Second Chance Algorithm, Enhanced Second Chance Algorithm, and the Optimal Algorithm.

The algorithm is implemented in C++(11) and is set to be running in terminal as a console application.

However, the project is implemented as a  web service where the user interface is a website powered by python on the backend using flask framework, the python server invokes the C++ program with the appropriate arguments provided by the user through the website and then returns back the output in a user friendly form.

This allows for fast computation using C++ as a driver for simulating the algorithms and suffer no losses in the computing speed while still having the program work with a nice user friendly interface.

The project displays and compares the output of the algorithms in a table structure and using a bar-chart to compare visually between their number of page faults (using CanvasJS).

### Project done in collaboration with : Robear Wagih @mo7sener
