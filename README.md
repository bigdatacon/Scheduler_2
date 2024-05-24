# Блоки с whl:

A1) Запуск церез whl файл локально(в корне):  
pip install wheel
  
python3 setup.py bdist_wheel  
pip install dist/my_module-1.0-cp310-cp310-linux_x86_64.whl    """ тут название файла из папки dist"""  
python test_2.py

A2) Запуск церез whl файл на другом компьютере(в корне):
- скопировать whl файл на другую машину  
- pip install /path/to/my_module-1.0-cp310-cp310-linux_x86_64.whl  
- python test_2.py  

# Блоки без whl:
-----------------------------------------  
-----------------------------------------  
-----------------------------------------   




0. Запуск pybind без CMAKE без task_json:  
в корне проекта ::   
   chmod +x build.sh  
   ./build.sh  
Далее запустить файл test_2.py


01. Запуск под mac:  
   source venv/bin/activate  
chmod +x build_mac.sh    
./build_mac.sh     

Внимание ниже  команды для терминала - в vscode можно просто запустить через RUN!  
1. Запуск без CMAKE через task_json на убунту - в корне проекта:   
а) компиляция задачи по сборке main.cpp:  
  /usr/bin/g++ -std=c++17 -O3 main.cpp -o main -Ijson/include  
b) компиляция задачи по сборке module.cpp:      
   /usr/bin/g++ -std=c++17 -shared -fPIC -O3 my_module/module.cpp my_module/InputData.cpp -o my_module.so -Iextern/pybind11/include -Ijson/include $(python3-config --includes) $(python3-config --ldflags)  

2. Запуск без CMAKE через task_json на MACOS- в корне проекта:  
а) компиляция задачи по сборке main.cpp:  
   /usr/bin/g++ -std=c++17 -O3 main.cpp -o main -Ijson/include  

b) компиляция задачи по сборке module.cpp:   
/usr/bin/clang++ -std=c++17 -shared -fPIC -O3 my_module/module.cpp my_module/InputData.cpp -o my_module.so -Iextern/pybind11/include -Ijson/include $(python3-config --includes) $(python3-config --ldflags) -undefined dynamic_lookup  








I.  Как запускать без Cmake чтобы отдельно  модули с++ которые не видны python:  
g++ -o main main.cpp  
./main




II.  как запускать с Использованием Cmake чтобы python видел модули с++:  

Scheduler_1/cmake-build-debug$ cmake --build .  
[2/2] Linking CXX executable Scheduler_1


Scheduler_1/cmake-build-debug$ ./Scheduler_1  
434235 7 9  "это результат"  
Scheduler_1/cmake-build-debug$ python3  
import my_module  
print(my_module.add_arrays([1, 2, 3], [4, 500066, 6999]))  
[5, 500068, 7002] - "это результат"  
quit()  
  
Также в файле test_1.py после билда - должна появиться возможность (ide сама предлагает) установить созданные в файле cpp my_module или даже без предложения установки
поскольку билд прошел - то можно просто файл test_1.py запускать через run - и будет тот же результат  что и при запуске через терминал 
https://disk.yandex.ru/i/EPtzaXmLaHriNQ
