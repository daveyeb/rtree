# r🌲 CLI 
A command line tool almost like the `tree` command but spits out a file dependency tree from repositories. This tool has only support for JavaScript projects at the moment.


## Building 

### Windows & Linux  

To build and install rtree CLI, run:
```
$ make install 
```

### macOs 

Ensure you have [https://brew.sh](Homebrew) installed or use the same process as Linux. 

## Usage:
    rtree
    rtree [-f | --full]
    rtree [-b | --base]
    rtree [-d | --dependants]
## Commands:
    -f,--full           Prints the absolute paths of imports
    -d,--dependants     List dependants only 
    -b,--basename       List all files with basename
    -h,--help           Prints usage 
## Options:
    -v,--version        Shows version 


## Contribute:
Any fixes, cleanup or new features are always appreciated.


