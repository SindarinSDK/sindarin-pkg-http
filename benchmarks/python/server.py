#!/usr/bin/env python3
"""HTTP JSON REST API Server - Python Implementation"""

import json
import threading
from http.server import HTTPServer, BaseHTTPRequestHandler
from socketserver import ThreadingMixIn
from urllib.parse import urlparse

items = {}
next_id = 1
lock = threading.Lock()

# Pre-populate 1000 items
for _i in range(1, 1001):
    items[_i] = {'name': f'Item {_i}', 'value': _i}


class ThreadedHTTPServer(ThreadingMixIn, HTTPServer):
    daemon_threads = True


class RequestHandler(BaseHTTPRequestHandler):
    protocol_version = 'HTTP/1.1'

    def log_message(self, format, *args):
        pass  # Suppress logging for performance

    def send_json(self, status, data):
        body = json.dumps(data).encode('utf-8')
        self.send_response(status)
        self.send_header('Content-Type', 'application/json')
        self.send_header('Content-Length', len(body))
        self.end_headers()
        self.wfile.write(body)

    def send_text(self, status, text):
        body = text.encode('utf-8')
        self.send_response(status)
        self.send_header('Content-Type', 'text/plain')
        self.send_header('Content-Length', len(body))
        self.end_headers()
        self.wfile.write(body)

    def read_body(self):
        content_length = int(self.headers.get('Content-Length', 0))
        return self.rfile.read(content_length).decode('utf-8')

    def is_json_content_type(self):
        content_type = self.headers.get('Content-Type', '')
        return 'application/json' in content_type

    def parse_id(self):
        try:
            return int(self.path.split('/')[2])
        except (IndexError, ValueError):
            return -1

    def do_GET(self):
        if self.path == '/items':
            self.list_items()
        elif self.path.startswith('/items/'):
            item_id = self.parse_id()
            if item_id > 0:
                self.get_item(item_id)
            else:
                self.send_json(400, {'error': 'Invalid ID'})
        else:
            self.send_text(404, 'Not found')

    def do_POST(self):
        if self.path == '/items':
            self.create_item()
        else:
            self.send_text(404, 'Not found')

    def do_PUT(self):
        if self.path.startswith('/items/'):
            item_id = self.parse_id()
            if item_id > 0:
                self.update_item(item_id)
            else:
                self.send_json(400, {'error': 'Invalid ID'})
        else:
            self.send_text(404, 'Not found')

    def do_DELETE(self):
        if self.path.startswith('/items/'):
            item_id = self.parse_id()
            if item_id > 0:
                self.delete_item(item_id)
            else:
                self.send_json(400, {'error': 'Invalid ID'})
        else:
            self.send_text(404, 'Not found')

    def list_items(self):
        global items
        with lock:
            result = []
            for item_id, data in items.items():
                item = {'id': item_id}
                item.update(data)
                result.append(item)
        self.send_json(200, result)

    def create_item(self):
        global items, next_id

        if not self.is_json_content_type():
            self.send_json(400, {'error': 'Content-Type must be application/json'})
            return

        body = self.read_body()
        try:
            data = json.loads(body)
        except json.JSONDecodeError:
            data = {}

        with lock:
            item_id = ((next_id - 1) % 1000) + 1
            next_id += 1
            items[item_id] = data

        result = {'id': item_id}
        result.update(data)
        self.send_json(200, result)

    def get_item(self, item_id):
        global items
        with lock:
            data = items.get(item_id)

        if data is None:
            self.send_json(200, {'id': item_id, 'name': '', 'value': 0})
            return

        result = {'id': item_id}
        result.update(data)
        self.send_json(200, result)

    def update_item(self, item_id):
        global items

        if not self.is_json_content_type():
            self.send_json(400, {'error': 'Content-Type must be application/json'})
            return

        body = self.read_body()
        try:
            data = json.loads(body)
        except json.JSONDecodeError:
            data = {}

        with lock:
            items[item_id] = data

        result = {'id': item_id}
        result.update(data)
        self.send_json(200, result)

    def delete_item(self, item_id):
        global items
        with lock:
            items.pop(item_id, None)

        self.send_json(200, {'deleted': True})


def main():
    server = ThreadedHTTPServer(('', 8081), RequestHandler)
    print('Python Server listening on port 8081')
    server.serve_forever()


if __name__ == '__main__':
    main()
