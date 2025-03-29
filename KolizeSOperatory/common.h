#pragma once

#include<iostream>
#include <cmath>
#include <string>       
#include <windows.h>
#include <winuser.h>
#include <conio.h>  
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <fcntl.h>
#include <locale.h>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <random>
#include <ctime>
#include <map>
#include <chrono>

#define DEBUG()	if(GetAsyncKeyState(VK_ESCAPE)) {__debugbreak();}
#define PI		3.14159265359