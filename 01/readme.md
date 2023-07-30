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

- This means that the #include directive in Code has been replaced
by the contents of the file it was referring to. That is why you see the content of the stdio.h header file (which we replaced with ellipses) 

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


- Our following example, example 1.6, is about a simple loop which is not
comparable to boost's foreach at all, but yet, it is giving you an idea on how
to use variadic macros for repeating a number of instructions


```c
#include <stdio.h>
#define LOOP_3(X, ...) \
 printf("%s\n", #X);
#define LOOP_2(X, ...) \
 printf("%s\n", #X); \
 LOOP_3(__VA_ARGS__)
#define LOOP_1(X, ...) \
 printf("%s\n", #X); \
 LOOP_2(__VA_ARGS__)
#define LOOP(...) \
 LOOP_1(__VA_ARGS__)
int main(int argc, char** argv) {
 LOOP(copy paste cut)
 LOOP(copy, paste, cut)
 LOOP(copy, paste, cut, select)
 return 0;
}

```



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

- The only way to create a loop with a macro is just to put the iteration instructions
one after another, and as some separate instructions. This means that a simple
macro loop with 1000 iterations will be substituted with 1000 instructions in
C and we won't have any actual C loop in the final code.


- The preceding technique will lead to a large binary size which can be thought
of as a disadvantage.
- But putting instructions one after another instead of putting them into a loop,
which is known as **loop unrolling** , has its own applications,
which require an acceptable level of performance in constrained and highperformance environments.
According to what we explained so far, it seems that
loop unrolling using macros is a trade-off between binary size and performance.
We talk more about this in the upcoming section.

- There is one more note about the preceding example. As you see, different usages
of the LOOP macro in the main function have produced different results. In the
first usage, we pass copy paste cut without any commas between the words.
The preprocessor accepts it as a single input, so the simulated loop has only
one iteration

## Advantages and disadvantages of macros

- Overusing the macros may not be a big issue for you,
but it might be for your teammates. But why is that?


- Macros have an important characteristic. If you write something in macros, they
will be replaced by other lines of code before the compilation phase, and finally,
you'll have a flat long piece of code without any modularity at compile time. Of
course, you have the modularity in your mind and probably in your macros, but
it is not present in your final binaries. This is exactly where using macros can
start to cause design issues.


- Software design tries to package similar algorithms and concepts in several
manageable and reusable modules, but macros try to make everything linear
and flat. So, when you are using macros as some logical building blocks
within your software design, the information regarding them can be lost after
the preprocessing phase, as part of the final translation units. That's why the
architects and designers use a rule of thumb about macros:

```txt
If a macro can be written as a C function, then you should write
a C function instead!
```
 - From the debugging perspective, again, it is said that macros are evil. A
developer uses compilation errors to find the places where there exist syntax
errors as part of their daily development tasks. They also use logs and possibly
compilation warnings to detect a bug and fix it. The compilation errors and
warnings both are beneficial to the bug analysis routine, and both of them are
generated by the compilers.

 - Regarding the macros, and especially with old C compilers, the compiler didn't
know anything about the macros and it was treating the compiling source (the
translation unit) as a long, linear, flat piece of code. So, for a developer looking at
the actual C code with macros and for the C compiler looking at the preprocessed
code without macros, there were two different worlds. So, the developer could
not understand easily what the compiler reported.

- A more general form of this trade-off is between having a single big
binary and having multiple small binaries. Both of them are providing the same
functionality, but the former can have a better performance.

 - The number of binaries used in a project, especially when the project is big, is
more or less proportional to the degree of modularization and the design effort
spent on it. As an example, a project having 60 libraries (shared or static) and one
executable seems to be developed according to a software plan which is splitting
dependencies into multiple libraries and using them in a single main executable.

- In other words, **when a project is being developed according to the software
design principals and best practices, the number of binaries and their sizes
are engineered in a careful way and usually will be comprised of multiple
lightweight binaries with applicable minimum sizes, instead of having a single
huge binary.** 

- Software design tries to have each software component in a suitable position
in a giant hierarchy instead of putting them in a linear order. And this is
intrinsically against the performance even though its effect on the performance
is tiny in most cases.

- So, we can conclude that the discussion regarding example 1.6 was about the
trade-off between design and performance. When you need performance,
sometimes you need to sacrifice the design and put things in a linear
construction. For example, you could avoid loops and use loop unrolling instead.


- From a different perspective, performance starts with choosing proper
algorithms for the problems defined in the design phase. The next step is usually
called optimization or performance tuning. In this phase, gaining performance is
equivalent to letting the CPU just compute in a linear and sequential manner
and not to force it to jump between different parts of the code. This can be done
either by modifying the already used algorithms or by replacing them with some
performant and usually more complex algorithms. This stage can come into
conflict with the design philosophy. As we said before, design tries to put things
in a hierarchy and make them non-linear, but the CPU expects things to be linear,
already fetched and ready to be processed. So, this trade-off should be taken care
of and balanced for each problem separately.

- Let's explain the loop unrolling a bit more. This technique is mostly used
in embedded development and especially in environments that suffer from
limited processing power. The technique is to remove loops and make them
linear to increase the performance and avoid the looping overhead while
running iterations.

- This is exactly what we did in example 1.6; we mimicked a loop with macros,
which led to a linear set of instructions. In this sense, we can say that the
macros can be used for performance tuning in embedded development and
the environments in which a slight change in the way that the instructions are
executed will cause a significant performance boost. More than that, macros can
bring readability to the code and we can factor out repeated instructions.

- Regarding the quote mentioned earlier that says that macros should be replaced
by equivalent C functions, we know that the quote is there for the sake of design
and it can be ignored in some contexts. In a context where improved performance
is a key requirement, having a linear set of instructions that lead to better
performance may be a necessity.

- Code generation is another common application of macros. They can be used for
introducing DSLs into a project. Microsoft MFC, Qt, Linux Kernel, and wxWidgets
are a few projects out of thousands that are using macros to define their own
DSLs. Most of them are C++ projects, but they are using this C feature to facilitate
their APIs.

- As a conclusion, C macros can have advantages if the impacts of their
preprocessed form are investigated and known. If you're working on a project
within a team, always share your decisions regarding the usage of the macros
in the team and keep yourself aligned with the decisions made within the team.

(宏 可用于 代码生成，但难以调试，一般可以写成C函数不要用宏，在极端追求 performance)
(使用 因为 cpu 在执行线性的代码时效率更高, 宏可以以loop的生成一条一条指令，避免了)
(使用 for loop 时 cpu 要不断的跳跃)














