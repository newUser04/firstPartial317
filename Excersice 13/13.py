import multiprocessing as mp;
from multiprocessing import Pool;
import math

def binet(n):
  sqrt_5 = math.sqrt(5)
  phi = (sqrt_5 + 1) / 2
  return int(phi ** n / sqrt_5 + 0.5)

def fibo(init, end):
  v = [];
  for i in range(init, end):
    v.append(binet(i));
  return v;

if __name__ == '__main__':
  limit = 997;
  processors = mp.cpu_count();
  barrier = int(limit / processors);
  rest = limit % processors;

  parameters = [];

  for i in range(processors):
    if i == processors - 1:
      parameters.append((barrier * i, barrier * (i + 1) + rest));
    else:
      parameters.append((barrier * i, barrier * (i + 1)));

  print("Dinamic Division for " + str(limit) + " terms:");
  print("\t", parameters);

  pool = Pool(processes = processors);

  result = pool.starmap(fibo, parameters);

  for i in range(len(result)):
    print("Vector in Process:", i)
    print("\t", result[i]);
