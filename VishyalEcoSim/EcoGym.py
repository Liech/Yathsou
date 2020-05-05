import gym
from gym import spaces
from SupComEco.Eco import Eco

class EcoGym(gym.Env):
  """Custom Environment that follows gym interface"""
  metadata = {'render.modes': ['human']}

  def __init__(self):
    super(EcoGym, self).__init__()    # Define action and observation space
    # They must be gym.spaces objects    # Example when using discrete actions:
    self.action_space = spaces.Dict()    # Example for using image as input:
    self.observation_space = spaces.Box(shape=(2, 1), dtype=np.int32)


  def _take_action(self, action):
    print(action)

  def _next_observation(self):
    obs = [self._eco._mass,self._eco._energy]
    return obs 

  def step(self, action):
    self._take_action(action)
    self._eco.step()
    # Execute one time step within the environment
    reward = 1
    done = self._eco._time>300
    obs = self._next_observation()
    return obs, reward, done, {}

  def reset(self):
    self._eco = Eco()
    # Reset the state of the environment to an initial state


  def render(self, mode='human', close=False):
    # Render the environment to the screen
    game.plot()
