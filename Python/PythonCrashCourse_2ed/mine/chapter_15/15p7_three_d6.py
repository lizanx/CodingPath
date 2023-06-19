from plotly.graph_objs import Bar, Layout
from plotly import offline

from die import Die

if __name__ == '__main__':
    die_1 = Die()
    die_2 = Die()
    die_3 = Die()
    results = []
    for n in range(50_000):
        results.append(die_1.roll() + die_2.roll() + die_3.roll())
    
    frequencies = []
    max_result = die_1.num_sides + die_2.num_sides + die_3.num_sides
    for value in range(3, max_result + 1):
        frequencies.append(results.count(value))
    print(frequencies)

    # Visualize the results.
    x_values = list(range(3, max_result+1))
    data = [Bar(x=x_values, y=frequencies)]
    x_axis_config = {"title": "Result", 'dtick': 1}
    y_axis_config = {"title": "Frequence of Result"}
    layout = Layout(title="Results of rolling three D6s 50_000 times",
            xaxis=x_axis_config, yaxis=y_axis_config)
    offline.plot({'data': data, 'layout': layout}, filename='D6_D6_D6.html')

