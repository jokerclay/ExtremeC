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

# Conditional compilation
- Conditional compilation is another unique feature of C. It allows you to have
different preprocessed source code based on different conditions.
- Despite the
meaning it implies, the compiler is not doing anything conditionally, but **the
preprocessed code that is passed to the compiler can be different based on some
specified conditions.**  These conditions are evaluated by the preprocessor while
preparing the preprocessed code. There are different directives contributing to
the conditional compilation. You can see a list of them as follows:
    - `#ifdef` 
    - `#ifndef` 
    - `#else` 
    - `#elif` 
    - `#endif` 

- The following example, example 1.7, demonstrates a very basic usage of these
directives:


```c
#define CONDITION
int main(int argc, char** argv) {
#ifdef CONDITION
    int i = 0;
    i++;
#endif
    int j= 0;
    return 0;
}
```
- While preprocessing the preceding code, the preprocessor sees the CONDITION
macro's definition and marks it as **defined** . Note that no value is proposed for
the **CONDITION macro**  and this is totally valid.

- Then, the preprocessor goes down
further until it reaches the `#ifdef` statement. Since the CONDITION macro is
already defined, **all lines between #ifdef and #endif will be copied ** the final
source code.
- If the macro was not defined, we wouldn't see any replacement for the `#if-#endif` directives . 

- Macros can be defined using -D options passed to the
compilation command. Regarding the preceding example, we
can define the CONDITION macro as follows:

```bash
$ gcc -DCONDITION -E main.c
```
- This is a great feature because it allows you to have macros
**defined out of source files** .

- This is especially helpful when
having a single source code but compiling it for different
architectures, for example, Linux or macOS, which have
different default macro definitions and libraries.

- One of the very common usages of `#ifndef` is to serve as a `header guard`
statement. **This statement protects a header file from being included twice**in the
preprocessing phase, and we can say that almost all C and C++ header files in
nearly every project have this statement as their first instruction.

- an example on how to use a header guard
statement. Suppose that this is the content of a header file and by chance, it could
be included twice in a compilation unit. Note that example 1.8 is just one header
file and it is not supposed to be compiled:

```c
#ifndef EXAMPLE_1_8_H
#define EXAMPLE_1_8_H

void say_hello();
int read_age();

#endif
```

- As you see, **all variable and function declarations are put inside the #ifndef and
#endif pair and they are protected against multiple inclusions by a macro.**  In the
following paragraph, we explain how.

- As the first inclusion happens, the `EXAMPLE_1_8_H macro ` is not yet defined,
so the preprocessor continues by entering the `#ifndef-#endif` block.

- The next statement defines the `EXAMPLE_1_8_H macro`, and the preprocessor copies
everything to the preprocessed code until it reaches the `#endif` directive. 

- As the second inclusion happens, the `EXAMPLE_1_8_H ` macro is already defined, so
the preprocessor skips all of the content inside the `#ifndef-#endif` section and
moves to the next statement after `#endif`, if there is any.

- It is a common practice that the whole content of a header file is put between the
`#ifndef-#endif pair`, and nothing but comments are left outside.

- As a final note in this section, instead of having a pair of `#ifndef-#endif`
directives, one could use `#pragma once ` in order to protect the header file from
the **double inclusion issue.** 

- The difference between **conditional directives**  and the **#pragma once directive**  
is that **the latter is not a C standard** , despite the fact that
it is supported by almost all C preprocessors. 

- However, it is better to not to use it if portability of your code is a requirement.

- The following code box contains a demonstration on how to use #pragma once in
example 1.8, instead of #ifndef-#endif directives:

```c
#pragma once

void say_hello();
int read_age();
```

- we close the topic of preprocessor directives while we have demonstrated
some of their interesting characteristics and various applications. The next
section is about variable pointers, which are another important feature of C.


## Variable pointers
- The concept of a `variable pointer`, or for short pointer, is one of the most
fundamental concepts in C.

- You can hardly find any direct sign of them in most high-level programming languages. 
In fact, they have been replaced by some twin concepts, for example, `references in Java`.
It is worth mentioning that pointers are unique in the sense that the addresses they point to 
can be used directly by hardware, but this is not the case for the higher-level twin concepts
like references.

- Having a deep understanding about pointers and the way they work is crucial
to become a skilled C programmer.

