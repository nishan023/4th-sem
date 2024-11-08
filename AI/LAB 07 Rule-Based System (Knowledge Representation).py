rules = {
    'rainy': 'take umbrella',
    'sunny': 'wear sunglasses'
}

def rule_based_agent(percept):
    return rules.get(percept, 'do nothing')

print(rule_based_agent('rainy'))
