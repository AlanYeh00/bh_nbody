# Topic: Barnes-Hut algorithm simulation
# Class: Comp 464 High performance computing
# Team: Sung Yu Yeh and Cordova Ricardo


This project simulates the N-body problem using the Barnes-Hut algorithm for particle interaction. It supports parallel computation using OpenMP.

How to Use:
Set the Number of Threads: Set the number of threads for parallel execution using the command "export OMP_NUM_THREADS=<number_of_threads>", where <number_of_threads> is the desired number of threads.

Compile the Executable: Run "make" to compile the program and create the executable file BarnesHut.

Run the Simulation: Execute the simulation using ./BarnesHut -n <number_of_particles> -s <number_of_steps>, where <number_of_particles> is the total number of particles and <number_of_steps> is the number of simulation steps. For example, to simulate 1000 particles for 50 steps, use ./BarnesHut -n 1000 -s 50.

Clean Compiled Files: To remove the compiled executable and intermediate files, run make clean.

If you want to check the current number of threads.
Use the echo command to verify the current number of threads set in your environment:
"echo $OMP_NUM_THREADS"