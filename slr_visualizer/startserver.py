import subprocess as sp
import os
from bottle import route, run, static_file, template, TEMPLATE_PATH, view, Bottle, request, post
get_url = Bottle.get_url

abs_app_dir_path = os.path.dirname(os.path.realpath(__file__))
abs_views_path = os.path.join(abs_app_dir_path, 'templates')
TEMPLATE_PATH.insert(0, 'templates')

annotate = lambda x: '\"' + x + '\"'


@route('/static/:path#.+#', name='static')
def static(path):
    return static_file(path, root='templates/static')


@view('index')
def get_index_page(grammar='S->AA\nA->aA|b', s_json=''):
    return template('index', root='templates', grammar=grammar, s_json=s_json)


def get_json(grammar: str):
    cmd = 'templates\static\main.exe '
    l = grammar.split('\r\n')
    print("l :", l)
    cmd += ' '.join(list(map(lambda x: '\"' + x + '\"', l)))
    output = sp.getoutput(cmd)
    print(cmd)
    return output


@ post('/generate')
def generate():
    grammar = request.params.get('grammar_text')
    s_json = get_json(grammar=grammar)
    return get_index_page(grammar=grammar, s_json=s_json)


@ route('/')
def index():
    return get_index_page()


run(host='localhost', port=8080, reloader=True)
