# ✅ Qt Task Manager App Development Checklist

---

## 🛠️ 1. Project Setup
- [ ] Create Qt Widgets Application (no form)
- [ ] Set base class to QWidget
- [ ] Confirm files: `main.cpp`, `widget.h`, `widget.cpp`, `.pro`
- [ ] Initialize Git repository
- [ ] Create and push `test` branch
- [ ] Add and commit `checklist.md`

---

## 🎨 2. UI Layout
- [ ] Create QLineEdit for task input
- [ ] Add QPushButton to add task
- [ ] Create QListWidget to display tasks
- [ ] Add a checkbox or icon per task for status
- [ ] Organize widgets using QVBoxLayout or QGridLayout
- [ ] Add styling with Qt Stylesheets

---

## 💾 3. Task Management Logic
- [ ] Connect "Add" button to slot function
- [ ] Append task to QListWidget on click
- [ ] Add functionality to delete selected task
- [ ] Add functionality to mark task as complete/incomplete
- [ ] Add signal-slot connections for dynamic interactivity
- [ ] Optional: Implement task editing on double-click

---

## 🧠 4. Data Persistence (Basic)
- [ ] Save task list to a text file or JSON
- [ ] Load tasks from file when app starts
- [ ] Include task status (complete/incomplete) in file

---

## 🗃️ 5. Task Metadata (Advanced Features)
- [ ] Add due date field (using QDateEdit or QCalendarWidget)
- [ ] Add dropdown or tags for categories (e.g., Work, Personal)
- [ ] Implement filter view (e.g., show only Work tasks)
- [ ] Add sort option (e.g., by date or category)

---

## 🚀 6. Polish & UX
- [ ] Add confirmation dialog for deleting a task
- [ ] Add status bar or feedback label for actions
- [ ] Add icons to buttons (e.g., trash bin, checkmark)
- [ ] Make UI responsive and well-aligned
- [ ] Add keyboard shortcuts (e.g., Enter to add task)

---

## 🧪 7. Final Touches & Git
- [ ] Test app flow end-to-end
- [ ] Commit and push after each milestone
- [ ] Create a `feature/ui`, `feature/storage` etc. branches for major work
- [ ] Merge to `main` only after full testing
- [ ] Tag first working version as `v1.0`
