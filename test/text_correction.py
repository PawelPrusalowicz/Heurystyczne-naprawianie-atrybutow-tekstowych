import pandas as pd
import numpy as np

from build.text_correction import Text_Correction

initialWordList = []
unwantedSigns = [ ',', '.', '-', ';']

def clearData ( data, unwantedSigns):
    for sign in unwantedSigns:
        data = data.replace(sign, '')
    
    return data


correction = Text_Correction()

# dostarczenie i wstepne obrobienie danych


with open('resources/textwithmistakes.txt','r') as f:

    for line in f:
        for word in line.split():
            word = clearData (word, unwantedSigns)
            
            if word:
                print (word)
                initialWordList.append(word.lower())

data_pandas = pd.Series( (v for v in initialWordList) )
list_numpy = np.array(initialWordList)



# metoda info
#correction.info()

#test czyszczenia danych. dziala tak samo dla pandas.series i numpy.array
correctedWordList = correction.correctData(initialWordList)

print (correction.info())

#correctedWordList2 = correction.correctData(data_pandas.tolist())
#correctedWordList3 = correction.correctData(list_numpy.tolist())



