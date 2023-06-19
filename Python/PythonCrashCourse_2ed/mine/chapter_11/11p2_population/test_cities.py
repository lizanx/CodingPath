import unittest
from city_functions import get_formatted_city

class CityTestCase(unittest.TestCase):
    def test_city_country(self):
        formatted_city = get_formatted_city("chicago", "america")
        self.assertEqual(formatted_city, "Chicago, America - population 0")

    def test_city_country_population(self):
        formatted_city = get_formatted_city("santiago", "chile", population=5000000)
        self.assertEqual(formatted_city, "Santiago, Chile - population 5000000")

if __name__ == '__main__':
    unittest.main()