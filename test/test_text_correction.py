import pandas as pd
import numpy as np

import unittest
from build.text_correction import Text_Correction


class TestTextCorrection(unittest.TestCase):


    def test_info(self):

        self.text_correction = Text_Correction("resources/test_dictionary_example.txt", "resources/test_english_words_popularity.txt")
        self.assertIsNotNone(self.text_correction.info())
        self.assertEqual(self.text_correction.info(), "Used dictionary:   resources/test_dictionary_example.txt")
    
    

    def test_NorvigCorrectData(self):

        self.text_correction = Text_Correction("resources/test_dictionary_example.txt", "resources/test_english_words_popularity.txt")
        
        data_pandas = pd.Series( ( ["abbrevviate" , "abdoen"] ) )

        correctedWords = self.text_correction.correctData("norvig", True, data_pandas.tolist() )
        
        self.assertEqual(["abbreviate", "abdomen"], correctedWords)

        correctedWords = self.text_correction.correctData( "norvig", True, [] )
        self.assertEqual([], correctedWords)
            
            

    def test_TrieCorrectData(self):
        
        self.text_correction = Text_Correction("resources/test_dictionary_example.txt", "resources/test_english_words_popularity.txt")
        
        list_numpy = np.array(["abbrevviate" , "abdoen"])
        correctedWords = self.text_correction.correctData( "trie", True, list_numpy.tolist())
        
        self.assertEqual(["abbreviate", "abdomen"], correctedWords)
        correctedWords = self.text_correction.correctData(  "norvig", True, [] )
        self.assertEqual([], correctedWords)
    
    
        

    def test_SymspellCorrectData(self):
    
        self.text_correction = Text_Correction("resources/test_dictionary_example.txt", "resources/test_english_words_popularity.txt")

        correctedWords = self.text_correction.correctData(  "symspell", True, ["abbrevviate" , "abdoen"])
                    
        self.assertEqual(["abbreviate", "abdomen"], correctedWords)
            
        correctedWords = self.text_correction.correctData( "norvig",  True, [])
        self.assertEqual([], correctedWords)




if __name__ == '__main__':
    unittest.main()

