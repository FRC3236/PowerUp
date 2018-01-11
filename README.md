# TRIFORCE 3236 - FIRST PowerUp

## Code Setup Instructions

Before you do anything, you need GradleRIO. You can download it [here](https://github.com/Open-RIO/GradleRIO).

Project files are stored within the `src/cpp` folder. GradleRIO automatically makes an `src/include` folder for header files, but for our purposes we will not be putting header files in this folder.

It is recommended that you run all gradle commands in a command line that has administrator priviledges.

Make sure that you have installed the [C++ toolchain](http://first.wpi.edu/FRC/roborio/toolchains/), and [CTRE's Talon libraries](http://www.ctr-electronics.com/control-system/hro.html#product_tabs_technical_resources). If you do not have the WPILib includes, they can be found [here](https://drive.google.com/open?id=1a1DE70waDcB87WumJfISnJyxQFEDP31x). Extract them to somewhere you'll remember.

### Eclipse
1. Clone repository into desired directory.
2. Open a command prompt and navigate to this new directory. Run `gradlew.bat installToolchain`. You may need to do this as an administrator.
3. In Eclipse, import the project from the root directory (i.e, if you cloned into `FRC2018`, import the project from `FRC2018`.)
4. Follow the [WPILib Screensteps article](http://wpilib.screenstepslive.com/s/currentCS/m/cpp/l/145002-installing-eclipse-c-java) about installing WPILib into Eclipse.  
**Do not run a build by right clicking the project and clicking WPILib Deploy, like in previous years. GradleRIO is meant to move the build process away from the IDE.**

### CLion
1. Clone repository into desired directory.
2. Open a command prompt and navigate to this new directory. Run `gradlew.bat installToolchain`. You may need to do this as an administrator.
3. Run `gradlew.bat clion`
4. In CLion, import the project from the root directory (i.e, if you cloned into `FRC2018`, import the project from `FRC2018`.)
5. CLion uses a file called `CMakeLists.txt` to understand where includes and headers are. Add the following lines:
```
set(INCLUDE_DIRECTORIES
	<path/to/wpilib/includes>
	<path/to/ctre/phoenix>)
```
Replace `<path/to/wpilib/includes>` and `<path/to/ctre/phoenix>` with the correct paths. For example, my paths are `C:/Users/Eric/wpilib/cpp/current/include` for WPILib and `C:/Users/Eric/wpilib/user/cpp/include` for CTRE Phoenix.
Then, towards the bottom of `CMakeLists.txt`, add:
```
include_directories(${INCLUDE_DIRECTORIES})
```
As an example, this is what my CMakeLists.txt looks like:
![CMakeListExample](https://i.imgur.com/yb2w9dh.png)

## Building Code
Once you have written a section of code that you would like to validate, run `gradlew.bat build`. This will build the code and show you where any errors are apparent. This does **not** upload the code to the robot.

## Deploying Code
Once you have validated the code to be functional, run `gradlew.bat deploy`. This will deploy your code to the robot.