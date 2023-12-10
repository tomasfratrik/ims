# IMS project - Cellular automaton in the field of ecology
## Authors: 
* Tomáš Frátrik (xfratr01)
* Patrik Ješko (xjesko01)
## Usage

For visualization, python script is used, `vis_data.py`.
If using `ssh`, for visualization `-Y` parameter with `ssh` is needed for window forwarding
else only `gif` of animation will be saved

compile project with `make`
`$ ./main [arguments]`
 Arguments (all arguments are mandatory, if not used defaults will be user, still recomemdet to set width and height):
    * `-h <number>` set height of the grid
    * `-w <number>` set width of the grid
    * `-r <number>` set rule (1-4) (default 1)
    * `-s <number>` set number in % of rocks occupation (recomended low number, e.g 1) (default 0) 
    * `-m <number>` set moisture, float `<1.0, 2,0>` (does nothing without `-p`)
    * `-p <number>` how many moisture roots will be planted (default 0) (must be used with `-m`)
    * `-i <number>` how many iterations (default height)

### Examples: 
```./main```
```./main -h 50 - w 50```
```./main -h 70 - w 70 -s 1 -m 2 -p 4```

## Make Targets
* `make`: compile program 
* `make run`: comiple program, run progran with set arguments, run visualization
* `make todo`: show where todos in code occur
* `make clean`: clean files

## Requirements
* `g++`
* `make`
* `python3`
    * `matplotlib`
    * `numpy`

## File structure
.
├── `Makefile`: Makefile of this project
├── `README.md`: this readme
├── `data`: data.txt from program, and gif after visualization placed here
├── `documentation`: contains, testet files, with outputs `.txt` `.gif` `.png`
├── `vis_data.py`: visualization script
└── `src`: all source files


## Brief Implementation details
Project is programed in `C++`, used OOP. Implementation of `Cellular Automata`. For visualisation used `python script`   
Project tries to simulate different types of roots, with different moisture, or with obstacles (rocks).

