from setuptools import setup, Extension
import pybind11

setup(
    name='my_module',
    version='1.0',
    author='Your Name',
    author_email='your_email@example.com',
    description='A description of your project',
    ext_modules=[
        Extension(
            'my_module',
            sources=['my_module/module.cpp', 'my_module/InputData.cpp'],
            include_dirs=[pybind11.get_include(), 'extern/pybind11/include', 'json/include'],
            language='c++'
        )
    ],
    zip_safe=False,
)
