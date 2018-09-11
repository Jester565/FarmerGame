# FarmerGame
FarmerGame is a small project written in three days and was built to show the versatility of AllegroExt and Lighting4. It features a short campaign against evil potatos (don't ask) and was an implementation of a [team project outline](https://github.com/Jester565/FarmerGame-JavaDocTest).
![Allegro Configuration](/rmde/farmergame.gif)

## Installation
Requirements: Boost (1.68.0), Allegro (5.2.4), and Box2D (2.3.1)

#### Requirement Installation
1. Installing Boost
    i. Download at https://www.boost.org/
    ii. In boost root directory, run ```./bootstrap```
    iii. For default configuration compatibility run: ```./b2 --stagedir=./stage/VS2017/x64 address-model=64 --toolset=msvc-14.1 --with-thread variant=release link=static threading=multi runtime-link=static```
    iv. Add the boost root directory to CMAKE_INCLUDE_PATH and the directory of your boost library files (should be in stage/lib) to CMAKE_LIBRARY_PATH.
2. Installing Box2D
    i. Download from https://github.com/erincatto/Box2D
    ii. Install [Premake5](https://premake.github.io/)
    iii. Run ```premake5 vs2017 --StaticRuntime```
    iv. Run visual studio solution or make
3. Installing Allegro
    * Windows:
        i. After you generate the FarmerGame solution, goto Tools -> NuGet Packet Manager -> Manage NuGet Packages for Solution... -> Browse
        ii. Search for and install Allegro for AllegroExt, Lighting4, and FarmerGame
        iii. Goto the properties for the Allegro projects and set the dependencies like this ![Allegro Configuration](/rmde/AllegConf.png)
    * Ubuntu:
        i. Install Allegro5 Package with [this guide](https://wiki.allegro.cc/index.php?title=Install_Allegro_from_Ubuntu_PPAs)

#### Build
```
mkdir build
cd build
cmake .. -G "Visual Studio 15 2017" -A x64 -T host=x64 -Dboxlibdir="(Box2D Directory)\Build\bin\x86_64\Release\" -Dboxincludedir="(Box2D Directory)"        #For Ubuntu don't include -G option
```
Run make or build the solution  
Set FarmerGame as Startup Project after building on Visual Studio

#### Troubleshooting
* If using Visual Studio make all projects are using /MT runtime linking and Basic Runtime Checks is set to default.