#   Chris Jakins
#   1000802309
#   HW9 4/30
import numpy as np


# probability functions
task_prob = [ {3:.7, 4:.9, 2:1},
              {1:.5, 2:1},
              {6:.6, 8:.8, 5:1},
              {4:.8, 5:.9, 3:.95, 2:1} ]


def gen_random():
    return np.random.uniform(0, 1, size = (1,4))


def days_run(prob):
    num_days = 0
    for i in range(0, prob.shape[1]):
        for days in task_prob[i]:
            if prob[0, i]  <= task_prob[i][days]:
                num_days += days
                break

    return num_days


def estDuration(runs):
    total = 0
    min_days = np.inf
    max_days = 0

    for i in range(0, runs):
        probabilities = gen_random()
        days = days_run(probabilities)

        total += days
        min_days = min(min_days, days)
        max_days = max(max_days, days)

    return min_days, max_days, total / runs


########################  main  ########################
if __name__ == "__main__" :
    runs = 1000

    minDays, maxDays, avg = estDuration(runs)

    print("min = %d, max = %d, average = %.1f" % (minDays, maxDays, avg))
