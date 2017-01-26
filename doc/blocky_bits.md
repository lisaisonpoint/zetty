### Before the block is written => Methods are gathered
```
  => 31 Bit ValueCount
```
```
  => 1 Bit  1: Every number is positive/negative
            0: Mixed (positive + negative)
```
```
  => 1 Bit ONLY if the block has the same sign => signs for every number are defined at the beginning
            0: Every number is positive
            1: Every number is negative
```
```
  => 4 Bit the count of Bits of the biggest exponent is written (can have the maximum size of 2⁴ = 16 = int16)
```
```
  => 6 Bit the count of Bits for the biggest value is written (can have the maximum size of 2⁶ = 64 = int64)
```
### Block Header is being written

#### => 1 Bit -> if the follwing sequence of bits is a block (1) or not (0)
##### 1:
```
     => 1 Bit -> has exponent or not
                  1: => 1 Bit -> is the exponent negativ 1 yes, 0 no
                     => the max amount of bits needed (in metatdat) for exponents -> exponent is written 
                  0: => no exponent, nothing is written
```
```
        => 1 Bit -> is there a pattern or not? 
                  1: 2 Bit -> Pattern (enum) is written 
                  0: no pattern, nothing is written
``` 
```
        => 8 Bits -> lenght of the blocks is wirtten 
```
```
   => 1 Bit -> should the amount of needed bits for the biggest value be overridden
                  1: the max amount of bits needed to represent the max amount of bits needed to represent the max value (from metatdata) -> new max amount of bits of the max value is written (although in the program just the max amount of bits of the max value from the metadata is written)
                  0: no it should not be overridden
```                  
#### Block is written
##### if all numbers have the same sign the next bit is skipped 
```      
        => 1 Bit -> is the sign of all values in the block the same ?
                  1: yes, the sign (1: negative, 0: positive) is written
                  0: nothing is written
```                  
###### now every value is checked, the following operations are executed for every value in the block 
###### if every value in the block have different signs a bit is used otherwise no bit is used 
```        
        => 1 Bit -> decides if positive (0) or negative (1)
```        
```
        if the exponent of ten of the value is bigger then the general exponant of ten of the block
        *then* the additional exponents have to be coded into the number
        => max amount of bits of the max value -> the differenc between both exponents is being multiplied as n in (10 to the power of n) with the number of the value
        *else* just the number of value is written
        => max amount of bits of the max value -> number of values is wirtten
```  
### This operation is executed until the end of the blocks 

#### The next case happens if no block is following 
#### => 1 Bit -> if the follwing sequence of bits is a block or not 
##### 0:
```     
     if all values have different signs the sign is written in front of the values 
```
```
        => 1 Bit -> negative (1) or positive (0)?
```
```
        => the max amount of bits needed for the max value => write the number of value
```        
###### If an exponent exists, it will be serialized through the upcoming operationn
```        
          => 1 Bit -> positive (0) or negative (1)
          => max amount of bits for maxValue -> Value is written
```          

# This algorithm is called for every set of numbers in brackets (in OpenFOAM files)
