**Overview**

The Dining Philosophers problem is a classic synchronization problem in computer science, 
illustrating challenges in resource allocation and deadlock prevention. This project is 
implemented in C using threads and mutexes.

**Features**

Implements the Dining Philosophers problem using multithreading.

Uses mutexes to prevent race conditions and deadlocks.

Ensures philosophers pick up and release forks safely.

Includes configurable parameters such as the number of philosophers and simulation duration.

**Prerequisites**

GCC compiler

POSIX threads (pthread) library

**Compilation**

To compile the project, run: make
**
Usage**

Run the program with the following syntax:
./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]

**Arguments:**

<number_of_philosophers>: Number of philosophers (minimum 1).

<time_to_die>: Time (in milliseconds) after which a philosopher dies if they haven't eaten.

<time_to_eat>: Time (in milliseconds) it takes for a philosopher to eat.

<time_to_sleep>: Time (in milliseconds) a philosopher sleeps after eating.

[number_of_meals] (optional): Number of meals each philosopher must eat before the simulation ends.

**Implementation Details**

Each philosopher is represented by a thread.

Forks are implemented as mutexes.

A global monitor ensures synchronization and detects deadlocks.

Optional meal count terminates the program when all philosophers finish eating.

**Possible Issues**

Deadlocks: Prevented by enforcing an odd-even pickup strategy.

Starvation: Handled by tracking last meal time.
