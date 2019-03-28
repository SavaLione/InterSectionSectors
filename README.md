```
  _____       _            _____           _   _              _____           _                 
 |_   _|     | |          / ____|         | | (_)            / ____|         | |                
   | |  _ __ | |_ ___ _ _| (___   ___  ___| |_ _  ___  _ __ | (___   ___  ___| |_ ___  _ __ ___ 
   | | | '_ \| __/ _ \ '__\___ \ / _ \/ __| __| |/ _ \| '_ \ \___ \ / _ \/ __| __/ _ \| '__/ __|
  _| |_| | | | ||  __/ |  ____) |  __/ (__| |_| | (_) | | | |____) |  __/ (__| || (_) | |  \__ \
 |_____|_| |_|\__\___|_| |_____/ \___|\___|\__|_|\___/|_| |_|_____/ \___|\___|\__\___/|_|  |___/
                                                                                                
                                                                                                
```


|Файлы         |Описание                   |
|--------------|---------------------------|
|README.md     |Компиляция                 |
|TESTS.md      |Тесты                      |
|NEWTESTS.md   |Новые тесты                |
|CMaleLists.txt|CMake конфигурационный файл|

|Папки                  |Описание                                    |
|-----------------------|--------------------------------------------|
|res                    |Ресурсы                                     |
|src                    |Исходные файлы                              |
|src\optimized          |Оптимизированная версия программы           |
|src\original           |Оригинальная версия программы               |
|src\originaltimetest   |Оригинальная версия программы с таймером    |
|src\optimizedwithoutout|Оптимизированная версия программы без вывода|


Из-за того, что многопоточный вывод в консоль не приносит большой производительности(сонхронизация и тд.) было решено создать отдельный проект без вывода в консоль(optimizedwithoutout).

## Compile

For Linux:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

For Windows:

    > mkdir build
    > cd build
    > cmake ..\ -G "MinGW Makefiles"
    > mingw32-make


###### 28.03.2019 - 50/50/60