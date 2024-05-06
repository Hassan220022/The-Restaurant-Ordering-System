# Multi-threaded Restaurant Ordering System

This repository contains a C program that simulates a restaurant ordering system using multi-threading and semaphores for synchronization. The system includes separate threads for customers, chefs, and waiters, each interacting through shared resources with proper synchronization to simulate a real-world restaurant scenario.

## Overview

The program demonstrates a basic use of threads and semaphores in a POSIX environment. It models a system where:
- **Customers** place orders.
- **Chefs** cook the orders.
- **Waiters** serve the cooked orders.

Semaphores are used to manage the concurrency limits, such as the number of customers who can place orders at once, the number of chefs who can cook simultaneously, and the number of waiters who can serve.

## Requirements

To run this program, you will need:
- A GCC compiler
- A POSIX-compliant operating system (e.g., Linux or macOS)

## Compilation

Compile the program using the following GCC command:

```bash
gcc -o restaurant_system restaurant_system.c -lpthread
```

This command compiles the `restaurant_system.c` file and links the pthread library to handle the multi-threading.

## Running the Program

After compilation, you can run the program by executing:

```bash
./restaurant_system
```

The output will display the actions taken by customers, chefs, and waiters, along with the synchronization process handled by semaphores.

## Program Structure

- **Semaphores**:
  - `order_place_sem`: Controls the number of customers that can place orders simultaneously.
  - `order_cook_sem`: Limits the number of orders that can be cooked at the same time.
  - `order_serve_sem`: Restricts the number of orders that waiters can serve at once.

- **Mutex**:
  - `mutex`: Ensures that access to the shared order queue is synchronized among threads.

- **Threads**:
  - Customer threads simulate order placement.
  - Chef threads manage cooking processes.
  - Waiter threads handle serving of orders.

## Customization

You can modify the constants defined at the beginning of the `restaurant_system.c` file to change the number of threads for customers, chefs, and waiters, as well as the total number of orders allowed in the system.

## Contributing

Contributions to the project are welcome. You can contribute by improving the synchronization mechanism, adding new features, or optimizing the existing codebase.

## License

This project is open-sourced under the MIT License. See the `LICENSE` file for more details.
