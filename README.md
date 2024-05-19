# Simple Calculator with Client-Server Implementations

## Overview

This project implements a simple calculator that can perform the following operations on two integers supplied by the user:
- Addition
- Multiplication
- Square
- Square Root

In addition to the standalone version, the project includes client-server implementations to run the calculator on different machines. The implementations cover the following types of network communication:
- Iterative Connectionless (UDP)
- Iterative Connection-Oriented (TCP)
- Concurrent Connectionless (UDP)
- Concurrent Connection-Oriented (TCP)

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
  - [Standalone Calculator](#standalone-calculator)
  - [Client-Server Implementations](#client-server-implementations)
    - [Iterative Connectionless (UDP)](#iterative-connectionless-udp)
    - [Iterative Connection-Oriented (TCP)](#iterative-connection-oriented-tcp)
    - [Concurrent Connectionless (UDP)](#concurrent-connectionless-udp)
    - [Concurrent Connection-Oriented (TCP)](#concurrent-connection-oriented-tcp)

## Features

- Perform basic arithmetic operations: addition, multiplication, square, and square root.
- Client-server implementations using different network communication protocols.
- Suitable for running on different machines over a network.

## Requirements

- GCC (GNU Compiler Collection)
- POSIX-compliant operating system (e.g., Linux)

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/SonnyKundi/CSC322_CALCULATOR.git

## Usage

# Standalone Calculator

Compile and run the standalone calculator:
```
  gcc -o calculator calculator.c -lm
  ./calculator
```
# Client-Server Implementations

## Iterative Connectionless (UDP)
1. Compile the server and client:
```
gcc -o udp_server udp_server.c -lm
gcc -o udp_client udp_client.c
```
2. Run the server:
```
./udp_server
```
3. Run the client:
```
./udp_client
```
# Iterative Connection-Oriented (TCP)
1. Compile the server and client:
```
gcc -o tcp_server tcp_server.c -lm
gcc -o tcp_client tcp_client.c
```
2. Run the server:
```
./tcp_server
```
3. Run the client:
```
./tcp_client
```

# Concurrent Connectionless (CUDP)
1.  Compile the server and client:
```
gcc -o cudp_server cudp_server.c -lpthread -lm
gcc -o cudp_client cudp_client.c
```
2. Run the server:
```
./cudp_server
```
3. Run the client:
```
./cudp_client
```

# Concurrent Connection-Oriented (CTCP)
1.  Compile the server and client:
```
gcc -o ctcp_server ctcp_server.c -lpthread -lm
gcc -o ctcp_client ctcp_client.c
```
2. Run the server:
```
./ctcp_server
```
3. Run the client:
```
./ctcp_client
```





