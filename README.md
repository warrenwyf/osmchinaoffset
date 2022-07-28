# osmchinaoffset
----------------
Offset the OSM data coordinates within China to GCJ-02

将中国范围内的 OSM 数据坐标偏移为 GCJ-02「火星坐标系」


## Usage

``` bash
$ osmchinaoffset china.osm.pbf china-offset.osm.pbf
```


## Develop

#### Prerequisites:

``` macOS
$ brew install cmake libosmium googletest
```

``` Ubuntu
$ sudo apt install cmake libosmium2-dev libgtest-dev
```

#### Build:

``` bash
$ ./build.sh             # Build debug
$ ./build.sh test        # Build debug and run tests
$ ./build.sh release     # Build release
$ ./build.sh install     # Build release and install
```
