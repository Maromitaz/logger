# Logger

It's a simple logger made in C.

NOTE: Still in development.

# Usage

- Log to the console and outputs the log into a text file that you can set to.
- You can make your own logging text with it, as in logging level.

# Compiling

Here I must mention that the compiling steps are to compile for testing. If you wish to compile the code and link it to your project, you can just drag and drop it and use as a header file.

### [Premake5](https://premake.github.io/)

Depending on your OS, you can use the "premake5" command and make your working/compiling enviorment.

- Windows

```bash
premake5 vs2022
```

It'll create and configure your Visual Studio enviorment to compile the code for testing.

NOTE: You can use any vs version from 2005 all the way to vs2022. For more information please check the [premake5 docs](https://premake.github.io/).

- Linux

```bash
premake5 gmake2
```

It'll create a Makefile for you to run.

- MacOS

```bash
premake5 xcode4
```

NOTE: I don't use any Apple related hardware, nor software.

- Cross-platform

```bash
premake5 codelite
```

It'll create a [CodeLite](https://codelite.org/) project for you to run and compile.

NOTE: I don't use this IDE, I don't know if it works as intended.
