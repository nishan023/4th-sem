class Predicate:
    def __init__(self, subject, predicate):
        self.subject = subject
        self.predicate = predicate

    def evaluate(self, facts):
        return (self.subject, self.predicate) in facts

facts = {('Socrates', 'man')}
p = Predicate('Socrates', 'man')
print(p.evaluate(facts))
