from plotly.graph_objs import Bar, Layout
from plotly import offline

from die import Die

if __name__ == '__main__':
    die_1 = Die()
    die_2 = Die()
    results = [(die_1.roll() + die_2.roll()) for n in range(5000)]
    # for n in range(5000):
    #     results.append(die_1.roll() + die_2.roll())
    
    # frequencies = []
    max_result = die_1.num_sides + die_2.num_sides
    # for value in range(2, max_result + 1):
    #     frequencies.append(results.count(value))
    frequencies = [results.count(value) for value in range(2, max_result + 1)]
    print(frequencies)

    # Visualize the results.
    x_values = list(range(2, max_result+1))
    data = [Bar(x=x_values, y=frequencies)]
    x_axis_config = {"title": "Result", 'dtick': 1}
    y_axis_config = {"title": "Frequence of Result"}
    layout = Layout(title="Results of rolling two D6s 5000 times",
            xaxis=x_axis_config, yaxis=y_axis_config)
    offline.plot({'data': data, 'layout': layout}, filename='D6_D6_comprehension.html')

