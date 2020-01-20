---
title: Start Up Profit Prediction Model
date: 2019-12-06
categories: [data-analysis-projects]
permalink: /:categories/:title/
feature_img: /images/data_analysis_projects/profitpredictionmodel/profitpredictionmodel_img00.jpg
excerpt: "python, machine learning, regression, multiple linear regression, statistics, backward elimination"
purpose: "This assignment aimed at building a Multiple Linear Regression model based on 50 Start Up's Data to predict profit effects based on departmental expenditure and the state the business is operating in."
toc: true
classes: wide
---

<h2 class="text-underline">Purpose</h2>
The assignment aimed at building a Multiple Linear Regression model based on 50 Start Up's Data to predict profit effects based on departmental expenditure (R&D, Administration and Marketing) and the state (California, Florida and New York) the business is operating in.

<h2 class="text-underline">Dataset</h2>

<h2 class="text-underline">Procedure</h2>

<h2 class="text-underline">Implementation</h2>

**"The Code used to implement the Multiple Regression model**
```python
# Multiple Linear Regression

# Importing the libraries
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Importing the dataset
dataset = pd.read_csv('50_Startups.csv')
X = dataset.iloc[:, :-1].values
y = dataset.iloc[:, 4].values

# Encoding categorical data
from sklearn.preprocessing import LabelEncoder, OneHotEncoder
labelencoder = LabelEncoder()
X[:, 3] = labelencoder.fit_transform(X[:, 3])
onehotencoder = OneHotEncoder(categorical_features = [3])
X = onehotencoder.fit_transform(X).toarray()

# Avoiding the Dummy Variable Trap
X = X[:, 1:]

# Splitting the dataset into the Training set and Test set
from sklearn.cross_validation import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, random_state = 0)

# Feature Scaling
"""from sklearn.preprocessing import StandardScaler
sc_X = StandardScaler()
X_train = sc_X.fit_transform(X_train)
X_test = sc_X.transform(X_test)
sc_y = StandardScaler()
y_train = sc_y.fit_transform(y_train)"""

# Fitting Multiple Linear Regression to the Training set
from sklearn.linear_model import LinearRegression
regressor = LinearRegression()
regressor.fit(X_train, y_train)

# Predicting the Test set results
y_pred = regressor.predict(X_test)

```

<h2 class="text-underline">Testing</h2>
