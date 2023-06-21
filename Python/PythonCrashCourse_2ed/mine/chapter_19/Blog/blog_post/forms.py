from django import forms

from .models import BlogPost

class BlogPostForm(forms.ModelForm):
    """Form for BlogPost."""
    class Meta:
        model = BlogPost
        fields = ['title', 'text']
        labels = {'title': '', 'text': ''}
