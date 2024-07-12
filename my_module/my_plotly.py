import dash
from dash import dcc, html
from dash.dependencies import Input, Output, State
import plotly.figure_factory as ff
import json
from datetime import datetime

# Чтение данных из JSON-файла
with open('operations_data.json', 'r') as f:
    data = json.load(f)

js_operations = data['js_operations']
ms_operations = data['ms_operations']

# Создание данных для диаграммы Ганта
def create_gantt_data(operations, group_by):
    return [
        dict(Task=f'{group_by} {op[group_by]}', Start=op['Start'], Finish=op['Finish'], Resource=f'{group_by} {op[group_by]}', customdata=op[group_by])
        for op in operations
    ]

gantt_data_js = create_gantt_data(js_operations, 'Job')
gantt_data_ms = create_gantt_data(ms_operations, 'Machine')

fig_js = ff.create_gantt(gantt_data_js, index_col='Resource', show_colorbar=True, group_tasks=True)
fig_ms = ff.create_gantt(gantt_data_ms, index_col='Resource', show_colorbar=True, group_tasks=True)

# Инициализация Dash
app = dash.Dash(__name__)

app.layout = html.Div([
    html.H1('Interactive Gantt Charts'),
    html.Div([
        dcc.Graph(
            id='gantt-chart-js',
            figure=fig_js,
            config={'editable': True, 'edits': {'shapePosition': True, 'titleText': True}}
        ),
        dcc.Graph(
            id='gantt-chart-ms',
            figure=fig_ms,
            config={'editable': True, 'edits': {'shapePosition': True, 'titleText': True}}
        ),
    ]),
    html.Div([
        html.Label('Start:'),
        dcc.Input(id='start-input', type='number'),
        html.Label('Finish:'),
        dcc.Input(id='finish-input', type='number'),
        html.Button('Update Bar', id='update-button', n_clicks=0)
    ]),
    html.Button('Save Changes', id='save-button', n_clicks=0),
    dcc.Store(id='gantt-data-js', data=gantt_data_js),
    dcc.Store(id='gantt-data-ms', data=gantt_data_ms),
    dcc.Store(id='selected-task', data={'task': None, 'chart': None})
])

@app.callback(
    [Output('gantt-data-js', 'data'),
     Output('gantt-data-ms', 'data')],
    [Input('save-button', 'n_clicks'),
     Input('update-button', 'n_clicks')],
    [State('start-input', 'value'),
     State('finish-input', 'value'),
     State('gantt-chart-js', 'relayoutData'),
     State('gantt-chart-ms', 'relayoutData'),
     State('gantt-data-js', 'data'),
     State('gantt-data-ms', 'data'),
     State('selected-task', 'data')]
)
def update_data(save_n_clicks, update_n_clicks, start, finish, relayoutData_js, relayoutData_ms, data_js, data_ms, selected_task):
    ctx = dash.callback_context
    if not ctx.triggered:
        return data_js, data_ms

    button_id = ctx.triggered[0]['prop_id'].split('.')[0]

    if button_id == 'save-button':
        if relayoutData_js:
            for shape in relayoutData_js.get('shapes', []):
                if 'name' in shape:
                    task = shape['name']
                    start_date = datetime.fromtimestamp(shape['x0'] / 1000).strftime('%Y-%m-%d')
                    end_date = datetime.fromtimestamp(shape['x1'] / 1000).strftime('%Y-%м-%д')
                    for d in data_js:
                        if d['Task'] == task:
                            d['Start'] = start_date
                            d['Finish'] = end_date

        if relayoutData_ms:
            for shape in relayoutData_ms.get('shapes', []):
                if 'name' in shape:
                    task = shape['name']
                    start_date = datetime.fromtimestamp(shape['x0'] / 1000).strftime('%Y-%м-%д')
                    end_date = datetime.fromtimestamp(shape['x1'] / 1000).strftime('%Y-%м-%д')
                    for d in data_ms:
                        if d['Task'] == task:
                            d['Start'] = start_date
                            d['Finish'] = end_date

    elif button_id == 'update-button':
        task = selected_task['task']
        chart = selected_task['chart']
        if task and start is not None and finish is not None:
            if chart == 'js':
                for d in data_js:
                    if d['Task'] == task:
                        d['Start'] = start
                        d['Finish'] = finish
            elif chart == 'ms':
                for d in data_ms:
                    if d['Task'] == task:
                        d['Start'] = start
                        d['Finish'] = finish

    return data_js, data_ms

@app.callback(
    Output('gantt-chart-js', 'figure'),
    Input('gantt-data-js', 'data')
)
def update_gantt_chart_js(data):
    return ff.create_gantt(data, index_col='Resource', show_colorbar=True, group_tasks=True)

@app.callback(
    Output('gantt-chart-ms', 'figure'),
    Input('gantt-data-ms', 'data')
)
def update_gantt_chart_ms(data):
    return ff.create_gantt(data, index_col='Resource', show_colorbar=True, group_tasks=True)

@app.callback(
    [Output('start-input', 'value'),
     Output('finish-input', 'value'),
     Output('selected-task', 'data')],
    [Input('gantt-chart-js', 'clickData'),
     Input('gantt-chart-ms', 'clickData')]
)
def display_click_data(clickData_js, clickData_ms):
    if clickData_js and 'points' in clickData_js and len(clickData_js['points']) > 0:
        point = clickData_js['points'][0]
        if 'customdata' in point:
            task_name = point['customdata']
            start_value = point['x0']
            finish_value = point['x1']
            return start_value, finish_value, {'task': task_name, 'chart': 'js'}
    elif clickData_ms and 'points' in clickData_ms and len(clickData_ms['points']) > 0:
        point = clickData_ms['points'][0]
        if 'customdata' in point:
            task_name = point['customdata']
            start_value = point['x0']
            finish_value = point['x1']
            return start_value, finish_value, {'task': task_name, 'chart': 'ms'}
    return None, None, {'task': None, 'chart': None}

if __name__ == '__main__':
    app.run_server(debug=True)
