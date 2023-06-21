from django.db import models

# Create your models here.
class Pizza(models.Model):
    """Represent a pizza."""
    name = models.CharField(max_length=200)

    def __str__(self):
        """Return a string representation of the model."""
        return self.name


class Topping(models.Model):
    """Represent topping of a pizza."""
    name = models.CharField(max_length=200)
    pizza = models.ForeignKey(Pizza, on_delete=models.CASCADE)

    def __str__(self):
        """Return a string representation of the model."""
        return self.name

