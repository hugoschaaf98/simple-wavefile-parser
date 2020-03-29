# Simple Wavefile Parser

Everything you need is 'wavefile.h' which contains the parser function.

## How To use the example

###### Configure :
Inside ```parse_wavefile.c``` you can uncomment the line ```#define USE_EXAMPLE_HEADER 1```.
```
$ ./parse_wavefile
channels : 1
sampleRate : 44100
byteRate : 44100
bytesPerSample : 1
bitsPerSample : 8
dataSize : 104832
```
###### Build :
simply
```$ make```
###### Run :
if you've uncommented the line ```#define USE_EXAMPLE_HEADER 1``` simply
```$ ./parse_wavefile```

Otherwise you can specify filenames
```$ ./parse_wavefile myWaveFile0.wav myWaveFile1.wav myWaveFile2.wav```