- They are one of the most fundamental concepts in memory management, and despite their simple syntax, they have the potential to lead to a disaster when used in a wrong way.

- We will cover memory management-related topics in Chapter 4,
Process Memory Structure, and Chapter 5, Stack and Heap, but here in this chapter,

- we want to recap everything about pointers.

- If you feel confident about the basic terminology and the concepts
    surrounding the pointers, you can skip this section.

## Syntax

The idea behind any kind of pointer is very simple; 
it is just a simple variable that keeps a memory address.
The first thing you may recall about them is the asterisk character, `*`,
which is used for declaring a pointer in C. You can see
it in example 1.9. The following code box demonstrates how to declare and use
a variable pointer:


```c
int main(int argc, char** argv) {

    int var = 100;

    int* ptr = 0;

    ptr = &var;

    *ptr = 200;

    return 0;
}

```

- The preceding example has everything you need to know about the pointer's syntax. 

- The first line declares the var variable on top of the Stack segment.

- We will discuss the Stack segment in Chapter 4, Process Memory Structure. 

- The second line declares the pointer ptr with an initial value of zero.

- A pointer which has the zero value is called a null pointer.

- As long as the `ptr` pointer retains its zero value,

- it is considered to be a null pointer. It is very important to nullify a pointer if you
are not going to store a valid address upon declaration.

- As you see in Code Box 1-19, no header file is included.

- Pointers are part of the C language, and you don't need to have anything included to be able to use them.

- Indeed, we can have C programs, which do not include any header file at all.

- All of the following declarations are valid in C:

```c
int* ptr = 0;
int * ptr = 0;
int *ptr = 0;
```

- The third line in the main function introduces the `&` operator, which is called
the referencing operator. 

- It returns the address of the variable next to it. We need
this operator to obtain(获得) the address of a variable.

- Otherwise, we cannot initialize pointers with valid addresses.

- On the same line, the returned address is stored into the ptr pointer.
Now, the `ptr` pointer is not a null pointer anymore.

- On the fourth line, we see another operator `prior` to the pointer, 
which is called the **dereferencing operator**  and denoted by `*.`

- This operator allows you to have indirect access to the memory
cell that the ptr pointer is pointing to.

- In other words, it allows you to read and modify the var variable through the pointer that is pointing to it.
- The fourth line is equivalent to the `var = 200;` statement.

- A null pointer is not pointing to a valid memory address.

- Therefore, **dereferencing a null pointer must be avoided because it is considered
as an undefined behavior, which usually leads to a crash.** 

- As a final note regarding the preceding example, we usually have the default
macro NULL defined with value 0,
- and it can be used to nullify pointers upon declaration. 
- It is a good practice to use this macro instead of 0 directly because
**it makes it easier to distinguish between the variables and the pointers** :

    ```c
    char* ptr = NULL;
    ```

- It is crucial to remember that pointers must be initialized upon
declaration. 

- If you don't want to store any valid memory
address while declaring them, don't leave them uninitialized.

- Make it null by assigning 0 or NULL! Do this otherwise you may
face a fatal bug

- In most modern compilers, an uninitialized pointer is always nullified. 
- This means that the initial value is 0 for all uninitialized pointers.
- But this shouldn't be considered as an excuse to declare pointers without initializing them properly.

- Keep in mind that you are writing code for different architectures, old and new,
and this may cause problems on legacy systems.
- In addition, you will get a list of errors and warnings for these kinds of uninitialized pointers in most memory profilers. 
- Memory profilers will be explained thoroughly as part of Chapter 4,
Process Memory Structure, and Chapter 5, Stack and Heap.

## Arithmetic on variable pointers

- The simplest picture of memory is **a very long one-dimensional array of bytes** .

- With this picture in mind, if you're standing on one byte, you can only go back
and forth in the array;

- there's no other possible movement. So, this would be the
same for the pointers addressing different bytes in the memory.

- **Incrementing the pointer makes the pointer go forward**  and **decrementing it makes the pointer go
backward.**  

- **No other arithmetic operation is possible for the pointers.** 



Like we said previously, the arithmetic operations (算术运算) on a pointer are analogous(类似)
to the movements in an array of bytes.

