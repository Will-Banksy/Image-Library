# Image Library (ILib)

This is a wrapper around [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) and [stb_image_write](https://github.com/nothings/stb/blob/master/stb_image_write.h), it provides a single class, Image, which can be used as an object to store an image but also has static functions to simply get the bytes from an image file

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
