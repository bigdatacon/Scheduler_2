from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

class BuildExt(build_ext):
    def build_extensions(self):
        compiler = self.compiler.compiler_type
        if compiler == 'unix':
            for ext in self.extensions:
                ext.extra_compile_args = ['-std=c++17']
        build_ext.build_extensions(self)

ext_modules = [
    Extension(
        'my_module',
        sources=['my_module/module.cpp', 'my_module/InputData.cpp'],
        include_dirs=['extern/pybind11/include', 'json/include'],
        language='c++'
    ),
]

setup(
    name='my_module',
    version='1.0',
    ext_modules=ext_modules,
    cmdclass={'build_ext': BuildExt},
)
