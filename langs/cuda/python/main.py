# pip install cuda-python
# pip install numba

from numba import cuda
import numpy as np

# Define a custom CUDA kernel in Python
@cuda.jit
def vector_add(a, b, c):
    # Calculate the unique thread position
    pos = cuda.grid(1)
    if pos < a.size:
        c[pos] = a[pos] + b[pos]

# Initialize data on the host (CPU)
N = 100000
A = np.ones(N, dtype=np.float32)
B = np.ones(N, dtype=np.float32)
C = np.zeros(N, dtype=np.float32)

# Copy data to the device (GPU)
d_A = cuda.to_device(A)
d_B = cuda.to_device(B)
d_C = cuda.to_device(C)

# Configure threads and blocks
threads_per_block = 256
blocks_per_grid = (N + (threads_per_block - 1)) // threads_per_block

# Launch the kernel
vector_add[blocks_per_grid, threads_per_block](d_A, d_B, d_C)

# Copy the result back to the host
result = d_C.copy_to_host()
print(result[:5])  # Outputs: [2. 2. 2. 2. 2.]
