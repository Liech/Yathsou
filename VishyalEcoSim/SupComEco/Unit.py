
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


  def getActivityConsumption(self, bPower, eff): #production cost calculation
    if eff == 0:
      return (0, 0)
    time = self._buildTime/(bPower* eff)
    mPTick = self._mCost / time
    ePTick = self._eCost / time
    return (mPTick, ePTick)


  def progress(self, bPower, eff):
    self._progress+=bPower*eff


  def getConsumption(self,mLimit,eLimit):
    mProd = -eLimit*self._mProd
    eProd = -self._eProd if self._eProd > 0 else -self._eProd*eLimit
    eff = min([mLimit,eLimit])
  
    if not self._currentProduction:
      return (mProd, eProd)

    mPTick, ePTick = self._currentProduction[0].getActivityConsumption(self._bPower,eff)
    return (mPTick+mProd, ePTick+eProd)


  
  def tick(self,mLimit,eLimit, eco):
    assert self._progress >= self._buildTime, self._name+f" ticked at {self._progress} of {self._buildTime}"
    m,e = self.getConsumption(mLimit,eLimit)
    eff = min([mLimit,eLimit]) 
    if self._currentProduction:
      self._currentProduction[0].progress(self._bPower,eff)

      if self._currentProduction[0]._progress >= self._currentProduction[0]._buildTime:
        print(self._currentProduction[0]._name,"done at",eco._time,"by",self._name)
        if type(self._currentProduction[0]) == Unit:
          eco._units.append(self._currentProduction.pop(0))
        else:
          self._currentProduction.pop(0)
    return (m,e)

