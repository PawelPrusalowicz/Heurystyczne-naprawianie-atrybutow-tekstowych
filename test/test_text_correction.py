import pandas as pd
import numpy as np

import unittest
from build.text_correction import Text_Correction


class TestTextCorrection(unittest.TestCase):

    @classmethod
    def setUp(self):
        self.text_correction = Text_Correction()

    def test_loadDictionary(self):

        self.text_correction.loadDictionary("resources/dictionary_example.txt")
        dictionary = self.text_correction.getDictionary()
        self.assertTrue("abandon" in dictionary)


    def test_info(self):

        self.assertIsNotNone(self.text_correction.info())
        self.assertEqual(self.text_correction.info(), "Used dictionary:   resources/dictionary_example.txt")
        

    def test_correctData(self):

        correctedWords = self.text_correction.correctData( ["dolla" , "wors"])
        self.assertEqual(["doll", "worn"], correctedWords)

        correctedWords = self.text_correction.correctData( [])
        self.assertEqual([], correctedWords)

    def test_trieCorrection(self):

        correctedWords = self.text_correction.trieCorrection( ["dolla" , "wors"])
        print (correctedWords)
        # self.assertEqual(["dollar", "worse"], correctedWords)

        # correctedWords = self.text_correction.correctData( [])
        # self.assertEqual([], correctedWords)



if __name__ == '__main__':
    unittest.main()

