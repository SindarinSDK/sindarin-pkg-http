const http = require('http');

let items = {};
let nextId = 1;

const server = http.createServer((req, res) => {
    const url = new URL(req.url, `http://${req.headers.host}`);
    const path = url.pathname;
    const method = req.method;

    if (path === '/items') {
        handleItems(req, res, method);
    } else if (path.startsWith('/items/')) {
        const id = parseInt(path.substring('/items/'.length), 10);
        if (isNaN(id) || id <= 0) {
            sendJson(res, 400, { error: 'Invalid ID' });
        } else {
            handleItem(req, res, method, id);
        }
    } else {
        sendText(res, 404, 'Not found');
    }
});

function handleItems(req, res, method) {
    switch (method) {
        case 'GET':
            listItems(res);
            break;
        case 'POST':
            createItem(req, res);
            break;
        default:
            sendText(res, 405, 'Method not allowed');
    }
}

function handleItem(req, res, method, id) {
    switch (method) {
        case 'GET':
            getItem(res, id);
            break;
        case 'PUT':
            updateItem(req, res, id);
            break;
        case 'DELETE':
            deleteItem(res, id);
            break;
        default:
            sendText(res, 405, 'Method not allowed');
    }
}

function sendJson(res, status, data) {
    const body = JSON.stringify(data);
    res.writeHead(status, {
        'Content-Type': 'application/json',
        'Content-Length': Buffer.byteLength(body)
    });
    res.end(body);
}

function sendText(res, status, text) {
    res.writeHead(status, {
        'Content-Type': 'text/plain',
        'Content-Length': Buffer.byteLength(text)
    });
    res.end(text);
}

function readBody(req) {
    return new Promise((resolve) => {
        let body = '';
        req.on('data', chunk => body += chunk);
        req.on('end', () => resolve(body));
    });
}

function isJsonContentType(req) {
    const contentType = req.headers['content-type'] || '';
    return contentType.includes('application/json');
}

function listItems(res) {
    const result = Object.entries(items).map(([id, data]) => ({
        id: parseInt(id, 10),
        ...data
    }));
    sendJson(res, 200, result);
}

async function createItem(req, res) {
    if (!isJsonContentType(req)) {
        sendJson(res, 400, { error: 'Content-Type must be application/json' });
        return;
    }

    const body = await readBody(req);
    let data;
    try {
        data = JSON.parse(body);
    } catch {
        data = {};
    }

    const id = nextId++;
    items[id] = data;

    sendJson(res, 201, { id, ...data });
}

function getItem(res, id) {
    const data = items[id];
    if (!data) {
        sendJson(res, 404, { error: 'Item not found' });
        return;
    }
    sendJson(res, 200, { id, ...data });
}

async function updateItem(req, res, id) {
    if (!(id in items)) {
        sendJson(res, 404, { error: 'Item not found' });
        return;
    }

    if (!isJsonContentType(req)) {
        sendJson(res, 400, { error: 'Content-Type must be application/json' });
        return;
    }

    const body = await readBody(req);
    let data;
    try {
        data = JSON.parse(body);
    } catch {
        data = {};
    }

    items[id] = data;
    sendJson(res, 200, { id, ...data });
}

function deleteItem(res, id) {
    if (!(id in items)) {
        sendJson(res, 404, { error: 'Item not found' });
        return;
    }
    delete items[id];
    sendJson(res, 200, { deleted: true });
}

server.listen(8081, () => {
    console.log('Node.js Server listening on port 8081');
});
