# Philosophers

The **Philosophers** project at 42 Beirut is a classic concurrency problem in which multiple philosophers are sitting at a table with a bowl of spaghetti
. Each philosopher does only one of the following actions: **thinking**, **eating**, or **sleeping**. They are represented as threads,
and they need to share resources such as forks to eat. The objective of the project is to simulate the philosophers' behavior while 
avoiding deadlocks and ensuring that no philosopher starves.

## Requirements

- The project aims to implement a multithreading solution to the dining philosophers problem.
- You are required to use **pthread** to manage concurrency.
- Implement proper synchronization to avoid deadlocks and race conditions.

## Instructions

The program should simulate multiple philosophers using the following rules:

1. **Philosophers**: Each philosopher thinks and eats. They eat by picking up two forks. After eating, they put down the forks and sleep.
2. **Forks**: There are a limited number of forks, one for each philosopher. Each philosopher needs two forks to eat.
3. **Deadlock Prevention**: Ensure that no deadlocks occur. Deadlock happens if all philosophers pick up one fork and wait indefinitely for the second one.

The simulation should stop when either:

1. A philosopher has eaten enough times (a certain number defined by the input).
2. A philosopher starves (i.e., does not eat within a certain time period).
3. All philosophers have finished eating.

## Parameters

The program should take the following arguments:

```bash
./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]

How to Compile
To compile the program, you can use the provided Makefile:

make
This will generate the philosophers executable.

Example Usage
bash
Copy
Edit
./philosophers 5 800 200 200 5
This will simulate 5 philosophers, each eating 5 times, with a time limit of 800 milliseconds before they die from starvation,
 and a time of 200 milliseconds for both eating and sleeping.

File Structure
philosophers.c: The main program file containing the implementation of the philosophers' behavior.
philosophers_utils.c: Helper functions for managing philosophers' actions.
philosophers.h: Header file containing necessary declarations.
Makefile: The Makefile for compiling the program.
Constraints
Use of external libraries: Only pthread is allowed for managing concurrency.
No memory leaks: Ensure proper memory management using malloc and free.
Ensure no deadlocks or race conditions.
