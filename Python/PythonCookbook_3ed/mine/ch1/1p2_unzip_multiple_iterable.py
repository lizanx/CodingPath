record = ('Dave', 'dave@example.com', '773-555-1212', '847-555-1212')
name, email, *phone_numbers = record
print(f'{name} - {email} - {phone_numbers}')


print()
records = [
    ('foo', 1, 2),
    ('bar', 'hello'),
    ('foo', 3, 4),
]
for tag, *args in records:
    if tag == 'foo':
        print(f'{tag}: {args}')

print()
record = ('ACME', 50, 123.45, (12, 18, 2012))
name, *_, (month, day, year) = record
print(f'{name} - {year}/{month}/{day}')
