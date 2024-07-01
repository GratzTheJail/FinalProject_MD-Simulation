import matplotlib.pyplot as plt
from matplotlib.pyplot import cm
import numpy as np
import csv
import os


# =============================================================================
#                       Function Definitions
# =============================================================================

# Function to read the data file
# Returns a list of python tuples, with the first entry
# as the time and the second as a 2D numpy array of particles
def readData(filePath,nProperties=4):
    # Create empty list
    data = []
    with open(filePath) as tsv:
        header_line = tsv.readline()
        for line in csv.reader(tsv, delimiter="\t"):
            # Parse line into time and position
            time = float(line[0])
            
            # Create tuple
            dataSet = (time,np.zeros((int((len(line)-1)/nProperties),nProperties)))
            
            # Read in the particles
            for i in range(int((len(line)-1)/nProperties)):
                for j in range(nProperties):
                    dataSet[1][i][j] = float(line[1+j+i*nProperties])
            
            # Add dataSet to list
            data.append(dataSet)
    return data

def plot(time,particleData,colors):
    particles = []
    for i in range(particleData.shape[0]):
        particles.append(
            plt.Circle((particleData[i,0],particleData[i][1]),
            particleData[i][2],
            color=colors[int(particleData[i][3])]))
    
    if not os.path.isdir('PNG'):
        os.mkdir('PNG')
    
    plt.figure()
    ax = plt.gca()
    for p in particles:
        ax.add_patch(p)
    ax.set_xlim([-1,1])
    ax.set_ylim([-1,1])
    ax.set_aspect('equal', adjustable='box')
    ftime = int(float(time)*10000)
    plt.savefig(f'PNG/plotcircles-{ftime:05}.png')
    plt.close('all')


# =============================================================================
#                       Main Body of Script
# =============================================================================


data = readData('../data/particlePos.dat')
colors = cm.rainbow(np.linspace(0, 1,10))

for d in data:
    plot(d[0],d[1],colors)


