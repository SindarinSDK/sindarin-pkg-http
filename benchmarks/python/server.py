#!/usr/bin/env python3
"""HTTP JSON REST API Server - Python Implementation (uvicorn + starlette)"""

import json
import uvicorn
from starlette.applications import Starlette
from starlette.responses import JSONResponse, Response
from starlette.routing import Route

items = {}
next_id = 1

# Pre-populate 1000 items
for _i in range(1, 1001):
    items[_i] = {'name': f'Item {_i}', 'value': _i}


async def list_items(request):
    result = [{'id': k, **v} for k, v in items.items()]
    return JSONResponse(result)


async def create_item(request):
    global next_id

    content_type = request.headers.get('content-type', '')
    if 'application/json' not in content_type:
        return JSONResponse({'error': 'Content-Type must be application/json'}, status_code=400)

    try:
        data = await request.json()
    except Exception:
        data = {}

    item_id = ((next_id - 1) % 1000) + 1
    next_id += 1
    items[item_id] = data

    return JSONResponse({'id': item_id, **data})


async def get_item(request):
    item_id = int(request.path_params['id'])
    data = items.get(item_id)

    if data is None:
        return JSONResponse({'id': item_id, 'name': '', 'value': 0})

    return JSONResponse({'id': item_id, **data})


async def update_item(request):
    item_id = int(request.path_params['id'])

    content_type = request.headers.get('content-type', '')
    if 'application/json' not in content_type:
        return JSONResponse({'error': 'Content-Type must be application/json'}, status_code=400)

    try:
        data = await request.json()
    except Exception:
        data = {}

    items[item_id] = data

    return JSONResponse({'id': item_id, **data})


async def delete_item(request):
    item_id = int(request.path_params['id'])
    items.pop(item_id, None)
    return JSONResponse({'deleted': True})


async def handle_items(request):
    if request.method == 'GET':
        return await list_items(request)
    elif request.method == 'POST':
        return await create_item(request)
    return Response('Method not allowed', status_code=405, media_type='text/plain')


async def handle_item(request):
    if request.method == 'GET':
        return await get_item(request)
    elif request.method == 'PUT':
        return await update_item(request)
    elif request.method == 'DELETE':
        return await delete_item(request)
    return Response('Method not allowed', status_code=405, media_type='text/plain')


app = Starlette(routes=[
    Route('/items', handle_items, methods=['GET', 'POST']),
    Route('/items/{id:int}', handle_item, methods=['GET', 'PUT', 'DELETE']),
])

if __name__ == '__main__':
    print('Python Server listening on port 8081')
    uvicorn.run(app, host='0.0.0.0', port=8081, log_level='error')
