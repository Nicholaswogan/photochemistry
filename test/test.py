

import numpy as np
try:
    from mypackage import MyClass
except:
    import sys
    import os
    SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
    sys.path.append(os.path.dirname(SCRIPT_DIR))
    from mypackage import MyClass

my = MyClass()

my.arr = np.random.rand(10000)

print(my.sum_arr())