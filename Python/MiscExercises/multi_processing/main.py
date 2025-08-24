import multiprocessing
import time
import random

def calculate_pi_monte_carlo(iterations: int) -> float:
    pos_x = [random.random() for _ in range(iterations)]
    pos_y = [random.random() for _ in range(iterations)]
    radius_square = [x*x + y*y for x,y in zip(pos_x, pos_y)]
    circle_range_percentage = len([r <= 1 for r in radius_square]) / len(radius_square)
    return 4 * circle_range_percentage

def run_pool(process_cnt: int, iterations: int):
    with multiprocessing.Pool(process_cnt) as pool:
        # Split iterations to multiple pieces, each for one process.
        process_iterations = [iterations // process_cnt] * process_cnt
        result = pool.map(calculate_pi_monte_carlo, process_iterations)
    print(sum(result)/process_cnt, end=", ")

if __name__ == "__main__":
    iterations = 100_000_000
    start = time.time()
    run_pool(1, iterations)
    print(f"\n{time.time() - start} seconds")

    start = time.time()
    run_pool(10, iterations)
    print(f"\n{time.time() - start} seconds")
