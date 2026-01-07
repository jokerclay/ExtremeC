# Chapter 03 Object Files

- This chapter details the various products that a C/C++ project can have.

- Possible products include 
    - **relocatable object files,**
    - **executable object files,**  
    - **static libraries,**  
    - **shared object files.**  

- However, relocatable object files are considered to be temporary products and 
they act as ingredients(原料) for making other types of products that are final.

- It seems that today in C, it's crucial(至关重要的) to have further discussion about the various
types of object files and their internal structures. 

- The majority of C books only talk about the C syntax and the language itself;

- but, in real-world you need more in-depth knowledge to be a successful C programmer.

- When you are creating software, it is not just about the development and the
programming language.

- In fact, it is about the whole process: writing the code,
compilation, optimization, producing correct products, and further subsequent
steps,
- in order to run and maintain those products on the target platforms.

- You should be knowledgeable about these intermediate steps, to the extent
that you are able to solve any issues you might encounter. 

- This is even more serious regarding embedded development, as the hardware architectures and the instruction sets can be challenging and atypical(非典型的).

- This chapter is divided into the following sections:

1. **Application binary interface** : Here, we are first going to talk about the
Application Binary Interface (ABI) and 

2. **Object file formats** : In this section, we talk about various object file
formats that exist today or they have become obsolete(过时的) over the years.
We also introduce ELF as the most used object file format in Unix-like systems.

3. **Relocatable object files** : Here we discuss relocatable object files and the
very first products of a C project. We take a look inside ELF relocatable
object files to see what we can find there. 

4. **Executable object files** : As part of this section, we talk about the
executable object files. We also explain how they are created from a
number of relocatable object files. We discuss the **differences between ELF** 
**relocatable**  and **executable object files **  terms of their **internal structure**.

5. **Static library** : In this section, we talk about static libraries and how we
can create them. We also demonstrate how to write a program and use
already built static libraries.

6. **Dynamic library** : Here we talk about shared object files. We demonstrate
how to create them out of a number of relocatable object files and how to
use them in a program. We also briefly talk about the internal structure of
an ELF shared object file.

### Application binary interface (ABI)

- As you may already know, every library or framework, regardless of the
technologies or the programming language used, exposes a set of certain
functionalities, which is known as its  **Application Programming Interface (API).** 

- If a library is supposed to be used by another code, then the consumer code
should use the provided API. To be clear, nothing other than the API should be
used in order to use a library because it is the public interface of the library and
everything else is seen as a black box, hence cannot be used.

- Now suppose after some time, the library's API undergoes some modifications.
In order for the consumer code to continue using the newer versions of the
library, the code must adapt itself to the new API; otherwise, it won't be able to
use it anymore. The consumer code could stick to a certain version of the library
(maybe an old one) and ignore the newer versions, but let's assume that there is
a desire to upgrade to the latest version of the library.


- To put it simply, an API is like a convention (or standard) accepted between
two software components to serve or use each other. An ABI is pretty similar
to API, but at a different level.

- While the API guarantees the compatibility of two software components to continue
their functional cooperation, the ABI guarantees that two programs are compatible at
the level of their machine-level

- For instance, a program cannot use a dynamic or static library that has han that,
an executable file (which is, in fact, an object file) cannot be run on a system
supporting a different ABI than the one that the executable file was built for.
A number of vital(必不可少的) and obvious system
functionalities, such as dynamic linking, loading an executable, and function calling
convention, should be done precisely according to an agreed upon ABI. 


- An ABI will typically cover the following things:
    -  The instruction set of the target architecture, which includes the processor
    instructions, memory layout, endianness, registers, and so on.
    - Existing data types, their sizes, and the alignment policy.
    - The function calling convention describes how functions should be called.
    For example, subjects like the structure of the stack frame and the pushing
    order of the arguments are part of it.
    - Defining how system calls should be called in a Unix-like system.
    - Used object file format, which we will explain in the following section,
    for having relocatable, executable, and shared object files.
    - Regarding object files produced by a C++ compiler, the name mangling,
    virtual table layout, is part of the ABI.

- The **System V ABI**  is the most widely used ABI standard among Unix-like
operating systems like Linux and the BSD systems. Executable and Linking
Format (**ELF** ) is the standard object file format used in the System V ABI.

- Note:
- The following link is the System V ABI for AMD 64-
bit architecture: [psABI-x86](https://www.uclibc.org/docs/psABI-x86_64.pdf) .
You can go through the list of contents and see the areas it covers.
- In the following section, we will discuss the object file formats, particularly ELF.

### Object file formats
As we explained in the previous chapter, Chapter 2, Compilation and Linking,
on a platform, **object files have their own specific format for storing machinelevel instructions.** 

- Note that this is about the structure of object files and this is
different from the fact that each architecture has its own instruction set.

- As we know from the previous discussion, these two variations are different parts of the
ABI in a platform; the object file format and the architecture's instruction set.

- In this section, we are going to have a brief look into some widely known object
file formats. To start with, let's look at some object file formats used in various
operating systems:
    - **ELF**     used by Linux and many other Unix-like operating systems
    - **Mach-O**  used in OS X (macOS and iOS) systems
    - **PE**  used in Microsoft Windows





