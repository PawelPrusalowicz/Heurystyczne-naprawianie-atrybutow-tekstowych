import pandas as pd
import numpy as np

from build.text_correction import Text_Correction

initialWordList = []
unwantedSigns = [ ',', '.', '-', ';']

def clearData ( data, unwantedSigns):
    for sign in unwantedSigns:
        data = data.replace(sign, '')
    
    return data


correction = Text_Correction('resources/dictionary_example.txt','resources/english_words_popularity.txt')

# dostarczenie i wstepne obrobienie danych


with open('resources/text_with_mistakes.txt','r') as f:

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
correctedWordList = correction.correctData("trie", True, initialWordList)
correction.loadDictionary('resources/text_with_mistakes.txt')
print('get1')
lista = correction.getDictionary()
print(lista)
correction.loadDictionary('resources/probny.txt')
print('get2')
lista = correction.getDictionary()
print(lista)
correction.loadDictionary('resources/text_with_mistakes.txt')
print('get3')
lista = correction.getDictionary()
print(lista)


#correctedWordList2 = correction.correctData(data_pandas.tolist())
#correctedWordList3 = correction.correctData(list_numpy.tolist())



