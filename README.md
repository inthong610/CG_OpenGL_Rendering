# "OpenGL Rendering"
> OpenGL, 3DF Zephyr, Meshlab, C++ 이용하여 개발
>> Colorless & Color rendering.

 
## 1. OpenGL Rendering

## a. 프로젝트 설명

3DF Zephyr를 이용해서 만든 object를 meshlab을 이용하여 .off 파일로 변환하고, 이 파일들을 OpenGL을 이용하여 목표에 따라 rendering 하여 구현한다.

아래 사진은 3DF Zephyr를 이용해서 만든 object의 모습이다.


![CG HW2_1](https://user-images.githubusercontent.com/41661879/55077103-4c050200-50da-11e9-9b08-c10660f91892.png)
![CG HW2_2](https://user-images.githubusercontent.com/41661879/55077105-4c050200-50da-11e9-82fb-592c66e38aab.png)
![CG HW3_3](https://user-images.githubusercontent.com/41661879/55077106-4c050200-50da-11e9-9a88-d6cfc859b9b9.png)


## b. 프로젝트 목표

- add proper lighting (ambient, diffuse, specular)

- find proper viewpoint

- improve the speed of normal calculation

- restore the original color texture from HW2 by exporting and adding per-vertex color




## c. 시연

#### With Color :

<img width="500" alt="with_color_1" src="https://user-images.githubusercontent.com/41661879/55077516-507dea80-50db-11e9-9b7e-ebb2db2fb978.png">
<img width="500" alt="with_color_2" src="https://user-images.githubusercontent.com/41661879/55077517-507dea80-50db-11e9-9aca-d4e7687cdbad.png">
<img width="500" alt="with_color_3" src="https://user-images.githubusercontent.com/41661879/55077519-51168100-50db-11e9-8352-b9a4b4a7bfaf.png">
<img width="500" alt="with_color_4" src="https://user-images.githubusercontent.com/41661879/55077521-51168100-50db-11e9-8368-4b899e21e286.png">

#### Without Color :


<img width="500" alt="without_color_1" src="https://user-images.githubusercontent.com/41661879/55077522-51168100-50db-11e9-976e-506ede5402d3.png">
<img width="500" alt="without_color_2" src="https://user-images.githubusercontent.com/41661879/55077524-51af1780-50db-11e9-90fa-eb1f0175a788.png">
<img width="500" alt="without_color_3" src="https://user-images.githubusercontent.com/41661879/55077525-51af1780-50db-11e9-8bfa-56c76b5789c4.png">
<img width="500" alt="without_color_4" src="https://user-images.githubusercontent.com/41661879/55077527-51af1780-50db-11e9-91f4-0e1b152982de.png">

## 3. 실행 파일 실행법 & 소스 코드 컴파일 하는 법

#### - 실행 파일 실행

(Mac OS 기준)

1) 터미널을 켠다.
2) 해당 폴더로 이동한다.

``` cd /Users/folder ```

3-1) (without color) 
	typing 
	
	./CG_HW5
	
	Enter the file name :  generated.off
3-2) (with color)
	typing
	
	./CG_HW5_colored 
	
	Enter the file name : generatedColored.off 
	 

#### 소스 코드 컴파일 하기

( Eclipse 기준 )

1) 프로젝트를 만든다.
2) Project > Properties > C/C++ Build > Settings > MacOX X C++ Linker > Miscellaneout>Linker flags 
   add 
   -framework GLUT -framework OpenGL
3) Project > Properties > C/C++ Build > Settings > GCC C++ Compiler > Includes > Include paths (-l) 
   add 
   "/opt/X11/include "
4) BUILD PROJECT -> RUN as LOCAL C/C++ APPLICATION



## 4. 개발자 정보

홍정수
  
## 5. 최종 업데이트 날짜

2018.12.03 (MON)
