import pandas as pd
import numpy as np

import unittest
from build.text_correction import Text_Correction


class TestTextCorrection(unittest.TestCase):


    def test_loadDictionary(self):
        text_correction = Text_Correction()

        text_correction.loadDictionary("resources/wordlist.txt")
        dictionary = text_correction.getDictionary()
        self.assertTrue("abandon" in dictionary)


    def test_info(self):
        text_correction = Text_Correction()

        self.assertIsNotNone(text_correction.info())
        self.assertEqual(text_correction.info(), "Used dictionary:   resources/wordlist.txt")
        

    def test_correctData(self):
        text_correction = Text_Correction()

        correctedWords = text_correction.correctData( ["dolla" , "wors"])
        self.assertEqual(["dollar", "worse"], correctedWords)

        correctedWords = text_correction.correctData( [])
        self.assertEqual([], correctedWords)



if __name__ == '__main__':
    unittest.main()

