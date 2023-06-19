import unittest

from employee import Employee

class TestEmployee(unittest.TestCase):
    def setUp(self):
        self.e = Employee("Bruce", "Lee", 1_000_000)
    
    def test_give_default_raise(self):
        salary = self.e.annual_salary
        self.e.give_raise()
        self.assertEqual(self.e.annual_salary, salary + 5000)
    
    def test_give_custom_raise(self):
        salary = self.e.annual_salary
        self.e.give_raise(9999)
        self.assertEqual(self.e.annual_salary, salary + 9999)

if __name__ == '__main__':
    unittest.main()