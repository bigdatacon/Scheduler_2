from setuptools import setup, Extension
import pybind11

setup(
    name='my_module',
    version='1.0',
    ext_modules=[Extension('my_module', ['my_module/module.cpp', 'my_module/InputData.cpp'], include_dirs=[pybind11.get_include()])],
    setup_requires=['pybind11>=2.5.0'],
    install_requires=[
        'pybind11>=2.5.0'
    ],
)
