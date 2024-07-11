import plotly.figure_factory as ff
import pandas as pd

# Данные для диаграммы Ганта
data = [
    dict(Task='Task 1', Start='2024-07-10', Finish='2024-07-15'),
    dict(Task='Task 2', Start='2024-07-11', Finish='2024-07-17'),
    dict(Task='Task 3', Start='2024-07-12', Finish='2024-07-14')
]

# Создание диаграммы Ганта с помощью Plotly
fig = ff.create_gantt(
    data,
    index_col='Task',
    show_colorbar=True,
    group_tasks=True  # Группировка задач в одной области
)

# Добавление JavaScript кода для поддержки перетаскивания элементов
fig.update_layout(
    updatemenus=[
        dict(
            type="buttons",
            buttons=[
                dict(label="Save",
                     method="relayout",
                     args=["dragmode", "select"]),
                dict(label="Delete",
                     method="restyle",
                     args=[{"visible": [False, True]},
                           {"title": "Deleted!"}]),
            ],
        )
    ]
)

# Отображение диаграммы
fig.show()