- We can use this figure to introduce a new concept: 
**the arithmetic step size** .
- We need to have this new concept because
when you increment a pointer by 1, **it might go forward more than 1 byte** the memory.
- **Each pointer has an arithmetic step size** ,
- which means the number of bytes that the pointer will move if it is incremented or decremented by 1.
- **This arithmetic step size is determined by the C data type of the pointer.**

- In every platform, we have one single unit of memory and all pointers store the
addresses inside that memory.
- So, all pointers should have equal sizes in terms of bytes. 
- But this doesn't mean that all of them have equal arithmetic step sizes. 
- As we mentioned earlier, the arithmetic step size of a pointer is determined by its C data type.
- For example, an `int` pointer **has the same size as a**  `char` pointer,
- but they have different arithmetic step sizes.
- `int*` usually has a **4-byte**  arithmetic step size and `char* ` has a **1-byte**  arithmetic step size.
- Therefore, **incrementing an integer pointer makes it move forward by 4 bytes in the memory** 
(adds 4 bytes to the current address),

- and incrementing a character pointer makes it move forward
by **only 1 byte **  the memory. 

- The following example, example 1.10, demonstrates
the arithmetic step sizes of two pointers with two different data types:

```c
#include <stdio.h>

int main(int argc, char** argv) {

    int var = 1;

    int* int_ptr = NULL; // nullify the pointer

    int_ptr = &var;

    char* char_ptr = NULL;

    char_ptr = (char*)&var;

    printf("Before arithmetic: int_ptr: [%u], char_ptr: [%u]\n",
            (unsigned int)int_ptr, (unsigned int)char_ptr);

    int_ptr++;  // Arithmetic step is usually 4 bytes
    char_ptr++; // Arithmetic step in 1 byte

    printf("After  arithmetic: int_ptr: [%u], char_ptr: [%u]\n",
             (unsigned int)int_ptr, (unsigned int)char_ptr);

    return 0;
}


```
- output
```txt
Before arithmetic: int_ptr: [445793276], char_ptr: [445793276]
After  arithmetic: int_ptr: [445793280], char_ptr: [445793277]

```

- It is clear from the comparison of the addresses before and after the arithmetic
operations that the step size for the integer pointer is 4 bytes, and it is 1 byte for
the character pointer. If you run the example again, the pointers probably refer to
some other addresses, but their arithmetic step sizes remain the same:

- Now that you know about the arithmetic step sizes, we can talk about a classic
**example of using pointer arithmetic to iterate over a region of memory.** 

- The examples 1.11 and 1.12 are about to print all the elements of an integer array.

- The trivial approach without using the pointers is brought in example 1.11,
and the solution based on pointer arithmetic is given as part of example 1.12.
The following code box shows the code for example 1.11:

```c
#include <stdio.h>
#define SIZE 5

int main(int argc, char** argv) {
    int arr[SIZE];
    arr[0] = 9;
    arr[1] = 22;
    arr[2] = 30;
    arr[3] = 23;
    arr[4] = 18;

    for (int i = 0; i < SIZE; i++) {
        printf("%d\n", arr[i]);
    }

    return 0;
}
```
- The code in Code Box 1-23 should be familiar to you. It just uses a loop counter
to refer to a specific index of the array and read its content.
- But if you want to use pointers instead of accessing the elements via 
the indexer syntax (an integer between [ and ]), it should be done differently. 
The following code box demonstrates how to use pointers to iterate over the array boundary:

```c
#include <stdio.h>
#define SIZE 5

int main(int argc, char** argv) {

    int arr[SIZE];
    arr[0] = 9;
    arr[1] = 22;
    arr[2] = 30;
    arr[3] = 23;
    arr[4] = 18;

    int* ptr = &arr[0]; // 指向数组 第一个元素的 指针
    printf("%p\n",ptr);

    for (;;) {          // infinite loop

        printf("[%d] -> [%p] \n", *ptr, ptr);

        if (ptr == &arr[SIZE - 1]) {    // breaks when the address of the ptr pointer is the same as the last element of the array.
            break;
        }
        ptr++;
    }
    return 0;
}

```

- The second approach, demonstrated in Code Box 1-24, uses an **infinite loop** ,
which **breaks when the address of the ptr pointer is the same as the last element of the array.** 

