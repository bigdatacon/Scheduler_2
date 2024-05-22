from setuptools import setup, Extension
import os

# Define the extension module
module = Extension(
    'my_module',
    sources=['my_module/module.cpp', 'my_module/InputData.cpp'],
    include_dirs=['./extern/pybind11/include', './json/include'],
    extra_compile_args=['-std=c++17'],
)

# Run the setup
setup(
    name='my_module',
    version='1.0',
    description='My custom module',
    ext_modules=[module],
)
