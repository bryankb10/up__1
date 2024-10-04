const http = require('http');
const fs = require('fs');
const path = require('path');

let items = [
    { id: 1, name: 'Item 1' },
    { id: 2, name: 'Item 2' },
    { id: 3, name: 'Item 3' }
];


const server = http.createServer((req, res) => {
    if (req.url === '/') {
        fs.readFile(path.join(__dirname, 't3st.html'), (err, content) => {
            if (err) {
                res.writeHead(500);
                res.end('Error loading index.html');
            } else {
                res.writeHead(200, { 'Content-Type': 'text/html' });
                res.end(content);
            }
        });
    } else if (req.url === '/hello') {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end('<h2>You get  HAWK TUH GAWK GAWK SOUL SUCKER 3000!!</h2>');
    } else if (req.url === '/submit' && req.method === 'POST') {
        let body = '';
        req.on('data', chunk => {
            body += chunk.toString(); // convert Buffer to string
        });
        req.on('end', () => {
            const email = new URLSearchParams(body).get('email');
            res.writeHead(200, { 'Content-Type': 'text/html' });
            res.end(`<h2>Thank you for submitting: ${email}</h2>`);
        });

	} else if (req.url === '/items'){
		res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(renderItems());
	}else if (req.url.startsWith('/delete/') && req.method === 'DELETE') {
        const id = parseInt(req.url.split('/')[2]);
        deleteItem(id, res);		
	}else {
        res.writeHead(404);
        res.end('Not Found');
    }
});

function renderItems() {
    return items.map(item => `
        <li id="item-${item.id}">
            ${item.name}
            <button hx-delete="/delete/${item.id}"
                    hx-confirm="Are you sure you want to delete this item?"
                    hx-target="#item-${item.id}"
                    hx-swap="outerHTML"
                    class="delete-btn">
                Delete
                <span class="htmx-indicator">Deleting...</span>
            </button>
        </li>
    `).join('');
}

function deleteItem(id, res) {
    setTimeout(() => {  // Simulate a delay
        items = items.filter(item => item.id !== id);
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(''); // Send an empty response to remove the item
    }, 1000);
}

const PORT = 3000;
server.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
    console.log(`Load initial items by visiting: http://localhost:${PORT}/items`);
});