- We know that arrays are adjacent variables inside the memory, 
- so incrementing and decrementing a pointer which is pointing to an element effectively makes it
move back and forth inside the array and eventually point to a different element.


-  As is clear from the preceding code, the **ptr pointer**  has the data type `int*`.

- That's because of the fact that it must be able to point to any individual element
of the array which is an integer of type int. 

- Note that all the elements of an array are from the same type hence they have equal sizes. 

- Therefore, incrementing the ptr pointer makes it point to the next element inside the array.

- As you see, before the for loop, ptr points to the first element of the array, and by further
increments, it moves forward along the array's memory region.
- This is a very classic usage of pointer arithmetic.

- Note that **in C, an array is actually a pointer that points to its first element.**  
- So, in the example, the actual data type of arr is `int*`.

- Therefore, we could have written the line as follows:
```c
int* ptr = arr;
```

- Instead of the line:
```c
int* ptr = &arr[0];
```

## Generic pointers

- A pointer of type `void*` is said to be a generic pointer.
- It can point to any address like all other pointers,
- but we don't know its actual data type hence
- we don't know its arithmetic step size.
- Generic pointers are usually used to hold the content of other pointers,
- but they forget the actual data types of those pointers. 
- Therefore, **a generic pointer cannot be dereferenced** ,
- and one **cannot do arithmetic on it because its underlying data type is unknown.**
- The following example, example 1.13, shows us that dereferencing a generic pointer
is not possible:

```c
#include <stdio.h>

int main(int argc, char** argv) {

    int var = 9;

    int* ptr = &var;

    void* gptr = ptr;

    printf("%d\n", *gptr);


    return 0;
}

```

```txt

gptr.c: In function ‘main’:
gptr.c:12:20: warning: dereferencing ‘void *’ pointer
   12 |     printf("%d\n", *gptr);
      |                    ^~~~~
gptr.c:12:20: error: invalid use of void expression

```

- As you see, both compilers don't accept dereferencing a generic pointer.

- In fact, it is meaningless to dereference a generic pointer! 

- So, what are they good for?

- In fact, generic pointers are very handy to **define generic functions that can
accept a wide range of different pointers as their input arguments.**  

- The following example, example 1.14, tries to uncover the details regarding generic functions:

```c
#include <stdio.h>

void print_bytes(void* data, size_t length) {

    char delim = ' ';

    unsigned char* ptr = data;

    for (size_t i = 0; i < length; i++) {
        printf("%c 0x%x", delim, *ptr);
        delim = ',';
        ptr++;
    }

    printf("\n");
}

int main(int argc, char** argv) {
    int a = 9;
    double b = 18.9;
    print_bytes(&a, sizeof(int));
    print_bytes(&b, sizeof(double));
    return 0;
}


```

- In the preceding code box, the `print_bytes` function receives an address as
a `void*` pointer and an **integer**  indicating the length.

- Using these arguments, the function prints all the bytes starting from the given address
up to the given length.

- As you see, **the function accepts a generic pointer, which allows the
user to pass whatever pointer they want.** 

- **Keep in mind that assignment to a void pointer (generic pointer) does not need an explicit cast. ** 

- That is why we have passed the addresses of a and b without explicit casts.

- Inside the `print_bytes` function, we have to use an unsigned char pointer in
order to move inside the memory.

- Otherwise, we cannot do any arithmetic on the void pointer parameter, data, directly. 

- As you may know, the step size of a `char*` or unsigned `char*` is one byte.

- So, it is the best pointer type for iterating
over a range of memory addresses one byte at a time and processing all of those
bytes one by one.

- As a final note about this example, `size_t` is a standard and unsigned data type
usually used for storing sizes in C.

## Size of a pointer
- If you search for the size of a pointer in C on Google, you may realize that you
cannot find a definitive answer to that.

- There are many answers out there, and it is true that you cannot define a fixed size for a pointer in different architectures.

- **The size of a pointer depends on the architecture rather than being a specific C concept.**  

- C doesn't worry too much about such hardware-related details,

- and it tries to provide a generic way of working with pointers and other programming concepts. 

- That is why we know C as a standard. Only pointers and the arithmetic on them are important to C.


- Architecture refers to the hardware used in a computer
system. You will find more details in the upcoming chapter,
Compilation and Linking


- You can always use the `sizeof` function to obtain the size of a pointer.

