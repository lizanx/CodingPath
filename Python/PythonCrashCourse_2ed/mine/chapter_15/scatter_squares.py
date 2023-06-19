import matplotlib.pyplot as plt

x_values = range(1, 1001)
y_values = [i**2 for i in x_values]

plt.style.use('ggplot')

fig, ax = plt.subplots()
ax.scatter(x_values, y_values, s=3, c=y_values, cmap=plt.cm.inferno)

ax.set_title("Square Numbers", fontsize=24)
ax.set_xlabel("Value", fontsize=14)
ax.set_ylabel("Square of Values", fontsize=14)
ax.tick_params(axis='both', which='major', labelsize=14)
ax.axis([0, 1100, 0, 1100000])

# plt.show()
plt.savefig("tmp.png", bbox_inches='tight')