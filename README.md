# 📝 Action Board Tracker – Qt Task Manager

This is a **desktop-based Task Manager application** built using **Qt (C++ framework)**. The app is designed to help users track their tasks, mark them as complete, move them to a recycle bin, and restore or permanently delete them. Users can also save tasks to a file and load them back later without overwriting existing data (merge behavior).

---

## 🚀 Features

- ✅ Add new tasks to the To-Do list
- ✅ Mark tasks as completed (checkbox)
- ✅ Unmark completed tasks to return to To-Do
- ♻️ Move tasks to a **Recycling Bin** (with separate buttons for To-Do and Done tasks)
- 🔁 Restore tasks from Recycling Bin to original list
- ❌ Permanently delete tasks from the bin
- 💾 Save tasks to a `.txt` file
- 📂 Load tasks from a file (merges with current tasks, avoids duplicates)

---

## 📁 File Structure

- `widget.h` – Header file declaring the UI components and slots
- `widget.cpp` – Core logic and UI layout using Qt Widgets
- `main.cpp` – Standard Qt application entry point
- `resources.qrc` – (Optional) Add for icons or future styling

---

## 💡 How Tasks Are Handled

- **To-Do Tasks**: Unchecked tasks
- **Completed Tasks**: Checked tasks
- **Recycling Bin**: Stores deleted tasks along with metadata (`todo` or `done`)
- **File Saving Format**:
- **To-Do Tasks**:
- ***Task 1***:
- ***Task 2***:
- **Completed Tasks**:
- ***Task A***:
- ***Task B***:
- **Recycling Bin**:
- ***Task Y***:
- ***Task Z***:


---

## 🛠️ Requirements

- Qt 5 or 6 (Tested with Qt 6.x)
- C++17 or later
- Qt Creator (recommended) or any C++ IDE with qmake or CMake support

---

## 🧪 How to Build & Run

1. Clone the repository
2. Open `*.pro` or `CMakeLists.txt` in Qt Creator
3. Click **Build** and **Run**

---

## 🛣️ Planned Features (Suggestions)

- [ ] Dark mode / themes
- [ ] Drag-and-drop between lists
- [ ] Due dates and reminders
- [ ] JSON file format support
- [ ] Sync with cloud or GitHub gist

---

## 📸 Preview (Optional)

*You can add a screenshot here in future:*



---

## 📄 License

This project is for learning purposes and open for modification or reuse under the **MIT License**.

---

## 👨‍💻 Author

**Musa Dondolo**  
Freelance Developer  
[GitHub Profile](https://github.com/dondolo2) (Replace this with your link)

