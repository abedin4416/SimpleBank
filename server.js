const express = require('express');
const path = require('path');
const Database = require('better-sqlite3');
const argon2 = require('argon2');

const app = express();
app.use(express.json());

const db = new Database('bank.db');

db.exec(`
    CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL,
    balance REAL DEFAULT 0
    );
`)

app.post('/register', async (req, res) => {
    const {userId, password} = req.body;

    if (!userId || !password) {
        return res.status(400).json({ error: "Missing fields" });
    }

    try {
        const hash = await argon2.hash(password);
        const stmt = db.prepare(`
            INSERT INTO users (user_id, password_hash, balance)
            VALUES (?, ?, ?)
        `);

        stmt.run(userId, hash, 0);
        res.json({message: "Account created"});
    } catch (err) {
        if(err.code === 'SQLITE_CONSTRAINT_UNIQUE'){
            res.status(400).json({error: "User already exists"});
        }
        return res.status(500).json({ error: "Server error" });
    }
});

app.post('/login', async (req, res) => {
    const {userId, password} = req.body;
    const stmt = db.prepare(`
        SELECT * FROM users WHERE user_id = ?
    `);

    if(!userId || !password){
        return res.status(400).json({error: "Missing fields"});
    }

    const user = stmt.get(userId);

    if(!user) {
        return res.status(400).json({error: "Invalid credentials"});
    }

    const ok = await argon2.verify(user.password_hash, password);

    if(!ok) {
        return res.status(400).json({error: "Invalid credentials"});
    }

    res.json({
        message: "Login success",
        userId: user.user_id,
        balance: user.balance
    });
});
app.use('/', express.static('signin'));
app.use('/res', express.static('res'));
app.use('/signup', express.static('signup'));

app.listen(3000);