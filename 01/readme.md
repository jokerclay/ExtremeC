# Chapter 01 Essential Features

- This first chapter is primarily concerned with particular features of C that
you'll find extremely useful while you're writing C programs

-  We'll explore the following topics:
    - Preprocessor directives, macros, and conditional compilation:
        - Preprocessing brings a lot of advantages, and we'll dive into some of
          its interesting applications, including macros and conditional 
          directives.
    - Variable pointers
    - Functions:
        - the syntax is the
          easy part! In this section, we will look at functions as the building blocks
          for writing procedural code. This section also talks about the function call
          caller function.
    - Function pointers:
        - Undoubtedly, function pointers are one of the most
            important features of C. A function pointer is a pointer that points to
            an existing function instead of a variable. The ability to store a pointer to
            an existing logic is profoundly important in algorithm design, and that's
            why we have a dedicated section on this topic. Function pointers appear
            in a vast range of applications ranging from loading dynamic libraries to
            polymorphism,
    - Structures: 
    - C structures might have a simple syntax and convey a simple
        idea, but they are the main building blocks for writing well-organized
        and more object-oriented code. Their importance, together with function
        pointers, simply cannot be overstated! In the last section of this chapter,
        we'll revisit all the things that you need to know about structures in C
        and the tricks around them.

## Preprocessor directives

- now let's define preprocessing as something
that allows you to engineer and modify your source code **before** submitting
it to the compiler.

- This means that the C compilation pipeline has at least one
    step more in comparison to other languages
-  In other programming languages,the source code is directly sent to the 
    compiler, but in C and C++, it should be preprocessed first.
- This extra step has made C (and C++) a unique programming language in the
sense that a C programmer can effectively change their source code before
submitting it to the compiler. This feature is not present in most higher-level
programming languages.
- The purpose of preprocessing is to remove the preprocessing directives and
substitute them with equivalent generated C code and prepare a final source
that is ready to be submitted to the compiler

- The behavior of the C preprocessor can be controlled and influenced using
a set of directives. C directives are lines of code starting with a # character
in both header and source files. These lines are only meaningful to the C
preprocessor and never to the C compiler. There are various directives in C,
but some of them are very important especially the directives used for macro
definition and the directives used for conditional compilation.

## Macros
- There are many rumors regarding C macros. One says that they make your
source code too complicated and less readable.
-  Another says that you face issues
while debugging applications if you have used macros in your code
- The reality is that you'll find macros in any well-known C project. As proof,
download a well-known C project such as Apache HTTP Server and do a grep
for #define. You will see a list of files where macros are defined.

- For you as a C developer, there is no way to escape macros. Even if you don't
use them yourself,you will likely see them in other people's code.
Therefore, you need to learn what they are and how to deal with them.

- Macros have a number of applications and you can see some of them as follows:
    - Defining a constant
    - Using as a function instead of writing a C function
    - Loop unrolling
    - Header guards
    - Code generation
    - Conditional compilation


## Defining a macro
- Macros are defined using the #define directive. Each macro has a name and a
possible list of parameters. It also has a value that gets substituted by its name in
the preprocessing phase through a step called macro expansion. A macro can also be
undefined with the #undef directive.


```c
#define ABC 5
int main(int argc, char** argv) {
    int x = 2;
    int y = ABC;
    int z = x + y;
    return 0;
}
```
- `ABC`  is not a variable that holds an integer value nor an
integer constant. In fact, it's a macro called `ABC`  and its corresponding value is 5.
After the macro expansion phase, the resulting code that can be **submitted**  to the
C compiler

-  the preprocessor simply **replaced the macro's name with its value** . 
The preprocessor has also removed the comments on the beginning lines. 

- another example

```c
#define ADD(a, b) a + b
int main(int argc, char** argv) {
    int x = 2;
    int y = 3;
    int z = ADD(x, y);
    return 0;
}
```

-  ADD is not a function. It is just a function-like macro that accepts arguments.
After preprocessing, the resulting code will be like this:
```c
int main(int argc, char** argv) {
    int x = 2;
    int y = 3;
    int z = x + y;
    return 0;
}
```

- The argument x used as parameter a is replaced with all instances of
a in the macro's value. This is the same for the parameter b, and its corresponding
argument y. Then, the final substitution occurs, and we get x + y instead of
ADD(a, b) in the preprocessed code.

