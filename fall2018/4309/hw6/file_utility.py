import os
import numpy as np

class FileUtility:


    def find(self, name, path):
        for root, dirs, files in os.walk(path, topdown = False):
            if name in files:
                return os.path.join(root, name)


    def file_search(self, name):
        new_file = self.find(name, './')

        if new_file == None:
            new_file = self.find(name, '../')
        if new_file == None:
            new_file = self.find(name, '/')
        if new_file == None:
            print('%s not found. Quitting...' % (name))
            quit()
        
        return new_file


    def getData(self, filename):
        if filename == None:
            return None

        infile = self.file_search(filename)

        # parsing the file
        env = []
        for line in open(infile):
            line.strip()
            row = line.split(',')
            row[-1] = row[-1].strip()
            env.append(row)

        env_num = []
        for row in env:
            line = []
            for el in row:
                if el == '.' or el == 'X':
                    line.append(el)
                else:
                    line.append(float(el))
            env_num.append(line)

        return env_num
