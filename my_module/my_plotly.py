import dash
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input, Output, State
import plotly.figure_factory as ff

# Данные для диаграммы Ганта
tasks = ['Task 1', 'Task 2', 'Task 3']
start_dates = ['2024-07-10', '2024-07-11', '2024-07-12']
finish_dates = ['2024-07-15', '2024-07-17', '2024-07-14']

data = [
    dict(Task=tasks[i], Start=start_dates[i], Finish=finish_dates[i])
    for i in range(len(tasks))
]

# Создание диаграммы Ганта с помощью Plotly
fig = ff.create_gantt(data, index_col='Task', show_colorbar=True, group_tasks=True)

# Инициализация Dash
app = dash.Dash(__name__)

app.layout = html.Div([
    dcc.Graph(
        id='gantt-chart',
        figure=fig,
        config={'editable': True, 'edits': {'shapePosition': True}}
    ),
    html.Button('Save Changes', id='save-button', n_clicks=0),
    dcc.Store(id='gantt-data', data=data)
])

@app.callback(
    Output('gantt-data', 'data'),
    Input('save-button', 'n_clicks'),
    State('gantt-chart', 'relayoutData'),
    State('gantt-data', 'data')
)
def update_data(n_clicks, relayoutData, data):
    if n_clicks > 0 and relayoutData:
        for shape in relayoutData.get('shapes', []):
            if 'name' in shape:
                task = shape['name']
                start_date = datetime.fromtimestamp(shape['x0'] / 1000).strftime('%Y-%m-%d')
                end_date = datetime.fromtimestamp(shape['x1'] / 1000).strftime('%Y-%m-%d')
                for d in data:
                    if d['Task'] == task:
                        d['Start'] = start_date
                        d['Finish'] = end_date
    return data

@app.callback(
    Output('gantt-chart', 'figure'),
    Input('gantt-data', 'data')
)
def update_gantt_chart(data):
    return ff.create_gantt(data, index_col='Task', show_colorbar=True, group_tasks=True)

if __name__ == '__main__':
    app.run_server(debug=True)
