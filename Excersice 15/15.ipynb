print('NOTE: Intentionally crashing session to use the newly installed library.\n')

!pip uninstall -y pyarrow
!pip install ray[debug]==2.21.0
!pip install bs4

# HACK FOR AN RESTART
import os
os._exit(0)



import ray;

# INITIALIZE RAY
ray.init();

# DEFINE THE REMOTE FUNCTION
@ray.remote
def welcome():
    return "Hola, Mundo!";

# CALL TH REMOT FUNCTION AND GET RESULT
future = welcome.remote();
result = ray.get(future)

print(result);
