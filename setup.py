from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        "my_module",
        sources=[
            "my_module/module.cpp",
            "my_module/InputData.cpp",
        ],
        include_dirs=[
            pybind11.get_include(),
            "extern/pybind11/include",
            "json/include"
        ],
        language="c++",
        extra_compile_args=["-std=c++11"]
    ),
]

setup(
    name="my_module",
    version="1.0",
    author="Your Name",
    author_email="your.email@example.com",
    description="A sample C++ extension module",
    long_description="",
    ext_modules=ext_modules,
    install_requires=[
        "pybind11>=2.5.0"
    ],
    zip_safe=False,
)
