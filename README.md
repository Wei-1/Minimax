# Minimax

Wei's C++ Minimax Template

## Abstract

To play against all those talented players in gaming AI,

a Minimax Template will be very helpful in a lot of cases.

## How to use

To test the Minimax Function, there are 2 examples in this repo.

I wrote a small script `c11` to make it easier.

Compile the script and run it with the following:

```bash
./c11 ../cg_tmp/Minimax-Template.cpp temp.o
./temp.o
```

## Examples

#### Car Race Example

```bash
./c11 ../cg_tmp/Minimax-Carrace.cpp carrace.o
./carrace.o
```

Carrace example will only run for 2 rounds.

Since there is only 1 dimension.

You want to pick the highest speed for your car.

#### Ghost Example

The agent will try to avoid being catched by the ghost. (the other unit)

```bash
./c11 ../cg_tmp/Minimax-Ghost.cpp ghost.o
./ghost.o
```

## References

This structure of this agent template is highly based on:

https://github.com/git-knight/mad-starter

The algorithm in this repo is basically the direct duplication of:

https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning#Pseudocode

