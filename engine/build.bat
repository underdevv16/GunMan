set files=src\glad.c src\main.c src\engine_\global.c src\engine_\render\render.c src\engine_\render\render_init.c
set libs=E:\GunMan\lib\SDL2main.lib E:\GunMan\lib\SDL2.lib E:\GunMan\lib\freetype.lib

CL /Zi /I E:\GunMan\include %files% /link %libs% /OUT:GunMan.exe