# A Peak production in Cedar

Everything you want to know about DFT -> https://dynamicfieldtheory.org/

Cedar is the C++ Framework implementing the concepts of DFT -> https://cedar.ini.rub.de/

Everything you need to know about ROS -> http://www.ros.org/

## Getting Started

The plugin produce a peak of activation depending on 2 inputs : the amplitude of the peak, and its position on a 1D Field.
I personnaly use this plugin to produce a peak of activation gathering an external reward and a motor position.

The code work for the 6.x version of Cedar.


### Prerequisites

You first need to install cedar by following the instructions here : https://cedar.ini.rub.de/tutorials/installing_and_running_cedar/

You can't use a precompiled version of Cedar to compile and run the plugin.

I suggest reading about how to create a plugin in Cedar first, it will greatly help to understand how it works : https://cedar.ini.rub.de/tutorials/writing_custom_code_for_cedar/

**INSTALL YARP**

This last version of the plugin requires yarp (cedar built with yarp support - you don't have to do$

https://www.yarp.it/install.html

If you don't need it, remove the find_package(YARP REQUIRED) in the cedarProject.cmake

### Installing

First clone the repository :

`git clone https://github.com/rouzinho/RewardPeak.git`

In the project.conf, change the CEDAR_HOME directory to your own :

`set(CEDAR_HOME "your_own_cedar_repository")`

Then create a build repository and prepare the environment for the compilation :

`mkdir build`

`cd build`

`cmake ..`

Finally start the compilation :

`make`

You should see the plugin under the name libRewardPeak.so in the build/ repository


## Run the plugin

Execute cedar and load it into cedar 

*Tools -> Manage plugins*

In the plugin Manager window, click on *add* and choose the plugin libRewardPeak.so. This one should appear in the window.

You can close the window. The plugin is loaded inside cedar.

You can now go back to the cedar main interface and click on the Utilities tab.

Drag the RewardPeak widget into the architecture panel. When your architecture is ready, you can start the simulation.



## Authors

Quentin Houbre - Tampere University

## License

This project is licensed under the BSD licence

