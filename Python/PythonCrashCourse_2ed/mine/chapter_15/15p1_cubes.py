import matplotlib.pyplot as plt

def save_cube_pic(in_list=None):
    if not in_list:
        return
    y_values = [i**3 for i in in_list]
    fig, ax = plt.subplots()
    # 15-2: add corlor map
    ax.scatter(in_list, y_values, s=3, c=y_values, cmap=plt.cm.winter)
    
    plt.style.use('ggplot')
    ax.set_title('Cubes', fontsize=14)
    ax.set_xlabel('Values', fontsize=10)
    ax.set_ylabel('Cube of Values', fontsize=10)
    ax.tick_params(axis='both', which='major', labelsize=10)
    ax.axis([0, in_list[-1]+1, 0, y_values[-1]+1])

    plt.savefig(str(in_list[-1])+'_cube.png')


if __name__ == '__main__':
    l1 = range(1, 6)
    save_cube_pic(l1)

    l2 = range(1, 5001)
    save_cube_pic(l2)