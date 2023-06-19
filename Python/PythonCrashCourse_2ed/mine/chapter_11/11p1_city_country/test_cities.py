import unittest
from city_functions import get_formatted_city

class CityTestCase(unittest.TestCase):
    def test_city_country(self):
        formatted_city = get_formatted_city("chicago", "america")
        self.assertEqual(formatted_city, "Chicago, America")

if __name__ == '__main__':
    unittest.main()