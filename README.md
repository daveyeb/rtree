# r🌲 CLI 
A Command line tool almost like the `tree` command that spits out a file dependency tree of a repository. This tool has only support for JavaScript projects at the moment.


## Building 

### Windows 

To build and install rtree CLI, run:

```
$ make 
```

### Linux 

```
$ make install 
```

### macOs 

Ensure you have [https://brew.sh](Homebrew) installed or use the same process as Linux. 

## Usage 
    rtree
    rtree [-f | --full]
    rtree [-b | --base]
    rtree [-d | --dependants]
## Commands:
    -f,--full           Prints the absolute paths of imports
    -d,--dependants     List dependants only 
    -b,--basename       List all files with basename
## Options:
    -v,--version        Shows version. 

--- 

Tell me how you feel about this. 
    - twitter.com/daveyeb


