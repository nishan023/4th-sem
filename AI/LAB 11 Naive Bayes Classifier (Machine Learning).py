#machine Learning/Naive Bayes Classifier
from sklearn.naive_bayes import GaussianNB
from sklearn.model_selection import train_test_split
from sklearn import datasets

# Load dataset
data = datasets.load_iris()
X_train, X_test, y_train, y_test = train_test_split(data.data, data.target, test_size=0.3)

# traineing Naive Bayes
model = GaussianNB()
model.fit(X_train, y_train)

print(f"Accuracy: {model.score(X_test, y_test)}")