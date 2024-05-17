import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import OneHotEncoder
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import HistGradientBoostingClassifier
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import f1_score, confusion_matrix
from sklearn.model_selection import train_test_split

# Ler o CSV
df = pd.read_csv("Yugi_db_cleaned.csv")

features_to_encode = ['Attribute', 'Types', 'Effect types', 'Rarity', 'ATK / DEF','Effect types','ATK / LINK'] # Escolher Features que vao ser HOTCODED (Que sao string e irão virar float)
df_filtered = df.dropna(subset=['Level'])   # Dropar no Y onde o nivel é NaN, ou seja com links e XYZ
X = df_filtered[features_to_encode]     # Colocando as features que vou encodar

# One-hot encode the categorical features
encoder = OneHotEncoder(handle_unknown='ignore')  # Crio o encoder
encoded_features = encoder.fit_transform(X).toarray()   # Esse to array serve pra resolver um problema que estava tendo, Gemini me deu a call
encoded_features_df = pd.DataFrame(encoded_features, columns=encoder.get_feature_names_out(X.columns))  # Crio novo dataframe, encodado

# Retirar as features que nao quero, e fundir com as que eu quero, acho que isso ta errado quiça...
other_features = df_filtered.drop(columns=features_to_encode + ['Other names','Card_name','Image_name','Card-set','Card_number','Status','Ritual required','Link Arrows','Card type','Ritual required','Property', 'Ritual Monster required', 'Summoned by the effect of', 'Other names (Japanese)'])
X = pd.concat([encoded_features_df, other_features.reset_index(drop=True)], axis=1)

# Variavel a se descobrir
y = df_filtered['Level'].values

# Teste e treinamento, 0.2 pra 0.8
X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=0.2, random_state=42)  


param_grid = {
    #'max_iter': [100, 200, 300],  # The maximum number of iterations, or trees
    'max_depth': [None],  # The maximum depth of each tree. None means no limit.    PARAMETROS PARA SE TESTAR NA GRID... TINHA 3,5,7 AQUI
    #'min_samples_leaf': [5, 10, 20],  # The minimum number of samples per leaf node
    # 'learning_rate': [0.1, 0.01, 0.001],  # The learning rate, also known as shrinkage
    #'l2_regularization': [0.0, 0.1, 1.0],  # The L2 regularization parameter. Also known as alpha.
}



grid = GridSearchCV(
    estimator=HistGradientBoostingClassifier(),
    cv=4,
    param_grid=param_grid
)

# Treinamento
# mod = HistGradientBoostingClassifier()
grid.fit(X_train, y_train)

# Predição
predicoes = grid.predict(X_val)

# Matriz de Confusão
cm = confusion_matrix(y_val, predicoes)
print("Matriz de Confusão:")
print(cm)

# f1score
f1 = f1_score(y_val, predicoes, average='weighted')

# Visualização gráfica da Matriz de Confusão
plt.figure(figsize=(10,7))
plt.matshow(cm, cmap=plt.cm.Blues, fignum=1)
plt.title('Matriz de Confusão')
plt.colorbar()
plt.ylabel('Verdadeiro')
plt.xlabel('Previsão')
plt.show()

#prints batuta
#print(pd.DataFrame(grid.cv_results_))
print(f1)
plt.xlabel('Previsao') # dando nome ao eixo X e Y
plt.ylabel('Verdadeiro')
plt.scatter(predicoes, y_val) # criando um plot de previsoes X coisas corretas
plt.show() # mostrar o plot

### ----------------------------------------------------------------------
