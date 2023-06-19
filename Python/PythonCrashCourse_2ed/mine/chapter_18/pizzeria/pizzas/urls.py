"""Defines URL patterns for pizzas."""

from django.urls import path
from . import views

app_name = 'pizzas'
urlpatterns = [
    # Home page
    path(route='', view=views.index, name='index'),
    # Show all pizzas
    path(route='pizzas/', view=views.pizzas, name='pizzas'),
    # Show topping details of a pizza
    path(route='pizza/<str:pizza_name>/', view=views.pizza, name='pizza'),
]