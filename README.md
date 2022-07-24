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

###### C++14

###### cmake >= 3.20
- Homebrew: cmake
- Debian/Ubuntu: cmake
- Fedora/CentOS: cmake

###### libosmium >= 2.18.0
- Homebrew: libosmium
- Debian/Ubuntu: libosmium2-dev
- Fedora/CentOS: libosmium-devel

###### protozero >= 1.6.3
- MacPorts: protozero
- Debian/Ubuntu: libprotozero-dev
- Fedora/CentOS: protozero-devel

###### expat
- Homebrew: expat
- Debian/Ubuntu: libexpat1-dev
- Fedora/CentOS: expat-devel


#### Build:

``` bash
$ ./build.sh             # Build debug
$ ./build.sh test        # Build debug and run tests
$ ./build.sh release     # Build release
$ ./build.sh install     # Build release and install
```
