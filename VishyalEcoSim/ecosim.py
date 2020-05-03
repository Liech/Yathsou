import matplotlib.pyplot as plt
import copy 

#test this:
#https://github.com/SirAnthony/slpp/blob/master/slpp.py

class Unit:
  def __init__(self,name):
    self._name = name
    self._mCost = 0.0
    self._eCost = 0.0
    self._buildTime = 0.0 
    self._progress = 0.0

    self._eProd = 20.0
    self._mProd = 1.0

    self._bPower = 10.0

    self._currentProduction = list()


  def getConsumption(self,mLimit,eLimit):
    mProd = -eLimit*self._mProd
    eProd = -self._eProd if self._eProd > 0 else -self._eProd*eLimit
  
    if not self._currentProduction:
      return (mProd, eProd)

    if type(self._currentProduction[0]) == Reclaim:
      time = self._currentProduction[0]._buildTime/self._bPower
      mPTick = -self._currentProduction[0]._mCost / time
      ePTick = -self._currentProduction[0]._eCost / time
      return (mPTick+mProd, ePTick+eProd)

    if min([mLimit,eLimit]) == 0:
      return (mProd, eProd)

    eff = min([mLimit,eLimit])
    time = self._currentProduction[0]._buildTime/(self._bPower*eff)
    mPTick = self._currentProduction[0]._mCost / time
    ePTick = self._currentProduction[0]._eCost / time
    return (mPTick+mProd, ePTick+eProd)

  
  def tick(self,mLimit,eLimit, eco):
    assert self._progress >= self._buildTime, self._name+f" ticked at {self._progress} of {self._buildTime}"
    m,e = self.getConsumption(mLimit,eLimit)
    if self._currentProduction:
      eff = min([mLimit,eLimit]) if type(self._currentProduction[0]) == Unit else 1.0
      self._currentProduction[0]._progress += self._bPower*eff

      if self._currentProduction[0]._progress >= self._currentProduction[0]._buildTime:
        print(self._currentProduction[0]._name,"done at",eco._time)
        if type(self._currentProduction[0]) == Unit:
          eco._units.append(self._currentProduction.pop(0))
        else:
          self._currentProduction.pop(0)
    return (m,e)



class Reclaim:
  def __init__(self,mass, energy, buildTime):
    self._name = f"Reclaim M{mass} E{energy}"
    self._mCost = mass
    self._eCost = energy
    self._buildTime = buildTime
    self._progress = 0

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





factory = Unit("UEF Land Factory")
factory._mCost = 240
factory._eCost = 2100
factory._buildTime = 300
factory._eProd = 0
factory._mProd = 0
factory._bPower = 20

engi = Unit("UEF T1 Engi")
engi._mCost = 52
engi._eCost = 260
engi._buildTime = 260
engi._eProd = 0
engi._mProd = 0
engi._bPower = 5

mex = Unit("UEF T1 Mex")
mex._mCost = 36
mex._eCost = 360
mex._buildTime = 60
mex._eProd = -2
mex._mProd = 2
mex._bPower = 13.01

pgen = Unit("UEF T1 Pgen")
pgen._mCost = 75
pgen._eCost = 750
pgen._buildTime = 125
pgen._eProd = 20
pgen._mProd = 0
pgen._bPower = 0

tree = Reclaim(1,10,10)
shipWreck = Reclaim(900,0,300)

game = Eco()
game.tick()
fac = copy.deepcopy(factory)
fac._currentProduction.append(copy.deepcopy(engi))
fac._currentProduction.append(copy.deepcopy(engi))
fac._currentProduction.append(copy.deepcopy(engi))
fac._currentProduction.append(copy.deepcopy(engi))
fac._currentProduction.append(copy.deepcopy(engi))
fac._currentProduction.append(copy.deepcopy(engi))
fac._currentProduction.append(copy.deepcopy(engi))
fac._currentProduction.append(copy.deepcopy(engi)) 

game._units[0]._currentProduction.append(fac)
game._units[0]._currentProduction.append(copy.deepcopy(pgen))
game._units[0]._currentProduction.append(copy.deepcopy(pgen))
game._units[0]._currentProduction.append(copy.deepcopy(mex))
game._units[0]._currentProduction.append(copy.deepcopy(pgen))
game._units[0]._currentProduction.append(copy.deepcopy(mex))
game._units[0]._currentProduction.append(copy.deepcopy(mex))
game._units[0]._currentProduction.append(copy.deepcopy(mex))
#game._units[0]._currentProduction.append(copy.deepcopy(pgen))

fac._currentProduction[0]._currentProduction.append(copy.deepcopy(mex))
#fac._currentProduction[0]._currentProduction.append(copy.deepcopy(pgen))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))

fac._currentProduction[1]._currentProduction.append(copy.deepcopy(mex))
fac._currentProduction[1]._currentProduction.append(copy.deepcopy(pgen))
fac._currentProduction[1]._currentProduction.append(copy.deepcopy(pgen))
fac._currentProduction[1]._currentProduction.append(copy.deepcopy(pgen))

#for i in range(0,500):
#  game.tick()
doSim = True
while doSim:
  game.tick()
  doSim = False
  for unit in game._units:
    if len(unit._currentProduction)>0:
      doSim = True

game.plot()