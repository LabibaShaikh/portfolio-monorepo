# Portfolio notes

## Overview

A C++ memory-management simulation comparing first-fit and best-fit allocation strategies.

## Engineering evidence

The implementation models free and allocated chunks with linked lists, expands the simulated heap with `sbrk`, deallocates blocks and merges adjacent free chunks to reduce fragmentation.

## Contribution

The source README identifies Shaikh Naima Labiba as the author and documents the allocation, deallocation and test-data workflow.

## Validation

The project provides a Makefile, a test-data generator and executable commands for both allocation strategies. A current clean build has not been claimed in this snapshot.
