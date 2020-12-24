# Description

[Doubly stochastic matrix](https://en.wikipedia.org/wiki/Stochastic_matrix) generator/checker.

You can use the program in two ways:

* To create doubly stochastic matrices.
* To check whether a matrix is doubly stochastic.

## Compile

Use the provided Makefile:

```bash
make markov
```

## Typical usage

Max number of rows is 10. The program will terminate without any message if this condition is not satisfied.

Examples:

* Create a 5x5 doubly stochastic matrix and write the result to stdout:

```bash
./markov -create 5
```

* Read matrix from input_file, check whether it is doubly stochastic and write the result to stdout:

```bash
./markov -check < input_file
```

## Sample files

See [tests](tests).
