
class Idle:
  def __init__(self,time):
    self._name = f"Wait/Walk {time}s"
    self._buildTime = time
    self._progress = 0

  def progress(self, bPower, eff):
    self._progress+=1

  def getActivityConsumption(self, bPower, eff): #well
    return (0, 0)


