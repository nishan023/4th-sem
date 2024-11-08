class SimpleReflexAgent:
    def __init__(self):
        self.state = None

    def perceive(self, environment):
        return environment['percept']

    def act(self, percept):
        if percept == 'dirty':
            return 'clean'
        else:
            return 'move'

# Example environment
environment = {'percept': 'dirty'}

# Agent
agent = SimpleReflexAgent()
percept = agent.perceive(environment)
action = agent.act(percept)
print(f'Perceived: {percept}, Action: {action}')
