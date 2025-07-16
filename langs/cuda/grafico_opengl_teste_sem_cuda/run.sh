#Install OpenGL on Ubuntu
#sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
#sudo apt-get install libglfw3
#sudo apt-get install libglfw3-dev
#Compilar:
  #glfw: g++ -pthread -o main main.cpp -lglfw -lGLU -lGL -lXrandr -lX11 -lrt -ldl
  #glut: g++ main.cpp -o main -lglut -lGLU -lGL
g++ -pthread -o a data.h colors.h main.cpp -lglfw -lGLU -lGL -lXrandr -lX11 -lrt -ldl -lglut

./a

rm ./a

