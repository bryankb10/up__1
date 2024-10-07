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
    } else if (req.url === '/style.css') { // Serve the CSS file
        fs.readFile(path.join(__dirname, 'style.css'), (err, content) => {
            if (err) {
                res.writeHead(500);
                res.end('Error loading style.css');
            } else {
                res.writeHead(200, { 'Content-Type': 'text/css' }); // Correct MIME type
                res.end(content);
            }
        });
    } else if (req.url === '/custom-extension.js') {
        fs.readFile(path.join(__dirname, 'custom-extension.js'), (err, content) => {
            if (err) {
                res.writeHead(500);
                res.end('Error loading custom-extension.js');
            } else {
                res.writeHead(200, { 'Content-Type': 'application/javascript' });
                res.end(content);
            }
        });
    }else if (req.url === '/hello') {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end('<h3> YOU GET HAWK TUH GAWK GAWK SOUL SUCKER 3000</h3>');
    } else if (req.url === '/submit' && req.method === 'POST') {
        let body = '';
        req.on('data', chunk => {
            body += chunk.toString(); // convert Buffer to string
        });
        req.on('end', () => {
            const params = new URLSearchParams(body);
            const username = params.get('username');
            const email = params.get('email');
            setTimeout(() => {
                res.writeHead(200, { 'Content-Type': 'text/html' });
                res.end(`<h2>Submission Received</h2><p>Username: ${username}</p><p>Email: ${email}</p>`);
            }, 1000);

        });
	} else if (req.url === '/items'){
		res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(renderItems());
	}else if (req.url.startsWith('/delete/') && req.method === 'DELETE') {
        const id = parseInt(req.url.split('/')[2]);
        deleteItem(id, res);		
	} else if (req.url === '/add-item'&&req.method==='POST'){
        AddItem(req, res);
    } else if (req.url=== '/tab1') {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end('<p>This is content for Tab 1.</p>');
    } else if (req.url === '/tab2') {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end('<p>This is content for Tab 2.</p>');
    } else if (req.url === '/tab3') {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end('<p>This is content for Tab 3.</p>');
    } else {
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
                    hx-trigger="click delay:500ms"
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
function AddItem(req, res){
    let body = '';
    req.on('data', chunk => {
        body += chunk.toString();
    });
    req.on('end', () => {
        const itemName = new URLSearchParams(body).get('itemName');
        const newItem = {
            id: items.length + 1, // Auto-incrementing the ID
            name: itemName
    };
    items.push(newItem); // Add the new item to the list
    res.writeHead(200, { 'Content-Type': 'text/html' });
    res.end(`
        <li id="item-${newItem.id}">
            ${newItem.name}
            <button hx-delete="/delete/${newItem.id}"
                    hx-confirm="Are you sure you want to delete this item?"
                    hx-target="#item-${newItem.id}"
                    hx-swap="outerHTML"
                    class="delete-btn">
                Delete
                <span class="htmx-indicator">Deleting...</span>
            </button>
        </li>
    `);
});
}

const PORT = 3000;
server.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
    console.log(`Load initial items by visiting: http://localhost:${PORT}/items`);
});

