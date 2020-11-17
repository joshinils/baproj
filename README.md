# baproj

## to download (clone with `git`):
```bash
git clone --recurse-submodules -j8 https://github.com/joshinils/baproj
cd baproj
```

## to make (with cmake >=3.10):
``` bash
mkdir build
cd build
cmake ..
make -j "$(nproc)"
cd ..
```
(cmake needs a C++ compiler)

## to run; the executable is now located in the `build` directory, named `baproject`:
```bash
build/baproject
```

## Additionally a folder with GTFS data is needed:

for example this one:
https://www.vbb.de/unsere-themen/vbbdigital/api-entwicklerinfos/datensaetze

this then has to be extracted into a folder named (explicitly, for now) `BVG_VBB_bereichsscharf`.

i.e. the folder structure is:
```
baproj
├── [various source files, including main.cpp]
├── build
│   ├── baproject [the executable]
│   ├── [CMake files]
│   └── Makefile
├── BVG_VBB_bereichsscharf
│   ├── agency.txt
│   ├── calendar_dates.txt
│   ├── calendar.txt
│   ├── frequencies.txt
│   ├── pathways.txt
│   ├── routes.txt
│   ├── shapes.txt
│   ├── stops.txt
│   ├── stop_times.txt
│   ├── transfers.txt
│   └── trips.txt
│     or more, or less, this is an example
│
├── graph
│   ├── [submodule files]
├── idea
│   ├── skizze_1.jpg
│   └── skizze_2.jpg
├── README.md
├── .git
├── .gitignore
└── .gitmodules
```

## optionally install missing dependencies
install opengl:
```
sudo apt-get install freeglut3 freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev -y
```

`png.h` missing or another library:
```
sudo apt install libpng-dev libxinerama-dev libxrandr-dev libxi-dev libxcursor-dev libxxf86vm-dev -y
```
