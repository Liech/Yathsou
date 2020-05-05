class Reclaim:
  def __init__(self,mass, energy, buildTime):
    self._name = f"Reclaim M{mass} E{energy}"
    self._mCost = mass
    self._eCost = energy
    self._buildTime = buildTime
    self._progress = 0


  def getActivityConsumption(self, bPower, eff): #reclaim gain calculation
    time = self._buildTime/bPower
    mPTick = -self._mCost / time
    ePTick = -self._eCost / time
    return (mPTick, ePTick)


  def progress(self, bPower, eff):
    self._progress+=bPower

