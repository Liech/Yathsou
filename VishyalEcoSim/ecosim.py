import matplotlib.pyplot as plt
import copy 

#test this:
#https://github.com/SirAnthony/slpp/blob/master/slpp.py
from SupComEco.Unit import Unit
from SupComEco.Eco import Eco
from SupComEco.Reclaim import Reclaim
from SupComEco.Idle import Idle


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

fac._currentProduction[0]._currentProduction.append(Idle(5))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(mex))
#fac._currentProduction[0]._currentProduction.append(copy.deepcopy(pgen))
fac._currentProduction[0]._currentProduction.append(Idle(1))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))
fac._currentProduction[0]._currentProduction.append(Idle(1))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))
fac._currentProduction[0]._currentProduction.append(Idle(1))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))
fac._currentProduction[0]._currentProduction.append(Idle(1))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))
fac._currentProduction[0]._currentProduction.append(Idle(1))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))
fac._currentProduction[0]._currentProduction.append(Idle(1))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))
fac._currentProduction[0]._currentProduction.append(Idle(1))
fac._currentProduction[0]._currentProduction.append(copy.deepcopy(tree))

fac._currentProduction[1]._currentProduction.append(Idle(5))
fac._currentProduction[1]._currentProduction.append(copy.deepcopy(mex))
fac._currentProduction[1]._currentProduction.append(Idle(1))
fac._currentProduction[1]._currentProduction.append(copy.deepcopy(pgen))
fac._currentProduction[1]._currentProduction.append(Idle(1))
fac._currentProduction[1]._currentProduction.append(copy.deepcopy(pgen))
fac._currentProduction[1]._currentProduction.append(Idle(1))
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