# Image Library (ILib)

This is a wrapper around stb_image and stb_image_write, it provides a single class, Image, which can be used as an object to store an image but also has static functions to simply get the bytes from an image file

It could probably do with more work but it should work pretty well as it is

## Compiling

### Shared Library

Simply run cmake and make (or ninja or whatever you want to use)

First make a build directory in the project root directory and enter that, then:

```bash
cmake ..
make
```

### Static Library

Simply run cmake (but setting the option ILIB_STATIC to ON) and make (or ninja or whatever you want to use)

First make a build directory in the project root directory and enter that, then:

```bash
cmake -DILIB_STATIC=ON ..
make
```
