set render=src\engine_\render\render.c src\engine_\render\render_init.c src\engine_\render\render_util.c
set io=src\engine_\io\io.c
set files=src\glad.c src\main.c src\engine_\global.c %render% %io%
set libs=E:\GunMan\lib\SDL2main.lib E:\GunMan\lib\SDL2.lib E:\GunMan\lib\freetype.lib

CL /Zi /I E:\GunMan\include %files% /link %libs% /OUT:GunMan.exe