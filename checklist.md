# ✅ Development Planning Checklist for Action Board Tracker

## 🎯 Project Goal
Build a desktop Task Manager using Qt (C++) that helps users:
- Add, complete, restore, delete, and permanently remove tasks.
- Organize tasks into To-Do, Done, and Recycle sections.
- Toggle between light and dark themes.
- Save and load tasks from file.
- Have an intuitive, styled GUI with mouse and scroll support.

---

## ✅ UI Components
- [x] Main window with fixed size and emoji title
- [x] Title label with shadow and custom font
- [x] QLineEdit for task input
- [x] Add Task button
- [x] Theme toggle button (☀️/🌙)
- [x] Scrollable central area for layouts
- [x] Labels for task categories (To-Do, Completed, Bin)
- [x] Three QListWidgets (To-Do, Done, Recycling Bin)
- [x] Buttons for:
  - Move Task to Bin
  - Move Done to Bin
  - Restore Task
  - Permanently Delete
  - Load from File
  - Save to File

---

## 🎨 Styling Requirements
- [x] Custom QSS for light and dark modes
- [x] Button hover effects
- [x] Emoji icons on labels
- [x] Font sizing and spacing consistency
- [x] Scrollbar customization
- [x] Mouse pointer cursor for interactivity

---

## 💾 File Handling
- [x] Save task lists (To-Do, Done, Bin) to text file
- [x] Load and merge from text file

---

## ♻️ Task Logic
- [x] Prevent duplicates across lists
- [x] Move checked tasks to "Done"
- [x] Move unchecked from Done → To-Do
- [x] Move items to/from recycle bin
- [x] Mark origin (To-Do or Done) for restoration
- [x] Allow permanent deletion

---

## 🔄 Theme Switching
- [x] Theme toggle using emoji button
- [x] Load `light.qss` and `dark.qss` stylesheets
- [x] Default dark mode

---

## 🧪 Optional Extras (Stretch Goals)
- [ ] Sort tasks alphabetically or by timestamp
- [ ] Add due dates or priority levels
- [ ] Search/filter tasks
- [ ] Export to other formats (e.g. CSV, JSON)
