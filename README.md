##COSC 1254: Programming Using C++ Assignment 1
Author: Kirolos Kaldas (s3545643) & Josh Caratelli (s3492633)

##Description:
The following code compiles without warnings on the Titan RMIT server. 
It generates mazes using the Aldous Broder algorithim and can save to SVG and Binary.
It can also read binary mazes (rejecting invalid mazes)
It will also reject invalid command line arguments using our own 'ArgsParser' cmd parser class.

##Extra Features:
()Bonus Marks - We attempted to get the bonus marks by using C++14 features 
	such as using the auto keyword and lambda function expressions.

()Checks disk space on linux before saving as pre Paul's request.
	This uses a ifndef _WIN32 to ensure this only works on linux.

()ArgsParser class, to nicely assist with processing command line arguments.

##Development Process
We used a combination of git and Trello for version control and task management respectively.
Both team members had 50% contribution each.
We reguarly tested on the server, but for speed 
	and ease of development used Visual Studio Community 2015 Update 3 as our IDE of choice.

##Compiling and Running:
	1. run "source /opt/rh/devtoolset-4/enable"
	2. use make file by running "make clean" and then "make"
	3. Use one of the following command line arguments:
	
	./mazer --lb filename.maze --sv filename.svg # load binary file and save svg file
	./mazer --g seed --sb filename.maze # generate with seed value, save binary file
	./mazer --g seed --sv filename.svg # generate with seed value, save svg file
	./mazer --g seed --sb filename.maze --sv filename.svg # gen with seed, save binary, save svg
	./mazer --g seed width height ... #save afterwards
		




