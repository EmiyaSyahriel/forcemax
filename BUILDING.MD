# Building Steps
#### Common Prerequisites
- Git Client, e.g
  - `git` command
  - GitHub Desktop

### Using Visual Studio (2019/2022)
May also applicable to Visual Studio Code

#### Prerequisites
- Visual Studio CMake Integration

#### Steps
- Clone the repo somewhere in to your local machine
- Open Visual Studio
- On Project Selection, click on `Open local folder`, browse to where you cloned the source code
- Wait for the configuration to be done
- On the target selection, choose `forcemax.exe`
- Click the Green Play button to build and start the app

### Using MINGW
#### Prerequisites
- CMake
- GCC
- either Ninja or GNU Make

#### Steps
```bat
:: cd to somehere you would like to save the source code
git clone https://github.com/EmiyaSyahriel/forcemax
cd forcemax
:: You can use "Unix Makefiles" for GNU Make instead of "Ninja" here
cmake -G "Ninja" -B build -DCMAKE_BUILD_TYPE=MinSizeRel
cd build
:: Or `make` if you uses GNU Make
ninja
:: the program binary will be in the build folder
```

### Direct Compilation
The entire app is comprised in a single `.c` file in the `src` directory, you can just throw the 
file to a C Compiler and link the binary to Windows' `user32` system library to build the app
