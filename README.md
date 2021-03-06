# keno-cpp

## C++ Implementation Of The Keno Game

Keno is a popular gambling game with similarities to a lottery or bingo.

Players place a bet and choose anywhere from one to twenty numbers between 1 and 80, inclusive. Once the players have chosen their numbers, the game generates twenty random numbers between 1 and 80, and players receive a payoff based on how many numbers they picked that matched the chosen numbers.

For example, if a player picked seven numbers and all seven were chosen (very unlikely!), this player might win around $10.000 for a ten dollar bet. The actual payoffs are based on the probabilities of hitting k numbers out of n chosen.

You can read more about Keno [here](https://en.wikipedia.org/wiki/Keno)

## How To Build

To create a build of the game, on the base directory of the project run the following commands:

```shell
cmake -S ./ -B build
cmake --build build
```

### Windows and MinGW

If you are running this on a Windows machine and using MinGW as a compiler, you might want to use the following command instead. This will make sure you are using MinGW and prevent any futher issues that might occur.

```shell
cmake -S ./ -B build -G "MinGW Makefiles"
cmake --build build
```

Be aware that CMake uses a cache file, so if you are already using the proper Windows command and still facing issues on the build process, either delete the `CMakeCache.txt` file on the build directory or change your build directory to a new one.

## How To Run

Once you have builded the executable of the game, to play it, you can simply run:

```shell
./build/run
```
