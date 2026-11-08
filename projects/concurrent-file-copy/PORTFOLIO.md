# Portfolio notes

## Overview

A C++ operating-systems assignment implementing two concurrent file-copying programs.

## Engineering evidence

- Uses POSIX threads, a shared bounded queue, mutex protection and condition variables.
- The reader/writer design coordinates concurrent file access without busy waiting.
- Existing instructions cover Makefile builds and command-line execution.

## Contribution

The source README records pair-programming work with Jessica Bath across both tasks. This portfolio therefore describes the work as collaborative rather than attributing the entire implementation to one contributor.

## Validation

The repository includes executable build/run instructions and generated input guidance. A fresh test run has not been claimed in this snapshot.
