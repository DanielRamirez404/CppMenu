# How to run the tests

> [!NOTE]
> Requirements: ```CMake``` configured with your preferred build system, and a ```C++``` compiler previously installed.  

You can just build the ```Tests``` executable file by running this directory's build script. Here's an example that should work on ```Linux``` using ```make``` as your build system. It works by running the following command on this directory using ```bash```:

```
mkdir build && cd build && cmake .. && make && ./Tests
```

> [!NOTE]
> Notice that this command automatically runs the executable file after being built.
