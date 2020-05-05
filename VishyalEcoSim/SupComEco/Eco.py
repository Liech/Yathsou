import matplotlib.pyplot as plt
from .Unit import Unit

class Eco:
  def __init__(self):
    self._mass = 650
    self._energy = 4000
    self._time = 0

    self._massHistory = []
    self._energyHistory = []

    self._units = [Unit("UEF ACU")]
    self._units[0]._progress = self._units[0]._buildTime
  
  def tick(self):
    #print("Tick:",self._time)

    totalE = 0
    totalM = 0
    for unit in self._units:
      m,e = unit.getConsumption(1.0,1.0)
      totalM += m
      totalE += e
    mLimit = min([1.0,self._mass / float(totalM)]) if totalM >0 else 1.0
    eLimit = min([1.0,self._energy / float(totalE)]) if totalE >0 else 1.0

    #prodLimiter = min([eLimit,mLimit])
    #print("Mass:", self._mass, "Req Mass:",totalM,"Energy", self._energy,"Req Engergy:",totalE)

    for unit in self._units:
      m,e = unit.tick(mLimit,eLimit, self)
      self._mass -= m
      self._energy -= e

    if(self._energy>4000):
      self._energy = 4000

    self._massHistory.append(self._mass)
    self._energyHistory.append(self._energy)
    self._time+=1

  def plot(self):
    plt.plot(self._massHistory,'y')
    plt.plot(self._energyHistory,'g')
    plt.legend(["Mass","Energy"])
    plt.show()


