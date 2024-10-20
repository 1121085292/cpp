import matplotlib.pyplot as plt

def visualize(): 
  dist = [3.0, 2.5, 2.0, 1.8, 1.5, 1.0, 0.9, 1.0,
          1.5, 2.0, 2.5, 3.0, 2.2, 2.0, 1.5, 1.2]
  plt.plot(dist)

  plt.show()

if __name__ == "__main__":
  visualize()