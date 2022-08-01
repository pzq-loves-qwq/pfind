# pfind
Program for searching for low-width low-period spaceships in range-1 moore neighborhood cellular automata. 

# Usage

**Important note: this is only a preliminary implementation, please do not use this for serious searches. **

The period, displacement, and search width are specified in `blah.hpp`. To specify the symmetry, modify `mirror(u64)` in `blah.hpp`. To change the rule, modify `bool table[512]` in `blah.hpp`. 

In particular, the rule is stored as a 512-element lookup table, where the element with index 0babcdefghi encodes the center cell of the next generation of this configuration:

```
a b c
d e f
g h i
```

A [Golly](https://golly.sourceforge.net/) Python script `get_table.py` is included for generating the table. 

Note that when searching with symmetry, only half of the spaceship is outputted. 

After everything is ready, compile with

```
clang++ search.cpp -o search -O3 -mavx2
```

(clang++ is recommended here because its better auto-vectorization. When running a search for the [turtle](https://www.conwaylife.com/wiki/Turtle), the clang++ version was faster than the g++ version by ~0.3s). 
