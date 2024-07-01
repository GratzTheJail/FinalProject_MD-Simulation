#!/usr/bin/env python3
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
from matplotlib.pyplot import cm
import numpy as np
import csv
import os
import sys,getopt

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

def plot(time,particleData,colors,domainOrigin,domainDim,timeIndex):
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
    ax.set_xlim([domainOrigin[0]-0.5,domainOrigin[0]+domainDim[0]+0.5])
    ax.set_ylim([domainOrigin[1]-0.5,domainOrigin[1]+domainDim[1]+0.5])
    ax.set_aspect('equal', adjustable='box')
    ax.add_patch(Rectangle(domainOrigin, domainDim[0], domainDim[1],edgecolor='k',fill=False))
    plt.title("Time: "+str(time))
    plt.savefig(f'PNG/plotcircles-{timeIndex:05}.png')
    plt.close('all')


# =============================================================================
#                       Main Body of Script
# =============================================================================

def main(argv):
    domainOrigin = [0,0]
    domainDimension = [1,1]
    try:
        opts, args = getopt.getopt(argv,"o:d:",["origin=","dimension="])
        if not opts:
            print('plotResults -o <origin of domain> -d <dimensions of domain>')
            exit(0)
    except getopt.GetoptError:
        print('plotResults -o <origin of domain> -d <dimensions of domain>')
        exit(0)
    for opt,arg in opts:
        if opt == '-o' or opt == '--origin':
            str = arg.split(',')
            domainOrigin[0] = float(str[0])
            domainOrigin[1] = float(str[1])
        elif opt == '-d' or opt == '--dimension':
            str = arg.split(',')
            domainDimension[0] = float(str[0])
            domainDimension[1] = float(str[1])

    data = readData('../data/particlePos.dat')
    colors = cm.rainbow(np.linspace(0, 1,10))

    # Reduce data to max 200 time steps
    if len(data) > 200:
        data = data[0::int(len(data)/200.0)]

    timeIndex=0

    for d in data:
        plot(d[0],d[1],colors,domainOrigin,domainDimension,timeIndex)
        timeIndex = timeIndex +1


if __name__ == "__main__":
   main(sys.argv[1:])