- It is enough to see the result of `sizeof(char*) `on your target architecture.
As a rule of thumb, **pointers are 4 bytes in 32-bit architectures and 8 bytes in 64-bit
architectures,**  
but you may find different sizes in other architectures.

- Keep in mind that **the code you write should not be dependent on a specific value for the
size of a pointer, and it should not make any assumptions about it. Otherwise,
you will be in trouble while porting your code to other architectures.** 


```c
#include <stdio.h>

int main() {

    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Size of char: %zu bytes\n", sizeof(char));
    printf("Size of float: %zu bytes\n", sizeof(float));
    printf("Size of double: %zu bytes\n", sizeof(double));
    printf("Size of long: %zu bytes\n", sizeof(long));

    int numbers[] = {10, 20, 30, 40, 50};

    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Size of the array: %zu bytes\n", sizeof(numbers));
    printf("Number of elements in the array: %d\n", size);

    return 0;
}
```

## Dangling pointers(悬挂指针)

- There are many known issues caused by misusing pointers. The issue of dangling
pointers is a very famous one.

- A pointer usually points to an address to which there is a variable allocated.

- Reading or modifying an address where there is no variable registered is a big
mistake and can result in a crash or a segmentation fault situation. 

- Segmentation fault is a scary error that every C/C++ developer should
have seen it at least once while working on code.

- This situation usually happens when you are misusing pointers. 
You are accessing places in memory that you
are not allowed to.

- You had a variable there before, but it is deallocated by now.

- Let's try to produce this situation as part of the following example, example 1.15:

```c
#include <stdio.h>

int* create_an_integer(int default_value) {
    int var = default_value;
    return &var;
}

int main() {
    int* ptr = NULL;
    ptr = create_an_integer(10);
    printf("%d\n", *ptr);
    return 0;
}

```

```txt
seg_fault.c: In function ‘create_an_integer’:
seg_fault.c:5:12: warning: function returns address of local variable [-Wreturn-local-addr]
    5 |     return &var;
      |

```
- This is indeed an important warning message which can be easily missed and
forgotten by the programmer. We'll talk more about this later as part of Chapter 5,
Stack and Heap.

- Let's see what happens if we proceed and execute the resulting executable.
When you run example 1.15, you get a segmentation fault error, and the program
crashes immediately:

```txt
./seg_fault
[1]    28356 segmentation fault  ./seg_fault

```

- So, what went wrong? The `ptr` pointer is dangling and points to an already
deallocated portion of memory that was known to be the memory place of the
variable, `var.`

- The var variable is a local variable to the `create_an_integer` function, and it
**will be deallocated after leaving the function** , but its address can be returned
from the function. 

- So, after copying the returned address into `ptr` as part of the
main function, `ptr` **becomes a dangling pointer pointing to an invalid address
in memory.**
- Now, dereferencing the pointer causes a serious problem and the program crashes.

- If you look back at the warning generated by the compiler, it is clearly stating
the problem.

- It says that **you are returning the address of a local variable, which will be
deallocated after returning from the function.**  

- Smart compiler! If you take these warnings seriously, you won't face these scary bugs.

- But what is the proper way to rewrite the example? Yes, **using the Heap memory.** 

- We will cover heap memory fully in Chapter 4, Process Memory Structure, and
Chapter 5, Stack and Heap,

- but, for now, we will rewrite the example using Heap
allocation, and you will see **how you can benefit from using Heap instead of the Stack.**

- Example 1.16 below shows **how to use Heap memory for allocating variables** , and
**enabling the passing addresses between functions**  without facing any issues:

```c
#include <stdio.h>
#include <stdlib.h>
int* create_an_integer(int default_value) {
    int* var_ptr = (int*)malloc(sizeof(int));
    *var_ptr = default_value;
    return var_ptr;
}
int main() {
    int* ptr = NULL;
    ptr = create_an_integer(10);
    printf("%d\n", *ptr);
    free(ptr);
    return 0;
}

```
- As you see in the preceding code box, we have included a new header file,
stdlib.h, and we are using **two new functions** , `malloc` and `free`.
- The simple explanation is like this:

- the created integer variable inside the `create_an_integer` function **is not a local variable anymore.** 

