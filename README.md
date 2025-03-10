# Guitarras p'Alugar (Guitars Rental)

## About the Project
This project was developed as part of the **Introduction to Programming** course in the **Computer Engineering** degree at the Instituto Superior de Engenharia de Coimbra (ISEC). The program aims to manage guitar rentals in a fictional store called **"Guitarras p’Alugar"**.

The software was implemented in **C (following the C99 standard)**, utilizing **dynamic memory** and **text and binary file handling** for persistent data storage.

## Features
The program allows:

- **Guitar Management**
  - Add new guitars to stock
  - Display the rental history of a guitar
  - List all available guitars
  - List currently rented guitars
  - Register damaged guitars and allow repairs

- **Client Management**
  - Register new clients (ensuring they are not banned)
  - Remove active clients
  - Display client status (current rentals, fines, damaged guitars)
  - List all active clients
  - Display the list of banned clients

- **Rental Management**
  - Create new rentals for registered clients
  - Conclude rentals and calculate possible fines
  - Display active rentals
  - Penalize clients for late returns
  - Automatically ban clients who break the rules

## Data Structures
The program uses:

- **Dynamic Array** to store available guitars
- **Two-Level Linked List** to store clients and their rentals
- **Text Files** to store active clients and guitars
- **Binary File** to store banned clients

## Technical Requirements
- Programming Language: **C (C99)**

## File Structure
Data is stored in text and binary files:

- **guitarras.txt**: Contains guitar information in the following format:
  ```
  ID PricePerDay Value Status Name
  ```

- **clientes.txt**: Contains client information and their rentals:
  ```
  NIF NumberOfRentals Name
  GuitarID Status StartDate ReturnDate
  ```

- **banidos.dat**: Contains banned clients, stored in binary format.

## Notes
- The program **does not use the system date**, requiring the user to manually enter dates.
- For the first execution, ensure that **guitarras.txt** and **clientes.txt** files exist (even if empty).
- If a client is banned, they cannot be registered again.


This project was developed with a focus on **dynamic memory handling**, **data structures**, and **file manipulation** in C.