- Since function-like macros can accept input arguments, they can mimic
C functions. In other words, instead of putting a frequently used logic into
a C function, you can name that logic as a function-like macro and use that
macro instead.

- This way, the macro occurrences will be replaced by the frequently used logic,
as part of the preprocessing phase, and there is no need to introduce a new
C function


- Macros only exist before the compilation phase. This means that the compiler,
theoretically, doesn't know anything about the macros. This is a very important
point to remember if you are going to use macros instead of functions.
The compiler knows everything about a function because it is part of the
C grammar and it is parsed and being kept in the parse tree. But a macro is just
a C preprocessor directive only known to the preprocessor itself.

- Macros allow you **to generate code**  before the compilation. In other programming
languages such as **Java, you need to use a code generator to fulfill this purpose**.
Wewill give examples regarding this application of macros.


- Modern C compilers are aware of C preprocessor directives. Despite the
common belief that they don't know anything about the preprocessing phase,
they actually do. The modern C compilers know about the source before entering
the preprocessing phase. 

```c
#include <stdio.h>
#define CODE \
    printf("%d\n", i);

int main(int argc, char** argv) {
    CODE
        return 0;
}

```

- If you compile the above code using clang in macOS, the following would be
the output:

```text
$ clang example.c
code.c:7:3: error: use of undeclared identifier 'i'
CODE
^
code.c:4:16: note: expanded from macro 'CODE'
printf("%d\n", i);
 ^
1 error generated.
$
```

- As you see, the compiler has generated an error message that points exactly
to the line in which the macro is defined.

- As a side note, in most modern compilers, you can view the preprocessing result
just before the compilation. For example, when using gcc or clang, you can use
the -E option to dump the code after preprocessing. The following shell box
demonstrates how to use the -E option. Note that the output is not fully shown:

```text
$ clang -E example.c
# 1 "sample.c"# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 361 "<built-in>" 3
...
# 412 "/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/
usr/include/stdio.h" 2 3 4
# 2 "sample.c" 2
...
int main(int argc, char** argv) {
    printf("%d\n", i);
    return 0;
}
$
```
- Now we come to an important definition. **A translation unit (or a compilation unit)** 
is the preprocessed C code that is ready to be passed to the compiler.

- In a translation unit, all directives are substituted with inclusions or macro
expansions and a flat long piece of C code has been produced.

- Now that you know more about macros, let's work on some more difficult
examples
- They will show you the power and danger of macros. In my opinion,
extreme development deals with dangerous and delicate stuff in a skilled way,
and this is exactly what C is about.

```c
#include <stdio.h>
#define PRINT(a) printf("%d\n", a);
#define LOOP(v, s, e) for (int v = s; v <= e; v++) {
#define ENDLOOP }
int main(int argc, char** argv) {
 LOOP(counter, 1, 10)
 PRINT(counter)
 ENDLOOP
 return 0;
}

```


- As you see in the preceding code box, the code inside the main function is not
a valid C code in any way! But after preprocessing, we get a correct C source
code that compiles without any problem. Following is the preprocessed result


```text
...
... content of stdio.h …
...
int main(int argc, char** argv) {
 for (int counter = 1; counter <= 10; counter++) {
 printf("%d\n", counter);
 }
 return 0;
}

```

- in the main function, we just used a different and not C-looking
set of instructions to write our algorithm.
- we got a fully functional and correct C program. This is an important
application of macros;

**to define a new `domain specific language (DSL)` and write code using it.**  

- DSLs are very useful in different parts of a project; for example, they are used
heavily in testing frameworks such as Google Test framework (`gtest`) where
a DSL is used to write assertions, expectations, and test scenarios

- We should note that we don't have any C directives in the final preprocessed
code

- This means that the #include directive in Code  has been replaced
by the contents of the file it was referring to. That is why you see the content of
the stdio.h header file (which we replaced with ellipses) 

- two new operators regarding macro parameter, the `#`  and `##`  operators:


```c
#include <stdio.h>
#include <string.h>

#define CMD(NAME) \
    char NAME ## _cmd[256] = ""; \
    strcpy(NAME ## _cmd, #NAME);



int main(int argc, char** argv) {
    CMD(copy)
        CMD(paste)
        CMD(cut)
        char cmd[256];
    scanf("%s", cmd);
    if (strcmp(cmd, copy_cmd) == 0) {
        // ...
    }
    if (strcmp(cmd, paste_cmd) == 0) {
        // ...
    }
    if (strcmp(cmd, cut_cmd) == 0) {
        // ...
    }
    return 0;
}


```