- Instead, **it is a variable allocated from the Heap memory and its lifetime is not limited to the function declaring it.**

- Therefore, **it can be accessed in the caller**  (outer) function. The
pointers pointing to this variable are not dangling anymore, 

- and they can be dereferenced as long as the variable exists and is not freed.

- Eventually, the variable becomes deallocated by calling the free function as an end to its
lifetime. 

- Note that deallocating a Heap variable is mandatory(强制的;必须履行的;法定的) when it is not needed anymore.

In this section, we went through all the essential discussions regarding variable
pointers. In the upcoming section, we'll be talking about functions and their anatomy(解剖学) in C


## Some details about functions
- C is a procedural programming language.

- In C, functions act as procedures, and they are building blocks of a C program.

-  So, it is important to know what they are, how they behave, and what is happening 
when you enter or leave a function.

- In general, functions (or procedures) are analogous(类似) to ordinary variables that
store algorithms instead of values. 

- By putting variables and functions together into a new type,
we can store relevant values and algorithms under the same concept.
This is what we do in object-oriented programming, and it will be covered in the third part of the book,
Object Orientation. In this section, we want to explore functions and discuss their properties in C.

## Anatomy of a function

- In this section, we want to recap everything about a C function in a single place.

- A function is a box of logic that has a name, a list of input parameters, and a list of
output results.
- In C and many other programming languages that are influenced by C,
**functions return only one value.** 

- In object-oriented languages such as C++ and Java, functions (which are usually called methods) can also throw an exception,
which is not the case for C.
- Functions are invoked by a function call, which is simply using the name of the function to execute its logic.
- **A correct function call should pass all required arguments to the function and wait for its execution.** 
- Note that functions are always blocking in C.
This means that **the caller has to wait for the called function to finish and only then can it collect the returned result.** 

- Opposite to a **blocking function** , we can have a **non-blocking function** .
- When calling a non-blocking function, the caller doesn't wait for the function to finish
and it can continue its execution. 

- In this scheme, there is usually a callback mechanism which is triggered when the called (or callee) function is finished.

- A non-blocking function can also be referred to as an asynchronous function or
simply an **async function** . 
- Since we don't have async functions in C, we need to
implement them using multithreading solutions.
- We will explain these concepts in more detail in the fifth part of the book, Concurrency.

- It is interesting to add that nowadays, there is a growing interest in using nonblocking functions over blocking functions.
- It is usually referred to as eventoriented programming(面向事件的编程).
 - Non-blocking functions are centric in this programming approach, and most of the written functions are non-blocking.

- In event-oriented programming, actual function calls happen inside an event loop,
and proper callbacks are triggered upon the occurrence of an event.

- Frameworks such as `libuv` and `libev` promote this way of coding, and they allow you to
design your software around one or several event loops.


## Importance in design
- Functions are fundamental building blocks of procedural programming.
Since their official support in programming languages, they have had a huge impact
on the way we write code.

- Using functions, we can store logic in semi-variable
entities and summon them whenever and wherever they are needed.

- Using them, we can write a specific logic only once and use it multiple times in various places.

- In addition, functions allow us to hide a piece of logic from other existing logic.

- In other words, they introduce a level of abstraction between various logical
components.

- To give an example, suppose that you have a function, `avg`, which
calculates the average of an input array.

- And you have another function, `main`, which calls the function, `avg`.
- We say that the logic inside the avg function is
hidden from the logic inside the main function.

- Therefore, if you want to change the logic inside avg, you don't need to change
the logic inside the main function.

- That's because the main function **only depends on the name** and 
the availability of the avg function. 

- This is a great achievement,
at least for those years when we had to use punched cards to write and execute programs!

- We are still using this feature in designing libraries written in C or even
higherlevel programming languages such as C++ and Java.


## Stack management

- If you look at the memory layout of a process running in a Unix-like operating
system, you notice that **all of the processes share a similar layout** .

- We will discuss this layout in more detail in Chapter 4,
Process Memory Structure, but for now, we want to introduce one of its segments;

- the Stack segment. 
The Stack segment is the default memory location where all local variables, arrays, and structures
are allocated from.
- So, when you declare a local variable in a function, it is being
allocated from the Stack segment. This allocation always happens on top of the
Stack segment.

- Notice the term **stack**  in the name of the segment. It means that this segment
**behaves like a stack** .

