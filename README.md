# Multi-process race

This code simulates a horse race which has N processes: a master and N horses (which are subprocess). All the horses wait for a number that the master gives to them. After that, they show it on screen and finish themselves. When both subprocess have ended, the master also finishes itself.

## Purpose

We developed this program for the Operating Systems subject for the Autonomous University of Barcelona (UAB) with the intention to learn the technologies and languages used.

## Usage

### Compilation

To compile the program you can run from a terminal:

```bash
gcc -o exeFileName process_race.c
```

Where "exeFileName" can be any name. After that you can execute the file created from anywhere.

### Text files

The program uses the file "carrera.txt" where it keeps the number, horse name and rider name. It also needs a "puntuacio.txt" file in order to save the race results.

## Technologies used

* C
* [GCC](https://gcc.gnu.org) - GNU compiler

## Authors

* **[Rafael Díaz](https://github.com/palancana)**

  * Author and maintainer

* **[Mario Arias](https://github.com/Shooter9)**

  * Author and maintainer