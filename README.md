[![Benchmark](https://github.com/lukki15/JigChecker/actions/workflows/benchmark.yml/badge.svg)](https://github.com/lukki15/JigChecker/actions/workflows/benchmark.yml)
[![Documentation](https://github.com/lukki15/JigChecker/actions/workflows/documentation.yaml/badge.svg)](https://github.com/lukki15/JigChecker/actions/workflows/documentation.yaml)
[![Install](https://github.com/lukki15/JigChecker/actions/workflows/install.yml/badge.svg)](https://github.com/lukki15/JigChecker/actions/workflows/install.yml)
[![MacOS](https://github.com/lukki15/JigChecker/actions/workflows/macos.yml/badge.svg)](https://github.com/lukki15/JigChecker/actions/workflows/macos.yml)
[![Standalone](https://github.com/lukki15/JigChecker/actions/workflows/standalone.yml/badge.svg)](https://github.com/lukki15/JigChecker/actions/workflows/standalone.yml)
[![Standalone](https://github.com/lukki15/JigChecker/actions/workflows/standalone.yml/badge.svg)](https://github.com/lukki15/JigChecker/actions/workflows/standalone.yml)
[![Ubuntu](https://github.com/lukki15/JigChecker/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/lukki15/JigChecker/actions/workflows/ubuntu.yml)
[![Windows](https://github.com/lukki15/JigChecker/actions/workflows/windows.yml/badge.svg)](https://github.com/lukki15/JigChecker/actions/workflows/windows.yml)

# JigChecker

Inspired by the Matt Parker's video [How can a jigsaw have two distinct solutions?](https://youtu.be/b5nElEbbnfU?si=3KUICM_pbIy2_dEU).

## Usage

### Build and run the standalone target

Use the following command to build and run the executable target.

```bash
cmake -S standalone -B build/standalone
cmake --build build/standalone
./build/standalone/JigChecker --help
```

### Build everything at once

The project also includes an `all` directory that allows building all targets at the same time.
This is useful during development, as it exposes all subprojects to your IDE and avoids redundant builds of the library.

```bash
cmake -S all -B build
cmake --build build

# run tests
./build/test/JigCheckerTests
# format code
cmake --build build --target fix-format
# run standalone
./build/standalone/JigChecker --help
# build docs
cmake --build build --target GenerateDocs
```