- **The variables and arrays are always allocated on top of it**, 
and those at the top are the first variables to get removed.

- Remember this analogy with the stack concept. We will return to this in the next paragraph.

- The **Stack segment is also used for function calls.**  
- When you call a function,
**a stack frame containing the return address and all of the passing arguments is put on top of the Stack segment,** 
and only then is the function logic executed.
- **When returning from the function, the stack frame is popped out,**
and the instruction addressed by the return address gets executed,
which should usually continue the caller function.

- **All local variables declared in the function body are put on top of the Stack segment.* 

- So, when leaving the function, all Stack variables become freed.

- That is why we call them local variables and that is why a function cannot access the
variables in another function.

- This mechanism also explains why local variables are not defined before entering a function and after leaving it.

- Understanding the Stack segment and the way it works is crucial to writing
correct and meaningful code. 

- It also prevents common memory bugs from occurring.

- It is also a reminder that **you cannot create any variable on the Stack with any size you like.**

- **The Stack is a limited portion of memory, and you could fill it up and potentially receive a stack overflow error.**

- This usually happens when we have too many function calls consuming up all the Stack segment by their stack frames.
This is very common when dealing with **recursive functions** , when a function calls itself without any break condition or limit.

## Pass-by-value versus pass-by-reference

- In most computer programming books, there is a section dedicated to `passby-value` and `pass-by-reference` regarding
the arguments passed to a function.

- Fortunately, or unfortunately, we have only pass-by-value in C

- **There is no reference in C** , so there is no pass-by-reference either.
- Everything is copied into the function's local variables, and you cannot read or modify them
after leaving a function.

- Despite the many examples that seem to demonstrate pass-by-reference function
calls, 

- I should say that passing by reference is an illusion in C. In the rest of this
section, we want to uncover this illusion and convince you that those examples
are also pass-by-value. The following example will demonstrate this:

```c
#include <stdio.h>

void func(int a) {
    a = 5;
}

int main(int argc, char** argv) {
    int x = 3;
    printf("Before function call: %d\n", x);
    func(x);
    printf("After function call: %d\n", x);
    return 0;
}

```


- It is easy to predict the output. Nothing changes about the x variable because it
is passed by value. The following shell box shows the output of example 1.17 and
confirms our prediction:

```txt
Before function call: 3
After function call: 3
```

The following example, example 1.18, demonstrates that passing by reference
doesn't exist in C:
```c
#include <stdio.h>
void func(int* a) {
    int b = 9;
    *a = 5;
    a = &b;
}
int main(int argc, char** argv) {
    int x = 3;
    int* xptr = &x;
    printf("Value before call: %d\n", x);
    printf("Pointer before function call: %p\n", (void*)xptr);
    func(xptr);
    printf("Value after call: %d\n", x);
    printf("Pointer after function call: %p\n", (void*)xptr);
    return 0;
}
```


```txt
Value before call: 3
Pointer before function call: 0x7ffcbc6cf274
Value after call: 5
Pointer after function call: 0x7ffcbc6cf274
```
- As you see, **the value of the pointer is not changed after the function call**.

- This means that the pointer is passed as a pass-by-value argument. 
Dereferencing the pointer inside the func function has allowed accessing the variable where
the pointer is pointing to.

- But you see that changing the value of the pointer
parameter inside the function doesn't change its counterpart argument in
the caller function.

- During a function call in C, all arguments are passed by
value and dereferencing the pointers allows the modification of the caller
function's variables.

- It is worth adding that the above example demonstrates a pass-by-pointer
example in which we pass pointers to variables instead of passing them directly.

- It is usually recommended to use pointers as arguments instead of passing big
objects to a function but why?

- It is easy to guess. Copying 8 bytes of a pointer
argument is much more efficient than copying hundreds of bytes of a big object.

- Surprisingly, passing the pointer is not efficient in the above example! That's
because of the fact that the int type is 4 bytes and copying it is more efficient
than copying 8 bytes of its pointer.
- But this is not the case regarding structures and arrays.
Since copying structures and arrays is done byte-wise, and all of the
bytes in them should be copied one by one, it is usually better to pass
pointers instead.

- Now that we've covered some details regarding the functions in C, let's talk
about function pointers.


## Function pointers




