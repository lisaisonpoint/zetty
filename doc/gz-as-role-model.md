### research notes (2016-12-05)

Currently, the compression library [zlib](http://www.zlib.net/) (header file zlib.h) is responsible for the serialization of compressed data in OpenFOAM.

### the role model

the role model for our implementation is as follows:

```c++
// returns a file as gzFile
gzopen(filename, filemode);

// closes the gzFile specified; returns a value from a FileCloseOperationResultEnum as an int
gzclose(file);

// reads from gzFile and writes into buffer; returns a buffer length
gzread(file, buffer, buffLength);

// inverse of gzread; returns a buffer length
gzwrite(file, buffer, buffLength);
```