- While expanding the macro, the `#` operator turns the **parameter**  into 
**its string form surrounded by a pair of quotation marks** .

- For example, in the preceding code, the # operator used before the NAME parameter 
turns it into "copy" in the preprocessed code.

- The `##`   operator has a different meaning. It just concatenates the parameters
to other elements in the macro definition and usually forms variable names. 


```text

    banner("# and ## ");

    char copy_cmd[256] = ""; strcpy(copy_cmd, "copy");
        char paste_cmd[256] = ""; strcpy(paste_cmd, "paste");
        char theparam_cmd[256] = ""; strcpy(theparam_cmd, "theparam");
        char cut_cmd[256] = ""; strcpy(cut_cmd, "cut");
        char cmd[256];
    scanf("%s", cmd);
    if (strcmp(cmd, copy_cmd) == 0) {

    }
    if (strcmp(cmd, paste_cmd) == 0) {

    }
    if (strcmp(cmd, cut_cmd) == 0) {

    }
    if (strcmp(cmd, theparam_cmd) == 0) {

    }

    return 0;

```

 - Note that, in the final preprocessed code, all lines expanded from the same 
 macro definition are on the same line.


- It is a good practice to break long macros into multiple
lines but do not forget to use `\` (one backslash) to let the
preprocessor know that the rest of the definition comes on the
next line. Note that `\` doesn't get substituted with a newline
character. Instead, it is an indicator that the following line is
the continuation of the same macro definition.


## Variadic macros
- Variadic macros are function-like macros that contain a variable number of arguments.
- The next example, , is dedicated to variadic macros, which can accept a
variable number of input arguments. Sometimes the same variadic macro accepts
2 arguments, sometimes 4 arguments, and sometimes 7.
- Variadic macros are very handy when you are not sure about the number of arguments in different usages
of the same macro. A simple example is given as follows:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VERSION "2.3.4"
#define LOG_ERROR(format, ...) \
 fprintf(stderr, format, __VA_ARGS__)
int main(int argc, char** argv) {
 if (argc < 3) {
 LOG_ERROR("Invalid number of arguments for version %s\n.",
VERSION);
 exit(1);
 }
 if (strcmp(argv[1], "-n") != 0) {
 LOG_ERROR("%s is a wrong param at index %d for version %s.",
argv[1], 1, VERSION);
 exit(1);
 }
 // ...
 return 0;
}

```


- a new identifier: `__VA_ARGS__`. It is an
indicator that tells the preprocessor to replace it with all the remaining input
arguments that are not assigned to any parameter yet.

- in the second usage of `LOG_ERROR`, according to
the macro definition, the arguments `argv[1]`, `1` , and `VERSION` are those input
arguments that are not assigned to any parameter. So, they are going to be used
in place of `__VA_ARGS__` while expanding the macro.

- As a side note, the function fprintf writes to a file descriptor

- the file descriptor is `stderr`, which is the error stream of the process.

- Also, note the ending semicolon after each `LOG_ERROR` usage.
It is mandatory because the macro doesn't supply them as part of its definition
and the programmer must add that semicolon to make the final preprocessed code syntactically correct.

- The next example,  is a progressive usage of variadic macros that
tries to mimic a loop. There is a well-known example about this.

- Before having foreach in C++, the boost framework was (and still is) offering 
the foreach behavior using a number of macros.


```txt
int main(int argc, char** argv) {

# 113 ".\\main.c"

    printf("%s\n", "copy paste cut"); printf("%s\n", ""); printf("%s\n", "");
    printf("%s\n", "copy"); printf("%s\n", "paste"); printf("%s\n", "cut");
    printf("%s\n", "copy"); printf("%s\n", "paste"); printf("%s\n", "cut");

    return 0;
}
```

- if you look at the preprocessed code carefully, you will see that the `LOOP`
macro has been expanded to multiple printf instructions instead of looping
instructions such as `for` or `while`.

-  It is obvious why this is the case, and it's
because of the fact that the **preprocessor doesn't write smart C code for us**.

- **It is there to replace macros with the instructions given by us.** 



