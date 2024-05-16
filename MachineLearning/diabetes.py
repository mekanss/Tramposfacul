import matplotlib.pyplot as plt # importando negocio que faz plot
import numpy as np # importando numpy, por que nao?
import pandas as pd # Vou precisar disso, sou bibliotecario
from sklearn.datasets import load_diabetes    # Importando modelo
from sklearn.neighbors import KNeighborsRegressor # Definindo o metodo
from sklearn.preprocessing import StandardScaler, QuantileTransformer # Definindo 2 pre process
from sklearn.pipeline import Pipeline # Criar um pipeline pra colocar o fit dps dela, meio esquisito mas aceito
from sklearn.model_selection import GridSearchCV # O amigo que vai colocar a pipeline dentro Pra fazer 70;30



#print(load_diabetes()['DESCR'])   Isso daqui printa as infos do database...
#modelo = KNeighborsRegressor() # Dando nome ao objeto que é o metodo

X,y = load_diabetes(return_X_y=True) # Voltando colunas X e Y, acho que essa porra é exclusiva pra datasets do sklearn
#NovoX = QuantileTransformer(n_quantiles=100).fit_transform(X) # Normalizando X

pipa = Pipeline(steps=[              # pipa é a pipeline, ela é mais fancy pq aplica varias cositas de uma vez
    ("scale",QuantileTransformer(n_quantiles=100)),
    ("model",KNeighborsRegressor())
])


modelo = GridSearchCV(estimator=pipa,                                    # Meu modelo agora vai virar essa parada + complexa mas mais mutavel
             param_grid={'model__n_neighbors': [1,2,3,4,5,6,7,8,9,10]},
             cv=3)





modelo.fit(X,y) # Fit para X e Y
predicoes = modelo.predict(X) # previsao

plt.xlabel('Previsao') # dando nome ao eixo X e Y
plt.ylabel('Verdadeiro')
plt.scatter(predicoes, y) # criando um plot de previsoes X coisas corretas
plt.show() # mostrar o plot

df = pd.DataFrame(modelo.cv_results_) # Mostrar alguns dados interessantes, rank_test_score é interessante!
print(df.to_string())
