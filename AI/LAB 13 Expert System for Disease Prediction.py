symptoms = {'fever': 'Flu', 'rash': 'Allergy'}

def diagnose(symptom):
    return symptoms.get(symptom, 'Unknown')

print(diagnose('fever'))
