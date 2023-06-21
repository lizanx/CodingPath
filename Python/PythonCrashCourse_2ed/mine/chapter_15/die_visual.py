from plotly.graph_objs import Bar, Layout
from plotly import offline

from die import Die

if __name__ == '__main__':
    die = Die()
    results = []
    for n in range(1000):
        results.append(die.roll())
    
    frequencies = []
    for value in range(1, die.num_sides + 1):
        frequencies.append(results.count(value))
    print(frequencies)

    # Visualize the results.
    x_values = list(range(1, die.num_sides+1))
    data = [Bar(x=x_values, y=frequencies)]
    x_axis_config = {"title": "Result"}
    y_axis_config = {"title": "Frequence of Result"}
    layout = Layout(title="Results of rolling one D6 1000 times",
            xaxis=x_axis_config, yaxis=y_axis_config)
    offline.plot({'data': data, 'layout': layout}, filename='D6.html')

