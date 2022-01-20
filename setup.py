from skbuild import setup

setup(
    name="mypackage",
    packages=['mypackage'],
    python_requires='>=3.6',
    version="0.0.1",
    license="MIT",
    author='Nicholas Wogan',
    author_email = 'nicholaswogan@gmail.com',
    cmake_args=['-DSKBUILD=ON']
)
