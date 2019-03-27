

[How to execute the executable files]

1. first, OS is "macOS"
2. turn on the terminal
3. go to "[HW5]1415088_JungsooHong" folder. -> (ex) cd /Users/jungsoo/Desktop/\[CG\]HW5_1415088_JungsooHong

4-1 (without color) 
	1) typing -> ./CG_HW5
	2) Enter the file name :  generated.off
4-2 (with color)
	1) typing -> ./CG_HW5_colored
	2) Enter the file name : generatedColored.off


------------------------------------------------------------------------------------------
 

[How to compile]

1. use eclipse
2. make project
3. Project > Properties > C/C++ Build > Settings > MacOX X C++ Linker > Miscellaneout>Linker flags 
   add 
   -framework GLUT -framework OpenGL
4. Project > Properties > C/C++ Build > Settings > GCC C++ Compiler > Includes > Include paths (-l) 
   add 
   "/opt/X11/include "

5. BUILD PROJECT -> RUN as LOCAL C/C++ APPLICATION


------------------------------------------------------------------------------------------


[State explicitly which features are implemented]

1. add proper lighting (ambient, diffuse, specular)
2. find proper viewpoint
3. improve the speed of normal calculation 
4. restore the original color texture from HW2 by exporting and adding per-vertex color

