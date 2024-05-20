import random
import multiprocessing as mp;
from multiprocessing import Pool;

def monte_carlo_pi(x_points):
  points_circle = 0;
  for i in range(x_points):
    x = random.uniform(0, 1);
    y = random.uniform(0, 1);
    z = x * x + y * y;
    if z < 1:
      points_circle += 1;
  return points_circle;

if __name__ == "__main__":
  points = 100000;
  np = mp.cpu_count();

  pool = Pool(processes = np);

  parameters = [points] * np;

  results = pool.map(monte_carlo_pi, parameters);
  print("Points in Circle per Process: ", results);

  total = points * np;
  total__circle = sum(results);

  pi = 4 * total__circle / total;

  print("PI: " + str(pi));
