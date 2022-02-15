# Markov matrices

[Doubly stochastic matrix](https://en.wikipedia.org/wiki/Stochastic_matrix) generator/checker.

You can use the program in two ways:

* To create doubly stochastic matrices.
* To check whether a matrix is doubly stochastic.

This is a very simple program which always allocates a two-dimensional 10x10 array. Therefore matrices up to 10x10 can be generated and checked if they are valid.

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

## Tests

See [tests](tests). Two input .in files are provided and their corresponding .out files.

## Profiling

'markov' has been tested for memory leaks with [AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer).
