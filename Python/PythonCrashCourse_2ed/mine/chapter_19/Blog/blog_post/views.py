from django.shortcuts import redirect, render
from django.contrib.auth.decorators import login_required
from django.http import Http404

from .models import BlogPost
from .forms import BlogPostForm

# Create your views here.
def index(request):
    """Home page for blog_post."""
    posts = BlogPost.objects.order_by('date_added')
    context = {'posts': posts}
    return render(request, 'blog_post/index.html', context)

def post(request, post_id):
    """Details of a post."""
    post = BlogPost.objects.get(id=post_id)
    context = {'post': post}
    return render(request, 'blog_post/post.html', context)

@login_required
def add_post(request):
    """Add a new post."""
    if request.method != 'POST':
        form = BlogPostForm()
    else:
        form = BlogPostForm(data=request.POST)
        if form.is_valid():
            new_post = form.save(commit=False)
            new_post.owner = request.user
            new_post.save()
            return redirect('blog_post:index')
    context = {'form': form}
    return render(request, 'blog_post/add_post.html', context)

@login_required
def edit_post(request, post_id):
    """Edit a post."""
    post = BlogPost.objects.get(id=post_id)
    check_post_owner(post, request.user)
    if request.method != 'POST':
        form = BlogPostForm(instance=post)
    else:
        form = BlogPostForm(instance=post, data=request.POST)
        if form.is_valid():
            form.save()
            return redirect('blog_post:index')
    context = {'post': post, 'form': form}
    return render(request, 'blog_post/edit_post.html', context)

# Util functions, used in view functions.
def check_post_owner(post, user):
    """Make sure that a post belongs to current user."""
    if post.owner == user:
        return True
    raise Http404