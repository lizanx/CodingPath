from collections import namedtuple

Language = namedtuple('Language', 'name, type, mem_safe')
python = Language('Python', 'Dynamic', True)
print(python)
kotlin = Language('Kotlin', 'JVM', True)
print(f'{kotlin.name} - {kotlin.type} - {kotlin.mem_safe}')
name, type, mem_safe = kotlin
print(f'{name} - {type} - {mem_safe} len={len(kotlin)}')

java = kotlin._replace(name='Java')
print(java)

cpp = java._replace(**{'name': 'C++', 'type': "Static", 'mem_safe': False})
print(cpp)