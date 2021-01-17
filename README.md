# libCoinGecko
A c++ API wrapper for Coin Gecko

## Setup
You must first install the http library used

Install [cpp-httplib](https://github.com/yhirose/cpp-httplib)
```bash
git clone https://github.com/yhirose/cpp-httplib.git
cd cpp-httplib
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DHTTPLIB_COMPILE=on -DBUILD_SHARED_LIBS=on ..
sudo cmake --build . --target install
```

Now install this library
```bash
https://github.com/FloppyDisck/libCoinGecko.git
cd libCoinGecko
mkdir -p build
cd build
cmake -DMAKE_BUILD_TYPE=Release ..
sudo make install
```

If you would like to run the tests yourself you must first compile the testers, dont worry, cmake will handle all the setup
```bash
https://github.com/FloppyDisck/libCoinGecko.git
cd libCoinGecko
mkdir -p build_test
cd build_test
cmake -DMAKE_BUILD_TYPE=Debug -DMAKE_TESTS=true ..
sudo make install
make -j4
./test/test
```

## Using the API
The api is build in a more function oriented way, this means all you need to do to call the necessary info is just 
call a function and feed the necessary arguments

First add the library
```cpp
#include "coingecko.hpp"
```

Here I demonstrate how to get the top 7 most trending currencies 
```cpp
std::string response = coingecko::trending();
```
Now to properly parse this I would recommend to use the json library of your choice
