import matplotlib.pyplot as plt
import numpy as np

# Данные для графика
categories = ['Category A', 'Category B', 'Category C', 'Category D']
values = [5, 10, 15, 20]

fig, ax = plt.subplots()
bars = ax.barh(categories, values, align='center', picker=True)
draggable_bar = None

def on_pick(event):
    global draggable_bar
    if isinstance(event.artist, plt.Rectangle):
        draggable_bar = event.artist
        fig.canvas.mpl_connect('motion_notify_event', on_drag)

def on_drag(event):
    global draggable_bar
    if draggable_bar is not None:
        draggable_bar.set_width(event.xdata)
        fig.canvas.draw()

def on_release(event):
    global draggable_bar
    draggable_bar = None
    fig.canvas.mpl_disconnect('motion_notify_event')

fig.canvas.mpl_connect('pick_event', on_pick)
fig.canvas.mpl_connect('button_release_event', on_release)

plt.show()
