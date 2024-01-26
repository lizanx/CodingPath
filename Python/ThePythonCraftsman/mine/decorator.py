from functools import wraps
from time import sleep

def timer1(func):
    """Decorator to delay function call"""
    @wraps(func)
    def decorator(*args, **kwargs):
        """Read Decorator"""
        print('Timer-1: sleep 1 second')
        sleep(1)
        return func(*args, **kwargs)
    return decorator

def timer2(*, duration=1):
    """Decorator to delay 'duration' seconds"""
    def decorator(func):
        """Decorator function"""
        @wraps(func)
        def wrapper(*args, **kwargs):
            """Wrapper function"""
            print('Wrapper function')
            sleep(duration)
            return func(*args, **kwargs)
        return wrapper
    return decorator

@timer2(duration=3)
def greet(name='Mr. Nobody'):
    """Greet somebody."""
    print(f'Hello, {name}')

if __name__ == '__main__':
    print(greet.__name__)
    print(greet.__doc__)
    greet()
    greet('Gavin')
