import json
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.colors as mcolors
from matplotlib.widgets import TextBox, Button

# Загрузка данных из JSON файла
with open('operations_data.json', 'r') as file:
    data = json.load(file)

js_operations = data['js_operations']
ms_operations = data['ms_operations']

# Словари для хранения прямоугольников и их начальных данных
rect_dict = {}
initial_data = {}

# Функция для построения диаграммы Ганта
def plot_gantt_chart(operations, ax, y_label, group_by, color_by, reverse_y=False):
    groups = {}
    for op in operations:
        key = op[group_by]
        if key not in groups:
            groups[key] = []
        groups[key].append(op)

    yticks = []
    yticklabels = []

    unique_color_keys = list(set(op[color_by] for op in operations))
    colors = list(mcolors.TABLEAU_COLORS.values())[:len(unique_color_keys)]
    color_map = dict(zip(unique_color_keys, colors))

    max_key = max(groups.keys()) + 1  # добавляем запас по оси Y

    for i, key in enumerate(sorted(range(1, max_key + 1), reverse=reverse_y)):
        if key in groups:
            ops = groups[key]
            for op in ops:
                start = op['Start']
                end = op['Finish']
                other_key = op[color_by]
                color = color_map[other_key]

                rect = patches.Rectangle((start, i - 0.4), end - start, 0.8, edgecolor='black', facecolor=color, alpha=0.5, picker=True)
                ax.add_patch(rect)
                if group_by == 'Machine':
                    text = ax.text(start + (end - start) / 2, i, f'Job {op["Job"]}', ha='center', va='center', color='white')
                else:
                    text = ax.text(start + (end - start) / 2, i, f'Machine {op["Machine"]}', ha='center', va='center', color='white')

                # Сохраняем прямоугольники и данные
                rect_dict[rect] = (op, ax, text, color)
                initial_data[rect] = (start, end, i)

        yticks.append(i)
        yticklabels.append(f'{group_by} {key}')

    ax.set_xlabel('Time')
    ax.set_ylabel(y_label)
    ax.set_yticks(yticks)
    ax.set_yticklabels(yticklabels)
    ax.set_xlim(0, max(op['Finish'] for op in operations) + 10)
    ax.set_ylim(-0.5, len(yticks) - 0.5)
    ax.grid(True)

fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True, figsize=(12, 8))

# График для машин
plot_gantt_chart(js_operations, ax1, 'Machines', 'Machine', 'Job', reverse_y=True)
# График для задач
plot_gantt_chart(js_operations, ax2, 'Jobs', 'Job', 'Machine', reverse_y=True)

# Переменные для хранения активного прямоугольника и оси
active_rect = None

# Функция для обработки кликов на барах
def on_pick(event):
    global active_rect
    if isinstance(event.artist, patches.Rectangle):
        if active_rect is not None:
            active_rect.set_edgecolor('black')
            active_rect.set_linewidth(1)
            active_rect.set_alpha(0.5)
        active_rect = event.artist
        active_rect.set_edgecolor('red')
        active_rect.set_linewidth(2)
        active_rect.set_alpha(1.0)
        op, _, _, color = rect_dict[active_rect]
        # Обновляем текстовые поля
        start_box.set_val(str(op['Start']))
        finish_box.set_val(str(op['Finish']))
        job_box.set_val(str(op['Job']))
        machine_box.set_val(str(op['Machine']))
        fig.canvas.draw_idle()

# Функция для обновления данных бара
def update_bar(event):
    global active_rect
    if active_rect is not None:
        op, ax, text, color = rect_dict[active_rect]
        new_start = int(start_box.text)
        new_finish = int(finish_box.text)
        new_job = int(job_box.text)
        new_machine = int(machine_box.text)

        def update_linked_rects(op, new_start, new_finish, new_job, new_machine):
            for rect, (related_op, related_ax, related_text, related_color) in rect_dict.items():
                if related_op == op:
                    related_op['Start'] = new_start
                    related_op['Finish'] = new_finish
                    rect.set_x(new_start)
                    rect.set_width(new_finish - new_start)
                    related_text.set_x(new_start + (new_finish - new_start) / 2)

                    if related_ax == ax1:
                        if related_op['Machine'] != new_machine:
                            related_op['Machine'] = new_machine
                            new_y = [i for i, key in enumerate(sorted(set(op['Machine'] for op in js_operations), reverse=True)) if key == new_machine][0]
                            rect.set_y(new_y - 0.4)
                            related_text.set_y(new_y)
                            related_text.set_text(f'Machine {new_machine}')
                    elif related_ax == ax2:
                        if related_op['Job'] != new_job:
                            related_op['Job'] = new_job
                            new_y = [i for i, key in enumerate(sorted(set(op['Job'] for op in js_operations), reverse=True)) if key == new_job][0]
                            rect.set_y(new_y - 0.4)
                            related_text.set_y(new_y)
                            related_text.set_text(f'Job {new_job}')
            fig.canvas.draw_idle()

        # Обновляем данные для бара на графике Machines
        if ax == ax1:
            update_linked_rects(op, new_start, new_finish, new_job, new_machine)
        # Обновляем данные для бара на графике Jobs
        elif ax == ax2:
            update_linked_rects(op, new_start, new_finish, new_job, new_machine)

        # Сбрасываем поля
        start_box.set_val('')
        finish_box.set_val('')
        job_box.set_val('')
        machine_box.set_val('')
        active_rect = None

# Функция для сброса вида до оригинального
def reset_view(event):
    global active_rect
    ax1.set_xlim(0, max(op['Finish'] for op in js_operations) + 10)
    ax2.set_xlim(0, max(op['Finish'] for op in js_operations) + 10)
    ax1.set_ylim(-0.5, max(op['Machine'] for op in js_operations) + 1.5)
    ax2.set_ylim(-0.5, max(op['Job'] for op in js_operations) + 1.5)
    for rect, (op, ax, text, color) in rect_dict.items():
        start, end, i = initial_data[rect]
        rect.set_x(start)
        rect.set_width(end - start)
        rect.set_y(i - 0.4)
        text.set_x(start + (end - start) / 2)
        text.set_y(i)
    if active_rect is not None:
        active_rect.set_edgecolor('black')
        active_rect.set_linewidth(1)
        active_rect.set_alpha(0.5)
        active_rect = None
    fig.canvas.draw_idle()

# Создание текстовых полей для ввода новых значений
axbox1 = plt.axes([0.1, 0.01, 0.1, 0.05])
axbox2 = plt.axes([0.25, 0.01, 0.1, 0.05])
axbox3 = plt.axes([0.4, 0.01, 0.1, 0.05])
axbox4 = plt.axes([0.55, 0.01, 0.1, 0.05])
axbutton = plt.axes([0.7, 0.01, 0.1, 0.05])
axreset = plt.axes([0.85, 0.01, 0.1, 0.05])

start_box = TextBox(axbox1, 'Start Time', initial="0")
finish_box = TextBox(axbox2, 'Finish Time', initial="0")
job_box = TextBox(axbox3, 'Job', initial="1")
machine_box = TextBox(axbox4, 'Machine', initial="1")

button = Button(axbutton, 'Apply')
button.on_clicked(update_bar)

reset_button = Button(axreset, 'Reset')
reset_button.on_clicked(reset_view)

fig.canvas.mpl_connect('pick_event', on_pick)

plt.tight_layout()
plt.show()
