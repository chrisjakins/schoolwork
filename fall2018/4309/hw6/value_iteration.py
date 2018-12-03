# Chris Jakins 1000802309

import sys
import numpy as np
from file_utility import FileUtility

if len(sys.argv) != 5:
    print("Usage: value_iteration.py <environment_file> <non_terminal_reward> <gamma> <K>")
    quit()


environment_filename = sys.argv[1]
nt_reward = float(sys.argv[2])
gamma = float(sys.argv[3])
k = int(sys.argv[4])


def value_iteration(states, reward, gamma, k):
    n = len(states) * len(states[0]) # assumes rectangular
    u = np.zeros((len(states), len(states[0])))

    for it in range(0, k):
        u_prime = np.array(u)

        for i in range(0, len(states)):
            for j in range(0, len(states[i])):
                if states[i][j] == 'X':
                    u[i][j] = 0
                elif isinstance(states[i][j], float):
                    u[i][j] = states[i][j]
                else:
                    # calc for all possible transitions
                    u[i][j] = (reward + 
                              gamma * bm(states, u_prime, i, j, len(states), len(states[i])))

    return u


# don't look at this, thanks
def bm(env, u, i, j, max_i, max_j):
    ########### up 
    # up_l
    if j == 0 or env[i][j - 1] == 'X':
        up_l = .1 * u[i][j]
    else:
        up_l = .1 * u[i][j - 1]
    
    # up_u
    if i == 0 or env[i - 1][j] == 'X':
        up_u = .8 * u[i][j]
    else:
        up_u = .8 * u[i - 1][j]
    
    # up_r
    if j == max_j - 1 or env[i][j + 1] == 'X':
        up_r = .1 * u[i][j]
    else:
        up_r = .1 * u[i][j + 1]

    max_util = up_u + up_l + up_r


    ########### left
    # left_u
    if i == 0 or env[i - 1][j] == 'X':
        left_u = .1 * u[i][j]
    else:
        left_u = .1 * u[i - 1][j]

    # left_l
    if j == 0 or env[i][j - 1] == 'X':
        left_l = .8 * u[i][j]
    else:
        left_l = .8 * u[i][j - 1]

    # left_d
    if i == max_i - 1 or env[i + 1][j] == 'X':
        left_d = .1 * u[i][j]
    else:
        left_d = .1 * u[i + 1][j]

    if left_u + left_l + left_d > max_util:
        max_util = left_u + left_l + left_d


    ############# down
    # down_l
    if j == 0 or env[i][j - 1] == 'X':
        down_l = .1 * u[i][j]
    else:
        down_l = .1 * u[i][j - 1]

    # down_d
    if i == max_i - 1 or env[i + 1][j] == 'X':
        down_d = .8 * u[i][j]
    else:
        down_d = .8 * u[i + 1][j]

    # down_r
    if j == max_j - 1 or env[i][j + 1] == 'X':
        down_r = .1 * u[i][j]
    else:
        down_r = .1 * u[i][j + 1]

    if down_l + down_d + down_r > max_util:
        max_util = down_l + down_d + down_r

    ############# right
    # right_d
    if i == max_i - 1 or env[i + 1][j] == 'X':
        right_d = .1 * u[i][j]
    else:
        right_d = .1 * u[i + 1][j]

    # right_r
    if j == max_j - 1 or env[i][j + 1] == 'X':
        right_r = .8 * u[i][j]
    else:
        right_r = .8 * u[i][j + 1]

    # right_u
    if i == 0 or env[i - 1][j] == 'X':
        right_u = .1 * u[i][j]
    else:
        right_u = .1 * u[i - 1][j]

    if right_d + right_r + right_u > max_util:
        max_util = right_d + right_r + right_u

    return max_util

######################

file_util = FileUtility()
env = file_util.getData(environment_filename)
utility_values = value_iteration(env, nt_reward, gamma, k)


for i in range(0, len(utility_values)):
    for j in range(0, len(utility_values[i])):
        if j == len(utility_values[i]) - 1:
            print("%6.3f" % utility_values[i][j], end = '\n')
        else:
            print("%6.3f," % utility_values[i][j], end = '')
