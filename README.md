This is the compiled low-level version of Nebrix.

To start make sure you have the following installed:
- [cmake](https://cmake.org/)
- [make](https://www.gnu.org/software/make/)
- [gcc](https://gcc.gnu.org/)
- [gcc-multilib](https://packages.ubuntu.com/jammy/gcc-multilib)

Commands for Windows with scoop
```bash
scoop install cmake make gcc gcc-multilib
```

Commands to install the above packages on Ubuntu and Debian:
```bash
sudo apt install cmake make gcc gcc-multilib
```
For Arch Linux:
```bash
sudo pacman -S cmake make gcc gcc-multilib
```

Run the following commands for Windows:
```bash
mkdir build
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

Run the following commands for Linux:
```bash
mkdir build
cmake -S . -B build
cmake --build build
```

This will create a `nebrix` executable in the `build` directory.

## Usage
```bash
./build/nebrix <filename> -o <output name>
```

if you wish to save the assembly code to a file, use the `-s` flag:
```bash
./build/nebrix <filename> -o <output name> -s
```

if you want to clean up the build directory, use the `-c` flag:
```bash
./build/nebrix -c <exactable name>
```

Then run the output file with:
```bash
./<output name>
```