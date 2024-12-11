#!/bin/bash

# Asegurarse de que el script tenga permisos de ejecución
chmod +x "$0"

green=`tput setaf 2`
bold=`tput bold`
reset=`tput sgr0`

echo "${green}${bold}\n********************************************************************************${reset}"
echo "${green}${bold}*****************************INSTALADOR*****************************************${reset}"
echo "${green}${bold}********************************************************************************${reset}"

echo "${green}\n~INSTALACIÓN DE DEPENDENCIAS C++~\n${reset}"

echo "${green}Instalando 'clang'...${reset}"
sudo apt-get install clang -y 

echo "${green}Instalando 'make'...${reset}"
sudo apt-get install make -y 

echo "${green}Instalando 'cmake'...${reset}"
sudo apt-get install cmake -y

echo "${green}Instalando 'g++'...${reset}"
sudo apt-get install g++ -y

echo "${green}\n~INSTALACIÓN DE DEPENDENCIAS: SDL2~\n${reset}"

echo "${green}Instalando 'libsdl2-dev'...${reset}"
sudo apt-get install libsdl2-dev -y

echo "${green}Instalando 'libsdl2-image-dev'...${reset}"
sudo apt-get install libsdl2-image-dev -y

echo "${green}Instalando 'libsdl2-gfx-dev'...${reset}"
sudo apt-get install libsdl2-gfx-dev -y

echo "${green}Instalando 'libsdl2-mixer-dev'...${reset}"
sudo apt-get install libsdl2-mixer-dev -y

echo "${green}Instalando 'libsdl2-ttf-dev'...${reset}"
sudo apt-get install libsdl2-ttf-dev -y


echo "${green}\n~BUILD DEL JUEGO~\n${reset}"

echo "${green}Creando directorio 'build'...${reset}"
mkdir build

echo "${green}Compilando...${reset}"
cd build
cmake ..
make

echo "${green}${bold}\n********************************************************************************${reset}"
echo "${green}${bold}*****************************FIN DE INSTALACIÓN*********************************${reset}"
echo "${green}${bold}********************************************************************************${reset}"
