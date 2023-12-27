# Logger

It's a simple logger made in C.

NOTE: Still in development.

# Usage

- Log to the console and outputs the log into a text file that you can set to.
- You can make your own logging text with it, as in logging level.

## C / C++

To use this header file, you must acknowledge that there are two different functions to log: the already defined ones and the custom one.

### Initialization of the lib

To initialize this lib you must use the "file_init" function.

```c
file_init();
```

### The standard one (non-customizable)

It works with a function and a set of enums that are used in an array of structures called "log\_data\_type" and the name of the array is "log\_level".

To undestand the use of enum you must remember two things:

- Use the "log" function;

- Use the enums as the first argument.

And to finally tell you the enums and their use:

- LOG\_INFO - Will print "[INFO] ..." with a white label;

- LOG\_WARNING - Will print "[WARNING] ..." with a yellow label;

- LOG\_ERROR - Will print "[ERROR] ..." with a red label;

- LOG\_PANIC - Will print "[PANIC] ..." with a red label but will also exit the program.

The function looks like this:

```c
void log(bool log_to_file, short level, char* args, ...);
```
The explanation of the function:

- log\_to\_file -> a boolean (1 or 0) that tells if the log should be saved to a function;

- level -> makes use of the enums that were explained before;

- args -> the arguments given to the function to log to a file.

EXAMPLES (from the main.c file):
```c
log(false, LOG_INFO, "Informations....");
log(false, LOG_WARNING, "This is soooo coooooooool!!!!");
log(false, LOG_ERROR, "Uh oh... ", "This is big stuff now...");
```

### The custom logging

To log with a custom logging symbol (or simply said another text inside the brackets) you'll need to use another set of enums (yipee).

It's a lot easier because it's just words that represent colors:

- RED -> red color;
- YELLOW -> yellow color;
- and so on.

And the symbol you want to use (or text inside the brackets).

The could should look like this:

```c

struct custom_log_level test_custom_log = {
	WHITE,
	"Test",
};

```

And to actually use the log:

```c
// It starts the same way as the log function
custom_log(false, test_custom_log, "Parry ", "this ", "you ", "filthy ", "casual.");
```

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
