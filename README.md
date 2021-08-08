# rtree CLI 

## For any pull request or contributions? Contact 

1. [David Yeboah](mailto:daveyeb@gmail.com)

## Building 

### Linux 

To build and install rtree CLI, you can run: 

```
$ make install 
```

If you want to put the result in a different location than `/usr/bin`

```
$ PREFIX=/opt/rtree make install 
```

### macOs 

Ensure you have [https://brew.sh](Homebrew) installed or use the same process as Linux. 

## Usage 
    rtree (setup|init|auth)...
    rtree -f | --full
    rtree -d | --directories 
    rtree -L level | --level level
    rtree -o filename | --output filename 
## Commands:
    -f,--full           Prints the full path prefix for each import/module 
    -d,--directories    List directories only 
    -l,--level          Max display depth of the directory tree 
    -o,--output         Send output to filename 
## Options:
    -V,--version        Shows version. 

--- 

Tell me how you feel about this. 
    - twitter.com/daveyeb


