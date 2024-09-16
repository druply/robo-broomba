cd core/pygen
python3 sysgen.py
python3 sysconfig.py
mv sys_tasks.cpp sys_tasks.hpp sys_config.hpp ../../gen/
cd ../..
