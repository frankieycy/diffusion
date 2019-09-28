import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc

rc('text', usetex=True)

out = 'fig/' # output directory

traj = np.loadtxt('traj.txt', delimiter=' ') # tracer track
data = np.loadtxt('data.txt', delimiter=' ') # statistics

N = 2000 # num of particles
t = traj[:,0] # time
x = traj[:,1] # x-coord
y = traj[:,2] # y-coord
mu = data[:,1] # mean displacement
var = data[:,3] # squared displacement

m,b = np.polyfit(t,var,deg=1) # line fit: slope m = variance rate
bound = np.sqrt(m*t/N) # 68% liklihood bound

# --------- tracer --------- #

fig = plt.figure()
plt.plot(x,y,color='black')
plt.title(r'Sample path of a tracer')
plt.xlabel(r'$\Delta x$')
plt.ylabel(r'$\Delta y$')
fig.savefig(out+'traj.png',dpi=200)
plt.close()

# --------- statistics --------- #

fig = plt.figure()
plt.plot(t,mu,color='black')
plt.plot(t,bound,color='grey',linestyle='dashed',label='$68\%$ liklihood')
plt.plot(t,-bound,color='grey',linestyle='dashed')
plt.title(r'$\langle x \rangle$-$t$ plot')
plt.xlabel(r'time $t$')
plt.ylabel(r'mean displacement $\langle x \rangle$')
plt.legend()
fig.savefig(out+'mu.png',dpi=200)
plt.close()

fig = plt.figure()
plt.plot(t,var,color='black')
plt.title(r'$\langle x^2 \rangle$-$t$ plot')
plt.xlabel(r'time $t$')
plt.ylabel(r'squared displacement $\langle x^2 \rangle$');
fig.savefig(out+'var.png',dpi=200)
plt.close()

