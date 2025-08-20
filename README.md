# Project-Chat-Message-History-Manager
# Chat Message History Manager

## 📌 Concept
A C++ program to manage chat messages with **undo/redo functionality**.  
It uses:
- **Queue** for incoming messages
- **Stack** for undo/redo actions
- **Timestamps** for tracking when messages were sent
- **CSV export** for saving chat history

## ⚙️ Features
- Send messages with timestamps
- Undo last sent message
- Redo undone message
- Export history to `messages.csv`

## 🗂️ Project Structure
ChatMessageHistoryManager/   ← Root folder (project name)
│
│── src/                     ← Source code folder
│   └── main.cpp             ← Your main C++ program
│
│── data/                    ← Data folder (for outputs)
│   └── messages.csv         ← Chat history export file
│
│── README.md                ← Documentation (project explanation)
│
│── Makefile (optional)      ← For easy build/run automation

