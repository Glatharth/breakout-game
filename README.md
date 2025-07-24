# Breakout Game

Breakout is a classic arcade game where you control a paddle to bounce a ball and break all the blocks on the screen. This project is implemented in C using the [raylib](https://www.raylib.com/) library for graphics, audio, and input handling.

## Features

- Classic Breakout gameplay
- Sound effects and background music
- Custom graphics and resources

## Project Structure

- `src/`: Source code (`.c` and `.h` files)
- `src/include/`: Header files and raylib headers
- `resources/`: Game assets (images, music, sound effects)
- `lib/`: Precompiled raylib libraries
- `build/`: Build output directory
- `Makefile`: Build and run automation

## Requirements

- GCC (C compiler)
- [raylib](https://www.raylib.com/) (For windows, you can use the static library in `lib/`)
- `make` utility

### Building on Windows

- Run `build.bat` to compile the game using the static raylib library included in the `lib/` directory.

### Installing raylib on Linux

You can install raylib using [wiki instructions](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux).

### Building the Game

To build the game, open a terminal in the project root and run:
```sh
make
```
The compiled binary will be placed in build/breakout.

### The Game
After building, run the game with:
```sh
./build/breakout
```

### Resources

- Images: resources/images/
- Music: resources/musics/
- Sound Effects: resources/sfx/

### Credits

- Project structure created by [David Buzatto](https://github.com/davidbuzatto)
- Code and game logic by [Paulo Henrique Lisboa](https://github.com/glatharth/) and [Lucas Carrion](https://github.com/CarrinLucas)
- Developed using [raylib](https://www.raylib.com/)