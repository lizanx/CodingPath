"""Defines URL patterns for learning_logs."""

from django.urls import path
from . import views


app_name = 'learning_logs'
urlpatterns = [
    # Home page
    path(route='', view=views.index, name='index'),
    # Page that shows all topics.
    path(route='topics/', view=views.topics, name='topics'),
    # Detail page for a single topic.
    path(route='topic/<int:topic_id>/', view=views.topic, name='topic'),
    # Page for adding a new topic.
    path(route='new_topic/', view=views.new_topic, name='new_topic'),
    # Page for adding a new entry.
    path(route='new_entry/<int:topic_id>/', view=views.new_entry, name='new_entry'),
    # Page for editing an entry.
    path(route='edit_entry/<int:entry_id>/', view=views.edit_entry, name='edit_entry'),
]